#ifndef GAME_ENTITIES_HPP
#define GAME_ENTITIES_HPP

#include <string>
#include <unordered_set>

#include "GenericEntities.hpp"
#include "Adventurers.hpp"
#include "Quests.hpp"
#include "ConsoleHelpers.hpp"
#include "Skills.hpp"
#include "Generators.hpp"

typedef std::vector<std::unique_ptr<Adventurer>> adventurer_collection;
typedef std::vector<std::unique_ptr<Quest>> quest_collection;
typedef std::vector<std::string> string_context;

class CollectionIterators
{
public:
	template<class T>
	static bool transfer(std::vector<std::unique_ptr<T>>& source, std::vector<std::unique_ptr<T>>& destination, int id)
	{
		const auto it = std::find_if(source.begin(), source.end(),
			[id](auto&& item)
			{
				return item->get_id() == id;
			});
		if (it != source.end())
		{
			destination.push_back(std::move(*it));
			source.erase(it);
			return true;
		}
		return false;
	}

	template<class T>
	static T* find(const std::vector<std::unique_ptr<T>>& source, int id)
	{
		const auto it = std::find_if(source.begin(), source.end(),
			[id](auto&& item)
			{
				return item->get_id() == id;
			});
		if (it != source.end())
		{
			return it->get();
		}
		return nullptr;
	}
};

class EncyclopediaKeeper
{
public:
	EncyclopediaKeeper()
	{
		// Generic
		skill_creators.push_back(std::make_unique<SimpleEntityCreator<ISkill, Hoarder>>(1));
		skill_creators.push_back(std::make_unique<SimpleEntityCreator<ISkill, EscapeArtist>>(2));
		skill_creators.push_back(std::make_unique<SimpleEntityCreator<ISkill, MisterHandsome>>(3));
		skill_creators.push_back(std::make_unique<SimpleEntityCreator<ISkill, PerfectHero>>(4));
		// Counter Skills
		skill_creators.push_back(std::make_unique<SimpleEntityCreator<ISkill, Cleave>>(100));
		skill_creators.push_back(std::make_unique<SimpleEntityCreator<ISkill, Assassin>>(101));
		skill_creators.push_back(std::make_unique<SimpleEntityCreator<ISkill, Mage>>(102));
		skill_creators.push_back(std::make_unique<SimpleEntityCreator<ISkill, Healer>>(103));
		skill_creators.push_back(std::make_unique<SimpleEntityCreator<ISkill, Paladin>>(104));
		skill_creators.push_back(std::make_unique<SimpleEntityCreator<ISkill, Shaman>>(105));
		skill_creators.push_back(std::make_unique<SimpleEntityCreator<ISkill, Fighter>>(106));
		skill_creators.push_back(std::make_unique<SimpleEntityCreator<ISkill, Lightbearer>>(107));
		skill_creators.push_back(std::make_unique<SimpleEntityCreator<ISkill, SurvivalExpert>>(108));
		skill_creators.push_back(std::make_unique<SimpleEntityCreator<ISkill, Woodcutter>>(109));
		skill_creators.push_back(std::make_unique<SimpleEntityCreator<ISkill, Digger>>(110));
		skill_creators.push_back(std::make_unique<SimpleEntityCreator<ISkill, Pyromaniac>>(111));
		skill_creators.push_back(std::make_unique<SimpleEntityCreator<ISkill, Bard>>(112));
		skill_creators.push_back(std::make_unique<SimpleEntityCreator<ISkill, Troll>>(113));
		skill_creators.push_back(std::make_unique<SimpleEntityCreator<ISkill, Warlock>>(114));
		skill_creators.push_back(std::make_unique<SimpleEntityCreator<ISkill, Clown>>(115));

		create_skill_encyclopedia();
		create_quest_types_encyclopedia();
	}

	std::unique_ptr<ISkill> get_random_skill()
	{
		for (auto && entity_creator_base : skill_creators)
		{
			skills.emplace_back(entity_creator_base->create_entity());
		}
		throw("Encyclopedia Keeper does not contain fallback type in collection of creators.");
	}
	const std::vector<std::unique_ptr<ISkill>>& get_skills() const { return skills; }
	const std::unordered_set<QuestTypeWrapper>& get_quest_types() const { return quest_types; }
protected:
	void create_skill_encyclopedia()
	{
		for (auto&& entity_creator_base : skill_creators)
		{
			skills.emplace_back(entity_creator_base->create_entity());
		}
	}
	void create_quest_types_encyclopedia()
	{
		quest_types.insert(QuestTypeWrapper(QuestType::Minions, "Minions", "Multiple enemies."));
		quest_types.insert(QuestTypeWrapper(QuestType::Boss, "Boss", "Big guy."));
		quest_types.insert(QuestTypeWrapper(QuestType::Poison, "Poison", "Danger of poison is guaranteed."));
		quest_types.insert(QuestTypeWrapper(QuestType::Bleeding, "Bleeding", "You will bleed out quite fast."));
		quest_types.insert(QuestTypeWrapper(QuestType::Curse, "Curse", "You will end harmed on this quest in many ways."));
		quest_types.insert(QuestTypeWrapper(QuestType::Elfs, "Elfs", "See dwarfs."));
		quest_types.insert(QuestTypeWrapper(QuestType::Dwarfs, "Dwarfs", "See elfs."));
		quest_types.insert(QuestTypeWrapper(QuestType::Fairies, "Fairies", "Little jokers."));
		quest_types.insert(QuestTypeWrapper(QuestType::Magical, "Magical", "Atla is alive."));
		quest_types.insert(QuestTypeWrapper(QuestType::Darkness, "Darkness", "Why did you not bring torch ?"));
		quest_types.insert(QuestTypeWrapper(QuestType::Wilderness, "Wilderness", "Location is filled with primordial beings."));
		quest_types.insert(QuestTypeWrapper(QuestType::Dankness, "Dankness", "Dank."));
		quest_types.insert(QuestTypeWrapper(QuestType::Memes, "Memes", "Dark side of internet."));
		quest_types.insert(QuestTypeWrapper(QuestType::Mimes, "Mimes", "Annoying."));
	}
private:
	std::vector<std::unique_ptr<EntityCreatorBase<ISkill>>> skill_creators;
	std::vector<std::unique_ptr<ISkill>> skills;
	std::unordered_set<QuestTypeWrapper> quest_types;
};

