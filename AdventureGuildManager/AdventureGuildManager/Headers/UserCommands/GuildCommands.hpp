#ifndef GUILD_COMMANDS_HPP
#define GUILD_COMMANDS_HPP

#include "../UserInterfaces/GuildInterfaces.hpp"
#include "../UserInterfaces/InputInterfaces.hpp"

class GuildCommand : public ICommand
{
public:
	GuildCommand(string_context& command_context) : ICommand(command_context) { }
	~GuildCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 1 && (command_context[0] == "guild" || command_context[0] == "g");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		return interface.display_default();
	}
private:
	GuildInterfaces interface;
};

class GuildInfoCommand : public ICommand
{
public:
	GuildInfoCommand(string_context& command_context) : ICommand(command_context) { }
	~GuildInfoCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "guild" || command_context[0] == "g")
			&& (command_context[1] == "info" || command_context[1] == "-i");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		return interface.display_informations(game_data_manager);
	}
private:
	GuildInterfaces interface;
};


class GuildRenameCommand : public ICommand
{
public:
	GuildRenameCommand(string_context& command_context) : ICommand(command_context) { }
	~GuildRenameCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& (command_context[0] == "guild" || command_context[0] == "g")
			&& (command_context[1] == "rename" || command_context[1] == "-r");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		std::string name = context.size() >= 3
			? StringContext::merge(context, 2, " ")
			: interface.get_name();
		if (game_data_manager.rename_guild(name))
		{
			return interface.display_informations(game_data_manager);
		}
		return interface.display_no_rename(name);
	}
private:
	GuildInterfaces interface;
};

class GuildWaitCommand : public ICommand
{
public:
	GuildWaitCommand(string_context& command_context) : ICommand(command_context) { }
	~GuildWaitCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "guild" || command_context[0] == "g")
			&& (command_context[1] == "wait" || command_context[1] == "-w");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		game_data_manager.wait_turn();
		return interface.display_wait(game_data_manager);
	}
private:
	GuildInterfaces interface;
};


#endif