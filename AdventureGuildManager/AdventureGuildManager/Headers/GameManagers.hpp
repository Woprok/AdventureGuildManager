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
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, MenuCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, HelpCommand>>());
		command_creators.push_back(std::make_unique<ContextEntityCreator<ICommand, ExitCommand>>());
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
	const inline bool can_continue() const { return true; }

	void force_menu()
	{
		std::vector<std::string> body  { "menu" };
		auto menu = command_manager.create_command(body);
		ConsoleProcessors::clean_and_print(menu->execute());
	}
	
	void run_game()
	{
		while (can_continue())
		{
			auto cmd = ConsoleProcessors::get_next_command();
			ConsoleProcessors::print_debug(cmd);
			auto cmd_cmd = command_manager.create_command(cmd);
			auto rs = cmd_cmd->execute();
			ConsoleProcessors::print_interface(rs);
		}





		
		//auto creators = generic_creator<ICommand, IHelpCommand>();
		//generic_creator<ICommand, IHelpCommand>* pointer = &creators;
		//creator<ICommand>* ptr = pointer;

		//bool std = ptr->is_createable_from("null");
		//std::cout << std;


	}
private:
	CommandManager command_manager;
};

#endif