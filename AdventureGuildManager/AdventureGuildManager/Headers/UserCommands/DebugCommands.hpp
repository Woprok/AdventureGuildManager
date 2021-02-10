#ifndef DEBUG_COMMANDS_HPP
#define DEBUG_COMMANDS_HPP

#include "../Interfaces/ICommands.hpp"

class DebugCommand : public ICommand
{
public:
	DebugCommand(string_context& command_context) : ICommand(command_context) { }
	~DebugCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 1
			&& command_context[0] == "debug";
	}
	std::string execute([[maybe_unused]] GameDataManager& game_data_manager) override
	{
		if (context.size() >= 2)
		{
			if (context[1] == "more")
			{
				game_data_manager.guild->base_stats.gold.add_value(10000);
				game_data_manager.guild->base_stats.fame.add_value(1000);
				return "You have more gold and fame now!\n";
			}

			if (context[1] == "less")
			{
				game_data_manager.guild->base_stats.gold.rmv_value(10000);
				game_data_manager.guild->base_stats.fame.rmv_value(1000);
				return "You have less gold and fame now!\n";
			}
		}
		return "Debug can be used as debug more or debug less!\n";
	}
};

#endif