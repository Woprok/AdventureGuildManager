#ifndef MENU_INTERFACES_HPP
#define MENU_INTERFACES_HPP

#include <string>


#include "InputInterfaces.hpp"
#include "../Interfaces/IDisplayableInterfaces.hpp"

class MenuInterfaces final : public IDisplayeableInterfaces
{
public:
	MenuInterfaces() = default;
	~MenuInterfaces() override = default;
	std::string display_default() const override
	{
		std::ostringstream result_stream;
		result_stream << "Menu Commands:\n";
		result_stream << "\t- menu: current game state.\n";
		result_stream << "\t- menu start: start game.\n";
		result_stream << "\t- menu end: end game.\n";
		result_stream << "\t- menu difficulty \"new difficulty\": change game difficulty.\n";
		return result_stream.str();
	}
	std::string display_in_progress() const
	{
		std::ostringstream result_stream;
		result_stream << "*****Adventure Guild Manager!*****" << "\n";
		result_stream << "Game in progress! You can end game by using \"menu end\"." << "\n";
		return result_stream.str();
	}
	std::string display_no_progress() const
	{
		std::ostringstream result_stream;
		result_stream << "*****Adventure Guild Manager!*****" << "\n";
		result_stream << "No game in progress! You can start game by using \"menu start\"." << "\n";
		return result_stream.str();
	}
	std::string display_end(GameDataManager& game_data_manager) const
	{
		std::ostringstream result_stream;
		result_stream << "*****Adventure Guild Manager!*****" << "\n";
		result_stream << "Game was ended!" << "\n";
		result_stream << "You will have to start new game by using \"menu start\"." << "\n";
		result_stream << "Your final stats:" << "\n";
		result_stream << "\t" << "Quest completed: " << game_data_manager.quests->get_completed().size() << "\n";
		result_stream << "\t" << "Quest failed: " << game_data_manager.quests->get_failed().size() << "\n";
		result_stream << "\t" << "Adventurer retired: " << game_data_manager.adventurers->get_inactive().size() << "\n";
		result_stream << "\t" << "Adventurer killed: " << game_data_manager.adventurers->get_dead().size() << "\n";
		result_stream << "\t" << "And much more could be shown..." << "\n";
		return result_stream.str();
	}
	std::string display_start() const
	{
		std::ostringstream result_stream;
		result_stream << "*****Adventure Guild Manager!*****" << "\n";
		result_stream << "Game was started!" << "\n";
		result_stream << "Learn more by using \"help\"." << "\n";
		return result_stream.str();
	}
	std::string display_difficulty(int new_difficulty) const
	{
		std::ostringstream result_stream;
		result_stream << "*****Adventure Guild Manager!*****" << "\n";
		result_stream << "Game difficulty was changed!" << "\n";
		result_stream << "Current difficulty: " << new_difficulty << "\n";
		result_stream << "Learn more by using \"help\"." << "\n";
		return result_stream.str();
	}

	int get_difficulty_value(std::string&& cs) const
	{
		return InputInterfaces::get_num(cs, "difficulty");
	}
};

#endif