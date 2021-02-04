#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <memory>
#include <algorithm>
#include <numeric>
#include <vector>
#include "Interfaces.hpp"
#include "GameEntities.hpp"

typedef std::vector<std::string> string_context;

template<class TInterface>
class CreatorBase
{
public:
	virtual ~CreatorBase() = default;
	virtual bool can_create_from(string_context& creation_context) = 0;
	virtual std::unique_ptr<TInterface> create_entity(string_context& creation_context) = 0;
};

template<class TInterface, class TCreatable>
class ContextEntityCreator : public CreatorBase<TInterface>
{
	static_assert(std::is_base_of<TInterface, TCreatable>::value, "TCreatable must be derived from TInterface");
public:
	bool can_create_from(string_context& creation_context) override
	{
		return TCreatable::can_derive_from(creation_context);
	}
	std::unique_ptr<TInterface> create_entity(string_context& creation_context) override
	{
		return std::make_unique<TCreatable>(creation_context);
	}
};

class ICommand
{
public:
	ICommand(string_context& command_context) : context(std::move(command_context)) { }
	virtual ~ICommand() = default;
	/// <summary>
	/// Test if command_context is body without parameters for this command
	/// </summary>
	/// <returns>True or False</returns>
	static bool can_derive_from(string_context& command_context) { return false; }
	/// <summary>
	/// Runs command over real data, verifies parameters of command
	/// </summary>
	virtual std::string execute(GameData& game_data) = 0;
protected:
	string_context context;
};

#pragma region Commands
class MenuCommand : public ICommand
{
public:
	MenuCommand(string_context& command_context) : ICommand(command_context) { }

	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 1 && command_context[0] == "menu";
	}
	std::string execute(GameData& game_data) override
	{
		if (game_data.game_state.get_progress_state())
			return interface.in_progress();
		return interface.to_string();
	}
private:
	MenuInterface interface;
};

class MenuRestartCommand : public ICommand
{
public:
	MenuRestartCommand(string_context& command_context) : ICommand(command_context) { }

	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
		&& command_context[0] == "menu"
		&& command_context[1] == "restart";
	}
	std::string execute(GameData& game_data) override
	{
		if (game_data.game_state.get_progress_state())
		{
			game_data.clear_game_state();
			return interface.show_restart();
		}
		return interface.no_progress();
	}
private:
	MenuInterface interface;
};

class HelpCommand : public ICommand
{
public:
	HelpCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 1 && command_context[0] == "help";
	}
	std::string execute(GameData& game_data) override
	{
		return interface.to_string();
	}
private:
	HelpInterface interface;
};

class ExitCommand : public ICommand
{
public:
	ExitCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 1 && command_context[0] == "exit";
	}
	std::string execute(GameData& game_data) override
	{
		game_data.game_state.request_exit(true);
		return interface.to_string();
	}
private:
	ExitInterface interface;
};

class ErrorCommand : public ICommand
{
public:
	ErrorCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context) { return true; }
	std::string execute(GameData& game_data) override
	{
		return interface.to_string(context);
	}
private:
	ErrorInterface interface;
};

class GuildCommand : public ICommand
{
public:
	GuildCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 1 && command_context[0] == "guild";
	}
	std::string execute(GameData& game_data) override
	{
		return interface.to_string();
	}
private:
	GuildInterface interface;
};

class GuildCreateCommand : public ICommand
{
public:
	GuildCreateCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& command_context[0] == "guild"
			&& command_context[1] == "create";
	}
	std::string execute(GameData& game_data) override
	{
		if (game_data.game_state.get_progress_state())
			return interface.game_in_progress();
		game_data.create_game();
		return interface.to_string(game_data.current_guild);
	}
private:
	GuildInterface interface;
};

class GuildRenameCommand : public ICommand
{
public:
	GuildRenameCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& command_context[0] == "guild"
			&& command_context[1] == "rename";
	}
	std::string execute(GameData& game_data) override
	{
		std::string name;
		if (context.size() >= 3)
		{
			name = std::accumulate(context.begin() + 2, context.end(), name,
				[](std::string a, std::string b) { return a + " " + b; });
		}
		
		game_data.rename_guild(name);
		return interface.to_string(game_data.current_guild);
	}
private:
	GuildInterface interface;
};

class GuildDifficultyCommand : public ICommand
{
public:
	GuildDifficultyCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& command_context[0] == "guild"
			&& command_context[1] == "difficulty";
	}
	std::string execute(GameData& game_data) override
	{
		return interface.to_string(game_data.current_guild);
	}
private:
	GuildInterface interface;
};

#pragma endregion
#endif