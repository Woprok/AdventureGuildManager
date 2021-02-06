#ifndef INTERFACES_HPP
#define INTERFACES_HPP

#include <string>
#include <vector>
#include <sstream>

#include "ConsoleProcessors.hpp"
#include "ConsoleHelpers.hpp"
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
		std::ostringstream result;
		result << "Following command is not recognized: ";
		for (auto&& body : command)
			result << "[" << body << "] ";
		result << "\n";
		return result.str();
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
		std::ostringstream result;
		result << "Guild information's!\n" 
			<< "[NAME:" << guild.get_name() << "]"
			<< "[DIFF:" << guild.get_diff() << "]"
			<< "[FAME:" << guild.get_fame() << "]"
			<< "[GOLD:" << guild.get_gold() << "]"
			<< "\n";
		return result.str();
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
		std::ostringstream result;
		result << "Available adventurers:\n";
		for (auto&& adventurer : adventurer_keeper.get_available())
		{
			result << adventurer_detail(*adventurer);
		}
		return result.str();
	}

	std::string show_hired(AdventurerKeeper& adventurer_keeper)
	{
		std::ostringstream result;
		result << "Hired adventurers:\n";
		for (auto&& adventurer : adventurer_keeper.get_hired())
		{
			result << adventurer_detail(*adventurer);
		}
		return result.str();
	}
	
	std::string show_dead(AdventurerKeeper& adventurer_keeper)
	{
		std::ostringstream result;
		result << "Dead adventurers:\n";
		for (auto&& adventurer : adventurer_keeper.get_dead())
		{
			result << adventurer_detail(*adventurer);
		}
		return result.str();
	}
	
	std::string show_inactive(AdventurerKeeper& adventurer_keeper)
	{
		std::ostringstream result;
		result << "Inactive adventurers:\n";
		for (auto&& adventurer : adventurer_keeper.get_inactive())
		{
			result << adventurer_detail(*adventurer);
		}
		return result.str();
	}

	std::string not_available_recruit()
	{
		return "Adventurer is not available to recruit or you are missing necessary funds.\n";
	}
	std::string not_available_pension()
	{
		return "Adventurer is not available to inactivate or you are missing necessary funds.\n";
	}
private:
	std::string adventurer_detail(Adventurer& adventurer)
	{
		std::string list_of_succ_quests;
		list_of_succ_quests = std::accumulate(
			adventurer.get_succ_quest_ids().begin(),
			adventurer.get_succ_quest_ids().end(),
			list_of_succ_quests,
			[](std::string a, int b) { return a + "; " + std::to_string(b); });
		std::string list_of_fail_quests;
		list_of_fail_quests = std::accumulate(
			adventurer.get_fail_quest_ids().begin(),
			adventurer.get_fail_quest_ids().end(),
			list_of_fail_quests,
			[](std::string a, int b) { return a + "; " + std::to_string(b); });
		
		std::ostringstream result;
		result << adventurer.get_id() << "::" << adventurer.get_name() << "->"
			<< "[COMPLETED: "
			<< (list_of_succ_quests.empty() ? "None" : list_of_succ_quests)
			<< "]"
			<< "[FAILED: "
			<< (list_of_fail_quests.empty() ? "None" : list_of_fail_quests)
			<< "]" << "\n"
			<< "\tStatistics: "
			<< "[RECRUITMENT COST: " << adventurer.get_recruitment_cost() << "]"
			<< "[RETIREMENT COST: " << adventurer.get_retirement_cost() << "]"
			<< "[LIVING EXPENSES: " << adventurer.get_living_expenses() << "]"
			<< "\n";
		return result.str();
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
		std::ostringstream result;
		result << "Available quests:\n";
		for (auto&& quest : quest_keeper.get_available())
		{
			result << quest_detail(*quest);
		}
		return result.str();

	}

	std::string show_reserved(QuestKeeper& quest_keeper)
	{
		std::ostringstream result;
		result << "Reserved quests:\n";
		for (auto&& quest : quest_keeper.get_reserved())
		{
			result << quest_detail(*quest);
		}
		return result.str();
	}

	std::string show_completed(QuestKeeper& quest_keeper)
	{
		std::ostringstream result;
		result << "Completed quests:\n";
		for (auto&& quest : quest_keeper.get_completed())
		{
			result << quest_detail(*quest);
		}
		return result.str();
	}
	
	std::string show_failed(QuestKeeper& quest_keeper)
	{
		std::ostringstream result;
		result << "Failed quests:\n";
		for (auto&& quest : quest_keeper.get_failed())
		{
			result << quest_detail(*quest);
		}
		return result.str();
	}
	
	std::string not_available()
	{
		return "Quest is not available or does not exist or guild has not enough funds to dispatch this adventurer.\n";
	}
private:
	std::string quest_detail(Quest& quest)
	{
		std::ostringstream result;
		result << quest.get_id() << "::" << quest.get_name() << "->"
			<< "[ATTEMPTED: "
			<< (quest.get_adventurer_id() == -1 ? "Not yet" : std::to_string(quest.get_adventurer_id()))
			<< "]"
			<< "\n"
			<< "\tReward for success: "
			<< "[FAME: " << quest.get_reward().get_fame() << "]"
			<< "[GOLD: " << quest.get_reward().get_gold() << "]"
			<< "\n"
			<< "\tPenalty for failure: "
			<< "[FAME :" << quest.get_penalty().get_fame() << "]"
			<< "[GOLD: " << quest.get_penalty().get_gold() << "]"
			<< "[RISK OF DEATH: " << (quest.get_penalty().get_deadly() ? "YES" : "NO") << "]"
			<< "\n";
		return result.str();
	}
};

/// <summary>
/// Set of interfaces for additional input's
/// </summary>
class InputInterface : public IDisplayeableInterface
{
public:
	static std::string get_name()
	{
		ConsoleProcessors::print_interface("Enter a new name: ");
		return ConsoleHelpers::read_line();
	}
	static int get_id(std::string&& possible_id)
	{
		int id = -1;
		if (!possible_id.empty())
		{
			try
			{
				id = std::stoi(possible_id);
			}
			catch (...)
			{
				ConsoleProcessors::print_interface("Last argument is not a proper id.\n");
				id = -1;
			}
		}
		while (id <= -1)
		{
			ConsoleProcessors::print_interface("Enter a id: ");
			try
			{
				id = std::stoi(ConsoleHelpers::read_line());
			}
			catch (...)
			{
				ConsoleProcessors::print_interface("Not a proper id.\n");
				id = -1;
			}
		}
		return id;
	}
};
#endif