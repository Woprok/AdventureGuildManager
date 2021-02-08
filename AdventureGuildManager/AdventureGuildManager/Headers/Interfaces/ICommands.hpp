#ifndef I_COMMANDS_HPP
#define I_COMMANDS_HPP

#include <string>
#include <vector>

#include "../GameDataManagers.hpp"
#include "../Helpers/StringContexts.hpp"

class ICommand
{
public:
	ICommand(string_context& command_context) : context(command_context) { }
	virtual ~ICommand() = default;
	/// <summary>
	/// Test if command_context is body without parameters for this command.
	/// </summary>
	/// <returns>True or False</returns>
	static bool can_derive_from(string_context& command_context) { return false; }
	/// <summary>
	/// Runs command over real data, verifies parameters of command.
	/// </summary>
	virtual std::string execute(GameDataManager& game_data_manager) = 0;
protected:
	string_context context;
};

#endif