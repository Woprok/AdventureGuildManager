﻿#ifndef INTERFACES_HPP
#define INTERFACES_HPP

#include <string>
#include <vector>
#include "GameEntities.hpp"

class IDisplayeableInterface
{
public:
	virtual ~IDisplayeableInterface() = default;
	virtual std::string to_string() = 0;
};

class MenuInterface : public IDisplayeableInterface
{
public:
	std::string to_string() override
	{
		return "Welcome to Adventure Guild Manager!\nUse help to learn more or game create to start game.\n";
	}
	std::string in_progress()
	{
		return "Game in progress! You can restart game by using menu restart.\n";
	}
	std::string no_progress()
	{
		return "No game in progress! You can start game by using guild create.\n";
	}
	std::string show_restart()
	{
		return "Game state is reset! You will have to start new game.\n";
	}
};

class HelpInterface : public IDisplayeableInterface
{
public:
	std::string to_string() override
	{
		return "Help!\n Following commands are allowed: menu, help, exit, guild.\n";
	}
};

class ExitInterface : public IDisplayeableInterface
{
public:
	std::string to_string() override
	{
		return "You decided to left your adventuring life behind!\n";
	}
};

class ErrorInterface : public IDisplayeableInterface
{
public:
	std::string to_string() override
	{
		return "Invalid Command!\n";
	}
	std::string to_string(std::vector<std::string>& command)
	{
		std::string result;
		for (auto&& body : command)
			result += "[" + body + "] ";
		return "Following command is not recognized: " + result + "\n";
	}
};

class GuildInterface : public IDisplayeableInterface
{
public:
	std::string to_string() override
	{
		return "Welcome to your guild!\n";
	}
	std::string to_string(Guild& guild)
	{
		return "Guild information's!\n" + guild.get_name() + "-->"
			+ "[NAME:" + guild.get_name() + "]"
			+ "[DIFF:" + std::to_string(guild.get_diff()) + "]"
			+ "[FAME:" + std::to_string(guild.get_fame()) + "]"
			+ "[GOLD:" + std::to_string(guild.get_gold()) + "]"
			+ "\n";
	}

	std::string game_in_progress()
	{
		return "Game in progress, see help or menu for additional options!\n";
	}
};

class AdventurerInterface : public IDisplayeableInterface
{
public:
	std::string to_string() override
	{
		return "Welcome to public relations guild!\n";
	}
	std::string show_available(AdventurerKeeper& adventurer_keeper)
	{
		std::string result = "Available adventurers:\n";
		for (auto && adventurer : adventurer_keeper.get_available())
		{
			result += adventurer->get_name() + "\n";
		}
		return result;
	}

	std::string show_hired(AdventurerKeeper& adventurer_keeper)
	{
		std::string result = "Hired adventurers:\n";
		for (auto&& adventurer : adventurer_keeper.get_hired())
		{
			result += adventurer->get_name() + "\n";
		}
		return result;
	}
};

class QuestInterface : public IDisplayeableInterface
{
public:
	std::string to_string() override
	{
		return "Welcome to Quest board association!\n";
	}
	std::string show_available(QuestKeeper& quest_keeper)
	{
		std::string result = "Available quests:\n";
		for (auto&& adventurer : quest_keeper.get_available())
		{
			result += adventurer->get_name() + "\n";
		}
		return result;
	}

	std::string show_accepted(QuestKeeper& quest_keeper)
	{
		std::string result = "Accepted quests:\n";
		for (auto&& adventurer : quest_keeper.get_accepted())
		{
			result += adventurer->get_name() + "\n";
		}
		return result;
	}
};
#endif