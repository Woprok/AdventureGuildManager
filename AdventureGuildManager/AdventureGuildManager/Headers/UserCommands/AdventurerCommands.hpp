#ifndef ADVENTURER_COMMANDS_HPP
#define ADVENTURER_COMMANDS_HPP

#include "../UserInterfaces/AdventurerInterfaces.hpp"
#include "../Interfaces/ICommands.hpp"

class AdventurerCommand : public ICommand
{
public:
	AdventurerCommand(string_context& command_context) : ICommand(command_context) { }
	~AdventurerCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 1
			&& (command_context[0] == "adventurer" || command_context[0] == "a");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		return interface.display_default();
	}
private:
	AdventurerInterfaces interface;
};

class AdventurerAvailableCommand : public ICommand
{
public:
	AdventurerAvailableCommand(string_context& command_context) : ICommand(command_context) { }
	~AdventurerAvailableCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "adventurer" || command_context[0] == "a")
			&& (command_context[1] == "available" || command_context[1] == "-a");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		return interface.display_available(game_data_manager);
	}
private:
	AdventurerInterfaces interface;
};

class AdventurerHiredCommand : public ICommand
{
public:
	AdventurerHiredCommand(string_context& command_context) : ICommand(command_context) { }
	~AdventurerHiredCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "adventurer" || command_context[0] == "a")
			&& (command_context[1] == "hired" || command_context[1] == "-h");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		return interface.display_hired(game_data_manager);
	}
private:
	AdventurerInterfaces interface;
};

class AdventurerDeadCommand : public ICommand
{
public:
	AdventurerDeadCommand(string_context& command_context) : ICommand(command_context) { }
	~AdventurerDeadCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "adventurer" || command_context[0] == "a")
			&& (command_context[1] == "dead" || command_context[1] == "-d");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		return interface.display_dead(game_data_manager);
	}
private:
	AdventurerInterfaces interface;
};

class AdventurerInactiveCommand : public ICommand
{
public:
	AdventurerInactiveCommand(string_context& command_context) : ICommand(command_context) { }
	~AdventurerInactiveCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "adventurer" || command_context[0] == "a")
			&& (command_context[1] == "inactive" || command_context[1] == "-i");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		return interface.display_inactive(game_data_manager);
	}
private:
	AdventurerInterfaces interface;
};

class AdventurerRecruitCommand : public ICommand
{
public:
	AdventurerRecruitCommand(string_context& command_context) : ICommand(command_context) { }
	~AdventurerRecruitCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& (command_context[0] == "adventurer" || command_context[0] == "a")
			&& (command_context[1] == "recruit" || command_context[1] == "-r");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		const int adventurer_id = interface.get_adventurer_id_value(context.size() >= 3 ? context[2] : "");

		if (game_data_manager.hire_adventurer(adventurer_id))
		{
			return interface.display_adventurer_hired(game_data_manager, adventurer_id);
		}

		return interface.display_adventurer_action_failed(adventurer_id);
	}
private:
	AdventurerInterfaces interface;
};

class AdventurerPensionCommand : public ICommand
{
public:
	AdventurerPensionCommand(string_context& command_context) : ICommand(command_context) { }
	~AdventurerPensionCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& (command_context[0] == "adventurer" || command_context[0] == "a")
			&& (command_context[1] == "pension" || command_context[1] == "-p");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		const int adventurer_id = interface.get_adventurer_id_value(context.size() >= 3 ? context[2] : "");

		if (game_data_manager.pension_adventurer(adventurer_id))
		{
			return interface.display_adventurer_retired(game_data_manager, adventurer_id);
		}

		return interface.display_adventurer_action_failed(adventurer_id);
	}
private:
	AdventurerInterfaces interface;
};

#endif