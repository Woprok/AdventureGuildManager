#ifndef ENCYCLOPEDIA_COMMANDS_HPP
#define ENCYCLOPEDIA_COMMANDS_HPP

#include "../Interfaces/ICommands.hpp"
#include "../UserInterfaces/EncyclopediaInterfaces.hpp"

class EncyclopediaCommand : public ICommand
{
public:
	EncyclopediaCommand(string_context& command_context) : ICommand(command_context) { }
	~EncyclopediaCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 1
			&& (command_context[0] == "encyclopedia" || command_context[0] == "e");
	}
	std::string execute(GameDataManager& game_data) override
	{
		return interface.display_default();
	}
private:
	EncyclopediaInterfaces interface;
};

class EncyclopediaQuestTypesCommand : public ICommand
{
public:
	EncyclopediaQuestTypesCommand(string_context& command_context) : ICommand(command_context) { }
	~EncyclopediaQuestTypesCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "encyclopedia" || command_context[0] == "e")
			&& (command_context[1] == "quest_types" || command_context[1] == "-qt");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		return interface.display_quest_types(game_data_manager);
	}
private:
	EncyclopediaInterfaces interface;
};

class EncyclopediaQuestRaritiesCommand : public ICommand
{
public:
	EncyclopediaQuestRaritiesCommand(string_context& command_context) : ICommand(command_context) { }
	~EncyclopediaQuestRaritiesCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "encyclopedia" || command_context[0] == "e")
			&& (command_context[1] == "quest_rarities" || command_context[1] == "-qr");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		return interface.display_quest_rarities(game_data_manager);
	}
private:
	EncyclopediaInterfaces interface;
};

class EncyclopediaAdventurerRaritiesCommand : public ICommand
{
public:
	EncyclopediaAdventurerRaritiesCommand(string_context& command_context) : ICommand(command_context) { }
	~EncyclopediaAdventurerRaritiesCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "encyclopedia" || command_context[0] == "e")
			&& (command_context[1] == "adventurer_rarities" || command_context[1] == "-ar");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		return interface.display_adventurer_rarities(game_data_manager);
	}
private:
	EncyclopediaInterfaces interface;
};

class EncyclopediaSkillsCommand : public ICommand
{
public:
	EncyclopediaSkillsCommand(string_context& command_context) : ICommand(command_context) { }
	~EncyclopediaSkillsCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "encyclopedia" || command_context[0] == "e")
			&& (command_context[1] == "skills" || command_context[1] == "-s");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		return interface.display_skills(game_data_manager);
	}
private:
	EncyclopediaInterfaces interface;
};

class EncyclopediaPerksCommand : public ICommand
{
public:
	EncyclopediaPerksCommand(string_context& command_context) : ICommand(command_context) { }
	~EncyclopediaPerksCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "encyclopedia" || command_context[0] == "e")
			&& (command_context[1] == "perks" || command_context[1] == "-p");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		return interface.display_perks(game_data_manager);
	}
private:
	EncyclopediaInterfaces interface;
};

#endif