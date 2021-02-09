#ifndef GAME_ENTITIES_HPP
#define GAME_ENTITIES_HPP

#include <memory>


#include "Entities/AdventurerEntities.hpp"
#include "Entities/QuestEntities.hpp"
#include "Entities/GuildEntitiess.hpp"
#include "Entities/GameStates.hpp"

#include "DataKeepers/AdventurerDataKeepers.hpp"
#include "DataKeepers/SkillDataKeepers.hpp"
#include "DataKeepers/QuestDataKeepers.hpp"

#include "Generators/AdventurerGenerators.hpp"
#include "Generators/QuestGenerators.hpp"

#include "Perks/Perks.hpp"

constexpr int MIN_QUEST_COUNT = 5;
constexpr int MAX_QUEST_COUNT = 10;
constexpr int MIN_ADVENTURER_COUNT = 3;
constexpr int MAX_ADVENTURER_COUNT = 10;
constexpr int DEFAULT_QUEST_RESERVATION_GOLD_RENT = 50;
constexpr int DEFAULT_FAME_TO_GOLD_RATE = 10;
constexpr int DEFAULT_RESSURECTION_COST = 1000;
constexpr int DEFAULT_RETRAIN_COST_PER_SKILL = 250;
constexpr int DEFAULT_UPGRADE_COST_PER_RARITY_DIFF = 250;
constexpr int DEFAULT_GODSLAYER_COST = 500;
constexpr int DEFAULT_COST_PER_LEVEL_PERK = 500;

class GameDataManager
{
public:
	GameDataManager()
	{
		game_state = std::make_unique<GameState>();
	}
	std::unique_ptr<GameState> game_state;
	std::unique_ptr<Guild> guild;
	std::unique_ptr<QuestDataKeeper> quests;
	std::unique_ptr<AdventurerDataKeeper> adventurers;
	std::unique_ptr<QuestGenerator> gen_quests;
	std::unique_ptr<AdventurerGenerator> gen_adventurers;
	std::unique_ptr<SkillDataKeeper> skills;

	/// <summary>
	/// Create new game.
	/// </summary>
	void start_game();
	/// <summary>
	/// Progress game to next turn.
	/// </summary>
	void wait_turn();
	/// <summary>
	/// End current game.
	/// </summary>
	void end_game();
	/// <summary>
	/// Change guild name. Return is mostly true, rare cases false.
	/// </summary>
	bool rename_guild(const std::string&& new_guild_name);
	/// <summary>
	/// Change difficulty. Return is true value of new difficulty.
	/// </summary>
	int change_difficulty(const int new_difficulty);
	/// <summary>
	/// Accept quest. Return is true or false if quest was not found in available.
	/// </summary>
	bool take_quest(const int quest_id);
	/// <summary>
	/// Hire adventurer. Return is true or false if adventurer was not found in available.
	/// </summary>
	bool hire_adventurer(const int adventurer_id); //true on did something, else false
	/// <summary>
	/// Retire adventurer. Return is true or false if adventurer was not found in hired or not enough money.
	/// </summary>
	bool pension_adventurer(const int adventurer_id);



	/// <summary>
	/// Trade fame for gold. Return is true or false if not enough.
	/// </summary>
	bool trade(int fame_to_convert);
	/// <summary>
	/// Ressurect adventurer for gold. Return is true or false if not dead or found.
	/// </summary>
	bool resurrect(int adventurer_id);
	/// <summary>
	/// Retrain adventurer skills for gold. Return is true or false if not hired or found.
	/// </summary>
	bool retrain(int adventurer_id);
	/// <summary>
	/// Upgrade adventurer rarity for gold. Return is true or false if not hired or found.
	/// Up to Innkeeper.
	/// </summary>
	bool upgrade(int adventurer_id);
	/// <summary>
	/// Grant adventurer special skill for gold. Return is true or false if not hired or found.
	/// Adventurer becomes god.
	/// </summary>
	bool grant_godslayer(int adventurer_id);
	/// <summary>
	/// Buy perk for a guild.
	/// Adventurer becomes god.
	/// </summary>
	bool buy_perk(int perk_id);
protected:
	/// <summary>
	/// Clear current game state.
	/// </summary>
	void reset_game();
	/// <summary>
	/// Progress game by generating new quests and adventurers.
	/// </summary>
	void progress_game();
	void generate_quests(int quest_count);
	void generate_adventurers(int adventurer_count);
	void substract_quest_wait_fees();
	void substract_adventurer_wait_fees();


