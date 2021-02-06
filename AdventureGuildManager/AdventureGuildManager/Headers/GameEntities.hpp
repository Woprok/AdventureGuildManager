#ifndef GAME_ENTITIES_HPP
#define GAME_ENTITIES_HPP

#include <string>
#include <unordered_set>

#include "ConsoleHelpers.hpp"
#include "Generators.hpp"

enum class QuestStateEnum
{
	Success,
	Failure,
	Undefined
};

class NamedEntity
{
public:
	NamedEntity(std::string entity_name) : name(entity_name), id(last_id++) {}
	std::string get_name() const { return name; }
	std::string set_name(std::string value) { name = value; return name; }
	int get_id() const { return id; }
protected:
	std::string name = "Entity";
	int id;
	inline static int last_id = 0;
};

class Adventurer : public NamedEntity
{
public:
	Adventurer(std::string adventurer_name) : NamedEntity(adventurer_name) {}
	std::unordered_set<int>& get_succ_quest_ids() { return succ_quest_ids; }
	std::unordered_set<int>& set_succ_quest_id(int value) { succ_quest_ids.emplace(value); return succ_quest_ids; }
	std::unordered_set<int>& get_fail_quest_ids() { return fail_quest_ids; }
	std::unordered_set<int>& set_fail_quest_id(int value) { fail_quest_ids.emplace(value); return fail_quest_ids; }
	int get_recruitment_cost() const { return recruitment_cost; }
	int set_recruitment_cost(int value) { recruitment_cost = value; return recruitment_cost; }
	int get_retirement_cost() const { return retirement_cost; }
	int set_retirement_cost(int value) { retirement_cost = value; return retirement_cost; }
	int get_living_expenses() const { return living_expenses; }
	int set_living_expenses(int value) { living_expenses = value; return living_expenses; }
private:
	std::unordered_set<int> succ_quest_ids;
	std::unordered_set<int> fail_quest_ids;
	int recruitment_cost = 0;
	int retirement_cost = 0;
	int living_expenses = 0;
};

class Reward
{
public:
	int get_gold() const { return gold; }
	int set_gold(int value) { gold = value; return gold; }
	int get_fame() const { return fame; }
	int set_fame(int value) { fame = value; return fame; }
private:
	int gold = 0;
	int fame = 0;
};

class  Penalty
{
public:
	int get_gold() const { return gold; }
	int set_gold(int value) { gold = value; return gold; }
	int get_fame() const { return fame; }
	int set_fame(int value) { fame = value; return fame; }
	bool get_deadly() const { return deadly; }
	bool set_deadly(bool value) { deadly = value; return deadly; }
private:
	int gold = 0;
	int fame = 0;
	bool deadly = true;
};

class Quest : public NamedEntity
{
public:
	Quest(std::string quest_name) : NamedEntity(quest_name) {}
	Reward& get_reward() { return reward; }
	Penalty& get_penalty() { return penalty; }
	int get_adventurer_id() const { return adventurer_id; }
	int set_adventurer_id(int value) { adventurer_id = value; return adventurer_id; }
	QuestStateEnum get_state() const { return state; }
	QuestStateEnum set_state(QuestStateEnum value) { state = value; return state; }
private:
	Reward reward;
	Penalty penalty;
	QuestStateEnum state = QuestStateEnum::Undefined;
	int adventurer_id = - 1;
};

typedef std::vector<std::unique_ptr<Adventurer>> adventurer_collection;
typedef std::vector<std::unique_ptr<Quest>> quest_collection;

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

class AdventurerKeeper
{
public:
	std::unique_ptr<Adventurer> create_adventurer()
	{
		auto&& adventurer = std::make_unique<Adventurer>(name_generator.create_person_name());
		adventurer->set_recruitment_cost(50);
		adventurer->set_retirement_cost(10);
		adventurer->set_living_expenses(50);
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

class Guild : public NamedEntity
{
public:
	Guild() : NamedEntity("My Guild") {}
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
		current_guild.set_gold(100);
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
		if (adventurer != nullptr && current_guild.get_gold() >= adventurer->get_retirement_cost())
		{
			// Substract retirement cost
			current_guild.rmv_gold(adventurer->get_retirement_cost());
			// Pension
			return adventurers.pension(adventurer_id);
		}
		return false;
	}
	inline bool recruit(int adventurer_id)
	{
		const auto adventurer = CollectionIterators::find(adventurers.get_available(), adventurer_id);
		if (adventurer != nullptr && current_guild.get_gold() >= adventurer->get_recruitment_cost())
		{
			// Substract recruitment cost
			current_guild.rmv_gold(adventurer->get_recruitment_cost());
			// Recruit
			return adventurers.recruit(adventurer_id);
		}
		return false;
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
			if (chance_generator.get_chance() >= compare_value)
			{
				// Get Reward
				current_guild.add_gold(quest->get_reward().get_gold());
				current_guild.add_fame(quest->get_reward().get_fame());
				
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
				current_guild.rmv_gold(quest->get_penalty().get_gold());
				current_guild.rmv_fame(quest->get_penalty().get_fame());
				if (quest->get_penalty().get_deadly())
				{
					adventurers.kill(adventurer_id);					
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