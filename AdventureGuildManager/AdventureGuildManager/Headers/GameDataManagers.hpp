#ifndef GAME_ENTITIES_HPP
#define GAME_ENTITIES_HPP

#include <memory>

#include "Entities/GameStates.hpp"
#include "Entities/GuildEntitiess.hpp"


class GameDataManager
{
public:
	GameDataManager()
	{
		game_state = std::make_unique<GameState>();
		guild = std::make_unique<Guild>();
	}
	std::unique_ptr<GameState> game_state;
	std::unique_ptr<Guild> guild;

	//clear_game_state is original name
	void start_game(); // create game
	void end_game(); // end game
	bool rename_guild(const std::string& cs);
	void change_difficulty(const int new_difficulty);
	bool take_quest(const int quest_id);
	bool dispatch(const int adventurer_id, const int quest_id); //true on did something, else false
	bool hire_adventurer(const int adventurer_id); //true on did something, else false
	bool pension_adventurer(const int adventurer_id); //true on did something, else false
	/*
	class GuildCreateCommand : public ICommand
	{
	public:
		std::string execute(GameData& game_data) override
		{
			if (game_data.game_state.get_progress_state())
				return interface.game_in_progress();
			game_data.create_game();
			return interface.to_string(game_data.current_guild);
		}
	private:
		GuildInterfaces interface;
	};*/
};
/*/
#include <string>
#include <unordered_set>

#include "GenericEntities.hpp"
#include "Adventurers.hpp"
#include "Quests.hpp"
#include "ConsoleHelpers.hpp"
#include "Skills.hpp"
#include "Generators.hpp"
#include "GuildPerks.hpp"













class GameManagerData
{
public:
	GameState game_state;
	Guild current_guild;
	AdventurerKeeper adventurers;
	QuestKeeper quests;
	EncyclopediaKeeper encyclopedia;
	inline void clear_game_state()
	{
		game_state.clear();
		current_guild.clear();
		adventurers.clear();
		quests.clear();
	}
	/// <summary>
	/// Basically you need gold, so there is only one way to get gold at start...
	/// Due to this we can say that any setting can be done before.
	/// And as there is no reason to reset them, they will be kept.
	/// </summary>
	inline void create_game()
	{
		game_state.change_progress_state(true);
		current_guild.set_fame(0);
		current_guild.set_gold(1000);
		adventurers.generate(encyclopedia, 5);
		quests.generate(encyclopedia, 10);
	}
	inline void rename_guild(std::string new_name)
	{
		current_guild.set_name(new_name);
	}
	inline bool pension(int adventurer_id)
	{
		const auto adventurer = CollectionIterators::find(adventurers.get_hired(), adventurer_id);
		if (adventurer != nullptr && current_guild.get_gold() >= adventurer->get_level_retirement_cost())
		{
			// Substract retirement cost
			current_guild.rmv_gold(adventurer->get_level_retirement_cost());
			current_guild.add_fame(adventurer->get_level_retirement_fame());
			// Pension
			return adventurers.pension(adventurer_id);
		}
		return false;
	}
	inline bool recruit(int adventurer_id)
	{
		const auto adventurer = CollectionIterators::find(adventurers.get_available(), adventurer_id);
		if (adventurer != nullptr && current_guild.get_gold() >= adventurer->get_level_recruitment_cost())
		{
			// Substract recruitment cost
			current_guild.rmv_gold(adventurer->get_level_recruitment_cost());
			// Recruit
			return adventurers.recruit(adventurer_id);
		}
		return false;
	}

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