#ifndef ERROR_COMMANDS_HPP
#define ERROR_COMMANDS_HPP

#include <string>

#include "../GameDataManagers.hpp"
#include "../Interfaces/ICommands.hpp"
#include "../UserInterfaces/ErrorInterfaces.hpp"
#include "../Helpers/StringContexts.hpp"

class ErrorCommand final : public ICommand
{
public:
	ErrorCommand(string_context& command_context) : ICommand(command_context) {}
	~ErrorCommand() override = default;
	static bool can_derive_from([[maybe_unused]] string_context& command_context) { return true; }
	std::string execute([[maybe_unused]] GameDataManager& game_data_manager) override
	{
		return interface.display_error(context);
	}
private:
	ErrorInterfaces interface;
};

#endif