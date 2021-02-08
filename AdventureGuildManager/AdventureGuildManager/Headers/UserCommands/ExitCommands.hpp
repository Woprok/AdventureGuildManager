#ifndef EXIT_COMMANDS_HPP
#define EXIT_COMMANDS_HPP

#include <string>

#include "../GameDataManagers.hpp"
#include "../Interfaces/ICommands.hpp"
#include "../UserInterfaces/ExitInterfaces.hpp"
#include "../Helpers/StringContexts.hpp"

class ExitCommand final : public ICommand
{
public:
	ExitCommand(string_context& command_context) : ICommand(command_context) {}
	~ExitCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 1
			&& command_context[0] == "exit";
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		game_data_manager.game_state->request_exit(true);
		
		return interfaces.display_exit(game_data_manager);
	}
private:
	ExitInterfaces interfaces;
};

#endif