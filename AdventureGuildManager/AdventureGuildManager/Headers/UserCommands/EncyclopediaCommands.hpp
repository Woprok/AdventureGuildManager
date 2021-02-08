#ifndef ENCYCLOPEDIA_COMMANDS_HPP
#define ENCYCLOPEDIA_COMMANDS_HPP

class EncyclopediaCommand : public ICommand
{
public:
	EncyclopediaCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 1
			&& (command_context[0] == "encyclopedia" || command_context[0] == "e");
	}
	std::string execute(GameData& game_data) override
	{
		return interface.to_string();
	}
private:
	EncyclopediaInterface interface;
};

class EncyclopediaSkillTypessCommand : public ICommand
{
public:
	EncyclopediaSkillTypessCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "encyclopedia" || command_context[0] == "e")
			&& (command_context[1] == "skills" || command_context[1] == "-s");
	}
	std::string execute(GameData& game_data) override
	{
		return interface.wiki_skill_types(game_data.encyclopedia);
	}
private:
	EncyclopediaInterface interface;
};

class EncyclopediaQuestTypesCommand : public ICommand
{
public:
	EncyclopediaQuestTypesCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "encyclopedia" || command_context[0] == "e")
			&& (command_context[1] == "quest_types" || command_context[1] == "-q");
	}
	std::string execute(GameData& game_data) override
	{
		return interface.wiki_quest_types(game_data.encyclopedia);
	}
private:
	EncyclopediaInterface interface;
};

#endif