class AdventurerKeeper
{
public:
	std::unique_ptr<Adventurer> create_adventurer()
	{
		auto&& adventurer = std::make_unique<Adventurer>(name_generator.create_person_name());
		adventurer->set_recruitment_cost(50);
		adventurer->set_retirement_cost(10);
		adventurer->set_living_expenses(50);
		adventurer->set_skills(std::make_unique<PerfectHero>(999));
		adventurer->set_skills(std::make_unique<MisterHandsome>(998));
		adventurer->set_skills(std::make_unique<EscapeArtist>(997));
		adventurer->set_skills(std::make_unique<Hoarder>(996));
		adventurer->set_skills(std::make_unique<Cleave>(995));
		adventurer->set_skills(std::make_unique<PerfectHero>(994));

		return std::move(adventurer);
	}
	void generate(int count)
	{
		for (int i = 0; i < count; ++i)
		{
			available.push_back(create_adventurer());
		}
	}
	void clear()
	{
		available.clear();
		hired.clear();
		dead.clear();
		inactive.clear();
	}
	bool recruit(int adventurer_id)
	{
		return CollectionIterators::transfer(available, hired, adventurer_id);
	}
	bool pension(int adventurer_id)
	{
		return CollectionIterators::transfer(hired, inactive, adventurer_id);
	}
	bool kill(int adventurer_id)
	{
		return CollectionIterators::transfer(hired, dead, adventurer_id);
	}
	const adventurer_collection& get_hired() { return hired; }
	const adventurer_collection& get_available() { return available; }
	const adventurer_collection& get_dead() { return dead; }
	const adventurer_collection& get_inactive() { return inactive; }
private:
	adventurer_collection available;
	adventurer_collection hired;
	adventurer_collection dead;
	adventurer_collection inactive;
	NameGenerator name_generator;
};

class QuestKeeper
{
public:
	std::unique_ptr<Quest> create_quest()
	{
		auto&& quest = std::make_unique<Quest>(name_generator.create_quest_name());
		quest->get_reward().set_gold(100);
		quest->get_reward().set_fame(10);
		quest->get_penalty().set_gold(100);
		quest->get_penalty().set_fame(10);
		quest->set_difficulty(2);
		quest->set_quest_types(QuestType::Boss);
		quest->set_quest_types(QuestType::Minions);
		quest->set_quest_types(QuestType::Elfs);
		return std::move(quest);
	}
	void generate(int count)
	{
		for (int i = 0; i < count; ++i)
		{
			available.push_back(create_quest());
		}
	}
	void clear()
	{
		available.clear();
		reserved.clear();
		completed.clear();
		failed.clear();
	}
	bool take(int quest_id)
	{
		return CollectionIterators::transfer(available, reserved, quest_id);
	}
	bool complete(int quest_id)
	{
		return CollectionIterators::transfer(reserved, completed, quest_id);
	}
	bool fail(int quest_id)
	{
		return CollectionIterators::transfer(reserved, failed, quest_id);
	}

	const quest_collection& get_available() { return available; }
	const quest_collection& get_reserved() { return reserved; }
	const quest_collection& get_completed() { return completed; }
	const quest_collection& get_failed() { return failed; }
private:
	quest_collection available;
	quest_collection reserved;
	quest_collection completed;
	quest_collection failed;
	NameGenerator name_generator;
};

class Guild : public NamedUniqueEntity
{
public:
	Guild() : NamedUniqueEntity("My Guild") {}
	int get_gold() const { return gold; }
	int set_gold(int value) { gold = value; return gold; }
	int add_gold(int value) { gold += value; return gold; }
	int rmv_gold(int value) { gold -= value; return gold; }
	int get_fame() const { return fame; }
	int set_fame(int value) { fame = value; return fame; }
	int add_fame(int value) { fame += value; return fame; }
	int rmv_fame(int value) { fame -= value; return fame; }
	int get_diff() const { return diff; }
	int set_diff(int value) { diff = value; return diff; }
	void clear()
	{
		set_name("My Guild");
		set_gold(0);
		set_fame(0);
		set_diff(0);
	}
private:
	int gold = 0;
	int fame = 0;
	int diff = 0;
};

class GameState
{
public:
	//std::string get_name() const { return name; }
	//std::string set_name(std::string value) { name = value; return name; }
	bool is_exit_requested() const { return exit_requested; }
	bool request_exit(bool value) { exit_requested = value; return exit_requested; }
	bool get_progress_state() const { return is_progressing; }
	bool change_progress_state(bool value) { is_progressing = value; return is_progressing; }
	void clear()
	{
		//set_name("");
		request_exit(false);
		change_progress_state(false);
	}
private:
	//std::string name = "";
	bool exit_requested = false;
	bool is_progressing = false;
};

class GameData
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
		adventurers.generate(5);
		quests.generate(10);
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
				adventurer->add_experience(calculate_experience(quest->get_difficulty(), adventurer->get_level()));
				
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
					adventurer->rmv_experience(calculate_experience(quest->get_difficulty(), adventurer->get_level()));
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



#endif