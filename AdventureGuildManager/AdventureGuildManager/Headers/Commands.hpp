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
		return command_context.size() == 1
			&& command_context[0] == "menu";
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
		return command_context.size() == 1
			&& command_context[0] == "help";
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
		return command_context.size() == 1
			&& command_context[0] == "exit";
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
		return command_context.size() == 1 && (command_context[0] == "guild" || command_context[0] == "g");
	}
	std::string execute(GameData& game_data) override
	{
		return interface.to_string();
	}
private:
	GuildInterface interface;
};

class GuildInfoCommand : public ICommand
{
public:
	GuildInfoCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "guild" || command_context[0] == "g")
			&& (command_context[1] == "info" || command_context[1] == "-i");
	}
	std::string execute(GameData& game_data) override
	{
		return interface.to_string(game_data.current_guild);
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
			&& (command_context[0] == "guild" || command_context[0] == "g")
			&& (command_context[1] == "create" || command_context[1] == "-c");
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
			&& (command_context[0] == "guild" || command_context[0] == "g")
			&& (command_context[1] == "rename" || command_context[1] == "-r");
	}
	std::string execute(GameData& game_data) override
	{
		std::string name;
		if (context.size() >= 3)
		{
			name = std::accumulate(context.begin() + 2, context.end(), name,
				[](std::string a, std::string b) { return a + " " + b; });
		}
		else
		{
			name = InputInterface::get_name();
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
			&& (command_context[0] == "guild" || command_context[0] == "g")
			&& (command_context[1] == "difficulty" || command_context[1] == "-d");
	}
	std::string execute(GameData& game_data) override
	{
		return interface.to_string(game_data.current_guild);
	}
private:
	GuildInterface interface;
};


class AdventurerCommand : public ICommand
{
public:
	AdventurerCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 1
			&& (command_context[0] == "adventurer" || command_context[0] == "a");
	}
	std::string execute(GameData& game_data) override
	{
		return interface.to_string();
	}
private:
	AdventurerInterface interface;
};


class AdventurerAvailableCommand : public ICommand
{
public:
	AdventurerAvailableCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "adventurer" || command_context[0] == "a")
			&& (command_context[1] == "available" || command_context[1] == "-a");
	}
	std::string execute(GameData& game_data) override
	{
		return interface.show_available(game_data.adventurers);
	}
private:
	AdventurerInterface interface;
};


class AdventurerHiredCommand : public ICommand
{
public:
	AdventurerHiredCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "adventurer" || command_context[0] == "a")
			&& (command_context[1] == "hired" || command_context[1] == "-h");
	}
	std::string execute(GameData& game_data) override
	{
		return interface.show_hired(game_data.adventurers);
	}
private:
	AdventurerInterface interface;
};

class AdventurerDeadCommand : public ICommand
{
public:
	AdventurerDeadCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "adventurer" || command_context[0] == "a")
			&& (command_context[1] == "dead" || command_context[1] == "-d");
	}
	std::string execute(GameData& game_data) override
	{
		return interface.show_dead(game_data.adventurers);
	}
private:
	AdventurerInterface interface;
};

class AdventurerInactiveCommand : public ICommand
{
public:
	AdventurerInactiveCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "adventurer" || command_context[0] == "a")
			&& (command_context[1] == "inactive" || command_context[1] == "-i");
	}
	std::string execute(GameData& game_data) override
	{
		return interface.show_inactive(game_data.adventurers);
	}
private:
	AdventurerInterface interface;
};

class AdventurerRecruitCommand : public ICommand
{
public:
	AdventurerRecruitCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& (command_context[0] == "adventurer" || command_context[0] == "a")
			&& (command_context[1] == "recruit" || command_context[1] == "-r");
	}
	std::string execute(GameData& game_data) override
	{
		int id = InputInterface::get_id(context.size() == 3 ? context[2] : "");
		
		if (!game_data.recruit(id))
		{
			return interface.not_available_recruit();
		}
		
		return interface.show_hired(game_data.adventurers);
	}
private:
	AdventurerInterface interface;
};

class AdventurerPensionCommand : public ICommand
{
public:
	AdventurerPensionCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& (command_context[0] == "adventurer" || command_context[0] == "a")
			&& (command_context[1] == "pension" || command_context[1] == "-p");
	}
	std::string execute(GameData& game_data) override
	{
		int id = InputInterface::get_id(context.size() == 3 ? context[2] : "");

		if (!game_data.pension(id))
		{
			return interface.not_available_pension();
		}

		return interface.show_inactive(game_data.adventurers);
	}
private:
	AdventurerInterface interface;
};

class QuestCommand : public ICommand
{
public:
	QuestCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 1
			&& (command_context[0] == "quest" || command_context[0] == "q");
	}
	std::string execute(GameData& game_data) override
	{
		return interface.to_string();
	}
private:
	QuestInterface interface;
};


class QuestAvailableCommand : public ICommand
{
public:
	QuestAvailableCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "quest" || command_context[0] == "q")
			&& (command_context[1] == "available" || command_context[1] == "-a");
	}
	std::string execute(GameData& game_data) override
	{
		return interface.show_available(game_data.quests);
	}
private:
	QuestInterface interface;
};


class QuestReserverCommand : public ICommand
{
public:
	QuestReserverCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "quest" || command_context[0] == "q")
			&& (command_context[1] == "reserved" || command_context[1] == "-r");
	}
	std::string execute(GameData& game_data) override
	{
		return interface.show_reserved(game_data.quests);
	}
private:
	QuestInterface interface;
};

class QuestCompletedCommand : public ICommand
{
public:
	QuestCompletedCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "quest" || command_context[0] == "q")
			&& (command_context[1] == "completed" || command_context[1] == "-c");
	}
	std::string execute(GameData& game_data) override
	{
		return interface.show_completed(game_data.quests);
	}
private:
	QuestInterface interface;
};

class QuestFailedCommand : public ICommand
{
public:
	QuestFailedCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 2
			&& (command_context[0] == "quest" || command_context[0] == "q")
			&& (command_context[1] == "failed" || command_context[1] == "-f");
	}
	std::string execute(GameData& game_data) override
	{
		return interface.show_failed(game_data.quests);
	}
private:
	QuestInterface interface;
};

class QuestTakeCommand : public ICommand
{
public:
	QuestTakeCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& (command_context[0] == "quest" || command_context[0] == "q")
			&& (command_context[1] == "take" || command_context[1] == "-t");
	}
	std::string execute(GameData& game_data) override
	{
		const int id = InputInterface::get_id(context.size() == 3 ? context[2] : "");

		if (!game_data.quests.take(id))
		{
			return interface.not_available();
		}

		return interface.show_reserved(game_data.quests);
	}
private:
	QuestInterface interface;
};

class QuestDispatchCommand : public ICommand
{
public:
	QuestDispatchCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& (command_context[0] == "quest" || command_context[0] == "q")
			&& (command_context[1] == "dispatch" || command_context[1] == "-d");
	}
	std::string execute(GameData& game_data) override
	{
		const int adventurer_id = InputInterface::get_id(context.size() >= 3 ? context[2] : "");
		const int quest_id = InputInterface::get_id(context.size() >= 4 ? context[3] : "");
		auto&& result = game_data.dispatch(adventurer_id, quest_id);
		if (result == QuestStateEnum::Success)
			return interface.show_completed(game_data.quests);
		if (result == QuestStateEnum::Failure)
			return interface.show_failed(game_data.quests);
		return interface.not_available();
	}
private:
	QuestInterface interface;
};
#pragma endregion
#endif