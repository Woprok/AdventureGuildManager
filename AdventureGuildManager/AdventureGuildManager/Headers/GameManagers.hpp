#ifndef GAME_MANAGERS_HPP
#define GAME_MANAGERS_HPP

#include "Helpers/ConsoleProcessors.hpp"
#include "Helpers/EntityCreators.hpp"
#include "Interfaces/ICommands.hpp"
#include "UserCommands/DebugCommands.hpp"
#include "UserCommands/MenuCommands.hpp"
#include "UserCommands/HelpCommands.hpp"
#include "UserCommands/ExitCommands.hpp"
#include "UserCommands/GuildCommands.hpp"
#include "UserCommands/AdventurerCommands.hpp"
#include "UserCommands/QuestCommands.hpp"
#include "UserCommands/EncyclopediaCommands.hpp"
#include "UserCommands/PerkCommands.hpp"
#include "UserCommands/ErrorCommands.hpp"

class CommandManager
{
public:
	CommandManager()
	{
		// Debug Commands
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, DebugCommand>>());
		
		// Generic
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, MenuCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, MenuStartCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, MenuEndCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, MenuDifficultyCommand>>());

		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, HelpCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, ExitCommand>>());

		// Guild
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, GuildCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, GuildInfoCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, GuildRenameCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, GuildWaitCommand>>());
		
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
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, QuestReservedCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, QuestCompletedCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, QuestFailedCommand>>());
		
		// Quest Actions
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, QuestTakeCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, QuestDispatchCommand>>());

		// Encyclopedia
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, EncyclopediaCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, EncyclopediaQuestTypesCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, EncyclopediaQuestRaritiesCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, EncyclopediaAdventurerRaritiesCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, EncyclopediaSkillsCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, EncyclopediaPerksCommand>>());

		// Perks
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, PerkCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, PerkTradeFameCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, PerkRequalificationCourseCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, PerkArmoryCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, PerkChurchOfHeroesCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, PerkMadnessOfMasterCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, PerkBuyCommand>>());
		
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
	GameManager() = default;
	~GameManager() = default;
	GameManager(const GameManager&) = delete;
	GameManager& operator=(GameManager) = delete;
	void force_menu()
	{
		std::vector<std::string> body  { "menu", "start" };
		auto menu = command_manager.create_command(body);
		ConsoleProcessors::clean_and_print(menu->execute(game_data));
	}

	void force_win_screen()
	{
		std::ostringstream win_screen;
		
		win_screen << "****************************************\n";
		win_screen << "****************************************\n";
		win_screen << "****************************************\n";
		win_screen << "Your guild reached moon. Well not exactly, but you are most famous guild in world.\n";
		win_screen << "Well that's lie. You are only guild in world, there was no real competition to begin with.\n";
		win_screen << "****************************************\n";
		win_screen << "****************************************\n";
		win_screen << "****************************************\n";
		ConsoleProcessors::clean_and_print(win_screen.str());
	}

	void run_game()
	{
		while (!game_data.game_state->is_exit_requested())
		{
			auto cmd = ConsoleProcessors::get_next_command();
			ConsoleProcessors::print_debug(cmd);
			auto cmd_cmd = command_manager.create_command(cmd);
			auto rs = cmd_cmd->execute(game_data);
			ConsoleProcessors::print_interface(rs);

			if (game_data.win_condition())
			{
				force_win_screen();
			}
		}
	}
private:
	CommandManager command_manager;
	GameDataManager game_data;
};

#endif