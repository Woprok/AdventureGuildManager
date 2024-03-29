﻿#ifndef PERK_COMMANDS_HPP
#define PERK_COMMANDS_HPP

#include "../Interfaces/ICommands.hpp"
#include "../UserInterfaces/PerkInterfaces.hpp"

class PerkCommand : public ICommand
{
public:
	PerkCommand(string_context& command_context) : ICommand(command_context) { }
	~PerkCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 1
			&& (command_context[0] == "perk" || command_context[0] == "p");
	}
	std::string execute([[maybe_unused]] GameDataManager& game_data_manager) override
	{
		return interface.display_default();
	}
private:
	PerkInterfaces interface;
};
class PerkTradeFameCommand : public ICommand
{
public:
	PerkTradeFameCommand(string_context& command_context) : ICommand(command_context) { }
	~PerkTradeFameCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& (command_context[0] == "perk" || command_context[0] == "p")
			&& (command_context[1] == "trade_fame" || command_context[1] == "-t");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		int fame_amount = interface.get_fame_value(context.size() == 3 ? context[2] : "");

		if (game_data_manager.trade(fame_amount))
		{

		}
		return interface.display_trade_action_failed(fame_amount);
	}
private:
	PerkInterfaces interface;
};
class PerkRequalificationCourseCommand : public ICommand
{
public:
	PerkRequalificationCourseCommand(string_context& command_context) : ICommand(command_context) { }
	~PerkRequalificationCourseCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& (command_context[0] == "perk" || command_context[0] == "p")
			&& (command_context[1] == "requalification_course" || command_context[1] == "-r");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		int adventurer_id = interface.get_adventurer_id_value(context.size() == 3 ? context[2] : "");

		if (game_data_manager.retrain(adventurer_id))
		{
			return interface.display_armory(game_data_manager, adventurer_id);
		}
		return interface.display_adventurer_action_failed(adventurer_id);
	}
private:
	PerkInterfaces interface;
};
class PerkArmoryCommand : public ICommand
{
public:
	PerkArmoryCommand(string_context& command_context) : ICommand(command_context) { }
	~PerkArmoryCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& (command_context[0] == "perk" || command_context[0] == "p")
			&& (command_context[1] == "armory" || command_context[1] == "-a");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		int adventurer_id = interface.get_adventurer_id_value(context.size() == 3 ? context[2] : "");

		if (game_data_manager.upgrade(adventurer_id))
		{
			return interface.display_armory(game_data_manager, adventurer_id);
		}
		return interface.display_adventurer_action_failed(adventurer_id);
	}
private:
	PerkInterfaces interface;
};
class PerkChurchOfHeroesCommand : public ICommand
{
public:
	PerkChurchOfHeroesCommand(string_context& command_context) : ICommand(command_context) { }
	~PerkChurchOfHeroesCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& (command_context[0] == "perk" || command_context[0] == "p")
			&& (command_context[1] == "church_of_heroes" || command_context[1] == "-c");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		int adventurer_id = interface.get_adventurer_id_value(context.size() == 3 ? context[2] : "");

		if (game_data_manager.resurrect(adventurer_id))
		{
			return interface.display_church_of_heroes(game_data_manager, adventurer_id);
		}
		return interface.display_adventurer_action_failed(adventurer_id);
	}
private:
	PerkInterfaces interface;
};

class PerkMadnessOfMasterCommand : public ICommand
{
public:
	PerkMadnessOfMasterCommand(string_context& command_context) : ICommand(command_context) { }
	~PerkMadnessOfMasterCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& (command_context[0] == "perk" || command_context[0] == "p")
			&& (command_context[1] == "madness_of_master" || command_context[1] == "-m");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		int adventurer_id = interface.get_adventurer_id_value(context.size() == 3 ? context[2] : "");

		if (game_data_manager.grant_godslayer(adventurer_id))
		{
			return interface.display_madness_of_master(game_data_manager, adventurer_id);
		}
		return interface.display_adventurer_action_failed(adventurer_id);
	}
private:
	PerkInterfaces interface;
};

class PerkBuyCommand : public ICommand
{
public:
	PerkBuyCommand(string_context& command_context) : ICommand(command_context) { }
	~PerkBuyCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& (command_context[0] == "perk" || command_context[0] == "p")
			&& (command_context[1] == "buy" || command_context[1] == "-b");
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		int perk_id = interface.get_perk_id_value(context.size() == 3 ? context[2] : "");

		if (game_data_manager.buy_perk(perk_id))
		{
			return interface.display_bought(game_data_manager, perk_id);
		}
		return interface.display_perk_action_failed(perk_id);
	}
private:
	PerkInterfaces interface;
};

#endif