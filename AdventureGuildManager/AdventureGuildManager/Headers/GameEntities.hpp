#ifndef GAME_ENTITIES_HPP
#define GAME_ENTITIES_HPP

#include <string>
#include "ConsoleHelpers.hpp"
#include "Generators.hpp"

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
};

class Quest : public NamedEntity
{
public:
	Quest(std::string quest_name) : NamedEntity(quest_name) {}
	int get_gold() const { return gold; }
	int set_gold(int value) { gold = value; return gold; }
	int get_fame() const { return fame; }
	int set_fame(int value) { fame = value; return fame; }
private:
	int gold = 0;
	int fame = 0;
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
	void generate(int count)
	{
		for (int i = 0; i < count; ++i)
		{
			available.push_back(std::make_unique<Adventurer>(name_generator.create_person_name()));
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
	const adventurer_collection& get_hired() { return hired; }
	const adventurer_collection& get_available() { return available; }
private:
	adventurer_collection available;
	adventurer_collection hired;
	NameGenerator name_generator;
};

class QuestKeeper
{
public:
	std::unique_ptr<Quest> create_quest()
	{
		auto&& quest = std::make_unique<Quest>(name_generator.create_quest_name());
		quest->set_gold(100);
		quest->set_fame(10);
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

	const quest_collection& get_available() { return available; }
	const quest_collection& get_reserved() { return reserved; }
	const quest_collection& get_completed() { return completed; }
private:
	quest_collection available;
	quest_collection reserved;
	quest_collection completed;
	NameGenerator name_generator;
};

class Guild : public NamedEntity
{
public:
	Guild() : NamedEntity("My Guild") {}
	int get_gold() const { return gold; }
	int set_gold(int value) { gold = value; return gold; }
	int add_gold(int value) { gold += value; return gold; }
	int get_fame() const { return fame; }
	int set_fame(int value) { fame = value; return fame; }
	int add_fame(int value) { fame += value; return fame; }
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
		quests.generate(3);
	}
	inline void rename_guild(std::string new_name)
	{
		current_guild.set_name(new_name);
	}
	inline bool dispatch(int adventurer_id, int quest_id)
	{
		const auto adventurer = CollectionIterators::find(adventurers.get_hired(), adventurer_id);
		const auto quest = CollectionIterators::find(quests.get_reserved(), quest_id);
		if (adventurer != nullptr && quest != nullptr)
		{
			current_guild.add_gold(quest->get_gold());
			current_guild.add_fame(quest->get_fame());
			
			quests.complete(quest_id);
			return true;
		}
		else
		{
			return false;
		}
	}
private:
};



#endif