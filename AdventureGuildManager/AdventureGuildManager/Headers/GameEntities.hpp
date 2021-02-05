#ifndef GAME_ENTITIES_HPP
#define GAME_ENTITIES_HPP

#include <string>
#include "ConsoleHelpers.hpp"
#include "Generators.hpp"

class NamedEntity
{
public:
	NamedEntity(std::string entity_name) : name(entity_name) {}
	std::string get_name() const { return name; }
	std::string set_name(std::string value) { name = value; return name; }
protected:
	std::string name = "Entity";
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
	const std::vector<std::unique_ptr<Adventurer>>& get_hired() { return hired; }
	const std::vector<std::unique_ptr<Adventurer>>& get_available() { return available; }
private:
	std::vector<std::unique_ptr<Adventurer>> available;
	std::vector<std::unique_ptr<Adventurer>> hired;
	NameGenerator name_generator;
};

class QuestKeeper
{
public:
	void generate(int count)
	{
		for (int i = 0; i < count; ++i)
		{
			available.push_back(std::make_unique<Quest>(name_generator.create_quest_name()));
		}
	}
	void clear()
	{
		available.clear();
		accepted.clear();
	}
	const std::vector<std::unique_ptr<Quest>>& get_accepted() { return accepted; }
	const std::vector<std::unique_ptr<Quest>>& get_available() { return available; }
private:
	std::vector<std::unique_ptr<Quest>> available;
	std::vector<std::unique_ptr<Quest>> accepted;
	NameGenerator name_generator;
};

class Guild : public NamedEntity
{
public:
	Guild() : NamedEntity("My Guild") {}
	int get_gold() const { return gold; }
	int set_gold(int value) { gold = value; return gold; }
	int get_fame() const { return fame; }
	int set_fame(int value) { fame = value; return fame; }
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
		if (new_name.empty())
		{
			new_name = ConsoleHelpers::read_line();
		}
		current_guild.set_name(new_name);
	}
private:
};



#endif