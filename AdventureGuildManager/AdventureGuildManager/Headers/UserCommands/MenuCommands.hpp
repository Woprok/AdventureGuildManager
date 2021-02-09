#ifndef MENU_COMMANDS_HPP
#define MENU_COMMANDS_HPP

#include "../GameDataManagers.hpp"
#include "../Interfaces/ICommands.hpp"
#include "../UserInterfaces/MenuInterfaces.hpp"

class MenuCommand final : public ICommand
{
public:
	MenuCommand(string_context& command_context) : ICommand(command_context) { }
	~MenuCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 1
			&& (command_context[0] == "menu" || command_context[0] == "m");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		if (game_data_manager.game_state->get_progress_state())
			return interface.display_in_progress();
		return interface.display_no_progress();
	}
private:
	MenuInterfaces interface;
};

class MenuStartCommand final : public ICommand
{
public:
	MenuStartCommand(string_context& command_context) : ICommand(command_context) { }
	~MenuStartCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "menu" || command_context[0] == "m")
			&& (command_context[1] == "start" || command_context[1] == "-s");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		if (!game_data_manager.game_state->get_progress_state())
		{
			game_data_manager.start_game();
			return interface.display_start();
		}
		return interface.display_in_progress();
	}
private:
	MenuInterfaces interface;
};

class MenuEndCommand final : public ICommand
{
public:
	MenuEndCommand(string_context& command_context) : ICommand(command_context) { }
	~MenuEndCommand() override = default;

	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "menu" || command_context[0] == "m")
			&& (command_context[1] == "end" || command_context[1] == "-e");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		if (game_data_manager.game_state->get_progress_state())
		{
			game_data_manager.end_game();
			return interface.display_end();
		}
		return interface.display_no_progress();
	}
private:
	MenuInterfaces interface;
};

class MenuDifficultyCommand : public ICommand
{
public:
	MenuDifficultyCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& (command_context[0] == "menu" || command_context[0] == "m")
			&& (command_context[1] == "difficulty" || command_context[1] == "-d");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		if (!game_data_manager.game_state->get_progress_state())
		{
			const int new_difficulty = interface.get_difficulty_value(context.size() == 3 ? context[2] : "");
			new_difficulty = game_data_manager.change_difficulty(new_difficulty);
			return interface.display_difficulty(new_difficulty);
		}
		return interface.display_in_progress();
	}
private:
	MenuInterfaces interface;
};

#endif