	 //true on did something, else false
	bool dispatch(const int adventurer_id, const int quest_id);

	


};
/*/

	inline int calculate_experience(int diff, int level)
	{
		int base = 1000;
		int quest_multiplier = 11 - diff; // value from 1 to 10 (lv1 quest == 10, lv10 quest == 1)
		int quest_reward = std::clamp((base / quest_multiplier), 100, 1000);
		int level_bonus = diff / level;
		return quest_reward * level_bonus;
	}

	inline bool calculate_success(unsigned long long chance, unsigned long long base)
	{
		return chance >= base;
	}

	inline bool calculate_total_success(unsigned long long base, int level, int diff)
	{
		bool final_result;

		if (level - diff > 0) // x:1 is advantage, first success is result
		{
			final_result = false;
			for (int i = 0; i < level - diff + 1 && final_result == false; ++i)
			{
				final_result = calculate_success(chance_generator.get_chance(), base);
			}
		}
		else if (level - diff < 0) // 1:x is disadvantage, first fail is result
		{
			final_result = true;
			for (int i = 0; i < diff - level + 1 && final_result == true; ++i)
			{
				final_result = calculate_success(chance_generator.get_chance(), base);
			}
		}
		else // 1:1, base roll is returned
		{
			final_result = calculate_success(chance_generator.get_chance(), base);
		}
		return final_result;
	}

	void resolve_level(Adventurer* const adventurer, int old_lvl, int new_lvl)
	{
		const int skill_count = new_lvl / 5 - old_lvl / 5;
		if (skill_count > 0)
		{
				adventurer->set_skills(encyclopedia.generate_from_rarity(skill_count, adventurer->get_skills()));
		}
		else if (skill_count < 0) // level down at 5 and 10 does something
		{
			adventurer->rmv_skill(-skill_count); // lose last skill obtained, sorry :)
		}
	}

	inline QuestStateEnum dispatch(int adventurer_id, int quest_id)
	{
		const auto adventurer = CollectionIterators::find(adventurers.get_hired(), adventurer_id);
		const auto quest = CollectionIterators::find(quests.get_reserved(), quest_id);
		if (adventurer != nullptr && quest != nullptr && current_guild.get_gold() >= adventurer->get_living_expenses())
		{
			// Substract dispatch cost
			current_guild.rmv_gold(adventurer->get_living_expenses());
			
			//modify compare_value
			unsigned long long compare_value = adventurer->get_fail_quest_ids().size() + 51ull - adventurer->get_succ_quest_ids().size();
			{
				compare_value = std::clamp(compare_value, 10ull, 90ull);
			}
			// Calculate result
			bool result = calculate_total_success(compare_value, adventurer->get_level(), quest->get_difficulty());

			Reward quest_reward = quest->get_reward();
			Penalty quest_penalty = quest->get_penalty();
			for (auto && skill : adventurer->get_skills())
			{
				skill->execute_skill(result, *quest, quest_reward, quest_penalty);
			}
			
			// Finish valuation of quest
			if (result)
			{
				// Get Reward
				current_guild.add_gold(quest_reward.get_gold());
				current_guild.add_fame(quest_reward.get_fame());
				// Update experience
				auto old_lvl = adventurer->get_level();
				adventurer->add_experience(calculate_experience(quest->get_difficulty(), adventurer->get_level()));
				auto new_lvl = adventurer->get_level();
				resolve_level(adventurer, old_lvl, new_lvl);
				
				// Assign Quest - Adventurer and complete quest
				quest->set_adventurer_id(adventurer_id);
				adventurer->set_succ_quest_id(quest_id);
				quests.complete(quest_id);
				quest->set_state(QuestStateEnum::Success);
				return quest->get_state();
			}
			else
			{
				// Get Penalty
				current_guild.rmv_gold(quest_penalty.get_gold());
				current_guild.rmv_fame(quest_penalty.get_fame());
				if (quest_penalty.get_deadly())
				{
					// Just kill, no exp obtained sorry bro.
					adventurers.kill(adventurer_id);					
				}
				else
				{
					// Update experience
					auto old_lvl = adventurer->get_level();
					adventurer->rmv_experience(calculate_experience(quest->get_difficulty(), adventurer->get_level()));
					auto new_lvl = adventurer->get_level();
					resolve_level(adventurer, old_lvl, new_lvl);
				}
				
				// Assign Quest - Adventurer and fail quest
				quest->set_adventurer_id(adventurer_id);
				adventurer->set_fail_quest_id(quest_id);
				quests.fail(quest_id);
				quest->set_state(QuestStateEnum::Failure);
				return quest->get_state();
			}
		}
		return QuestStateEnum::Undefined;
	}
private:
	ChanceGenerator chance_generator;
};

/**/

#endif