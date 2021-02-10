#ifndef QUEST_COMMANDS_HPP
#define QUEST_COMMANDS_HPP

#include <string>

#include "../Interfaces/ICommands.hpp"

class QuestCommand : public ICommand
{
public:
	QuestCommand(string_context& command_context) : ICommand(command_context) { }
	~QuestCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 1
			&& (command_context[0] == "quest" || command_context[0] == "q");
	}
	std::string execute([[maybe_unused]] GameDataManager& game_data_manager) override
	{
		return interface.display_default();
	}
private:
	QuestInterfaces interface;
};

class QuestAvailableCommand : public ICommand
{
public:
	QuestAvailableCommand(string_context& command_context) : ICommand(command_context) { }
	~QuestAvailableCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "quest" || command_context[0] == "q")
			&& (command_context[1] == "available" || command_context[1] == "-a");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		return interface.display_available(game_data_manager);
	}
private:
	QuestInterfaces interface;
};

class QuestReservedCommand : public ICommand
{
public:
	QuestReservedCommand(string_context& command_context) : ICommand(command_context) { }
	~QuestReservedCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "quest" || command_context[0] == "q")
			&& (command_context[1] == "reserved" || command_context[1] == "-r");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		return interface.display_reserved(game_data_manager);
	}
private:
	QuestInterfaces interface;
};

class QuestCompletedCommand : public ICommand
{
public:
	QuestCompletedCommand(string_context& command_context) : ICommand(command_context) { }
	~QuestCompletedCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "quest" || command_context[0] == "q")
			&& (command_context[1] == "completed" || command_context[1] == "-c");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		return interface.display_completed(game_data_manager);
	}
private:
	QuestInterfaces interface;
};

class QuestFailedCommand : public ICommand
{
public:
	QuestFailedCommand(string_context& command_context) : ICommand(command_context) { }
	~QuestFailedCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "quest" || command_context[0] == "q")
			&& (command_context[1] == "failed" || command_context[1] == "-f");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		return interface.display_failed(game_data_manager);
	}
private:
	QuestInterfaces interface;
};

class QuestTakeCommand : public ICommand
{
public:
	QuestTakeCommand(string_context& command_context) : ICommand(command_context) { }
	~QuestTakeCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& (command_context[0] == "quest" || command_context[0] == "q")
			&& (command_context[1] == "take" || command_context[1] == "-t");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		const int quest_id = interface.get_quest_id_value(context.size() == 3 ? context[2] : "");
		if (game_data_manager.take_quest(quest_id))
		{
			return interface.display_quest_info(game_data_manager, quest_id);
		}
		return interface.display_quest_reservation_failed(quest_id);
	}
private:
	QuestInterfaces interface;
};

class QuestDispatchCommand : public ICommand
{
public:
	QuestDispatchCommand(string_context& command_context) : ICommand(command_context) { }
	~QuestDispatchCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& (command_context[0] == "quest" || command_context[0] == "q")
			&& (command_context[1] == "dispatch" || command_context[1] == "-d");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		const int adventurer_id = interface.get_adventurer_id_value(context.size() >= 3 ? context[2] : "");
		const int quest_id = interface.get_quest_id_value(context.size() >= 4 ? context[3] : "");
		if (game_data_manager.dispatch(adventurer_id, quest_id))
		{
			return interface.display_quest_result(game_data_manager, quest_id);
		}
		return interface.display_quest_dispatch_failed(adventurer_id, quest_id);
	}
private:
	QuestInterfaces interface;
};

#endif