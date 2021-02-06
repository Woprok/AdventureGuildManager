#ifndef GAME_MANAGERS_HPP
#define GAME_MANAGERS_HPP

#include "../Headers/Interfaces.hpp"
#include "../Headers/ConsoleHelpers.hpp"
#include "../Headers/ConsoleProcessors.hpp"
#include "../Headers/Commands.hpp"

class CommandManager
{
public:
	CommandManager()
	{
		// Generic
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, MenuCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, MenuRestartCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, HelpCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, ExitCommand>>());

		// Guild
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, GuildCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, GuildInfoCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, GuildCreateCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, GuildDifficultyCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, GuildRenameCommand>>());
		
		// Adventurer
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, AdventurerCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, AdventurerAvailableCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, AdventurerHiredCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, AdventurerDeadCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, AdventurerInactiveCommand>>());
		// Adventurer Actions
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, AdventurerRecruitCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, AdventurerPensionCommand>>());
		
		// Quest
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, QuestCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, QuestAvailableCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, QuestReserverCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, QuestCompletedCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, QuestFailedCommand>>());
		// Quest Actions
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, QuestTakeCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, QuestDispatchCommand>>());

		// Fallback, should be kept last while we keep them in the list
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, ErrorCommand>>());
	}

	std::unique_ptr<ICommand> create_command(std::vector<std::string>& command_body)
	{
		for (auto && command_creator : command_creators)
		{
			if (command_creator->can_create_from(command_body))
				return command_creator->create_entity(command_body);
		}
		throw("Command Manager does not contain fallback type in collection of creators.");
	}
private:
	std::vector<std::unique_ptr<CreatorBase<ICommand>>> command_creators;
};

class GameManager
{
public:
	void force_menu()
	{
		std::vector<std::string> body  { "menu" };
		auto menu = command_manager.create_command(body);
		ConsoleProcessors::clean_and_print(menu->execute(game_data));
	}
	
	void run_game()
	{
		while (!game_data.game_state.is_exit_requested())
		{
			auto cmd = ConsoleProcessors::get_next_command();
			ConsoleProcessors::print_debug(cmd);
			auto cmd_cmd = command_manager.create_command(cmd);
			auto rs = cmd_cmd->execute(game_data);
			ConsoleProcessors::print_interface(rs);
		}
	}
private:
	CommandManager command_manager;
	GameData game_data;
};

#endif