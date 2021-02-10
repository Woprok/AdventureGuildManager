#ifndef EXIT_INTERFACES_HPP
#define EXIT_INTERFACES_HPP

#include <sstream>
#include <string>


#include "../GameDataManagers.hpp"
#include "../Interfaces/IDisplayableInterfaces.hpp"

class ExitInterfaces final : public IDisplayeableInterfaces
{
public:
	ExitInterfaces() = default;
	~ExitInterfaces() override = default;
	std::string display_default() const override
	{
		std::ostringstream result_stream;
		result_stream << "Exit Commands:\n";
		result_stream << "\t- exit: closes game.\n";
		return result_stream.str();
	}
	std::string display_exit(GameDataManager& game_data_manager) const
	{
		std::ostringstream result_stream;
		result_stream << "*****Game ended!*****" << "\n";
		result_stream << "Your journey as guild manager ends here!" << "\n";
		result_stream << "Your final stats:" << "\n";
		result_stream << "\t" << "Quest completed: " << game_data_manager.quests->get_completed().size() <<"\n";
		result_stream << "\t" << "Quest failed: " << game_data_manager.quests->get_failed().size() <<"\n";
		result_stream << "\t" << "Adventurer retired: " << game_data_manager.adventurers->get_inactive().size() <<"\n";
		result_stream << "\t" << "Adventurer killed: " << game_data_manager.adventurers->get_dead().size() <<"\n";
		result_stream << "\t" << "And much more could be shown..." <<"\n";
		return result_stream.str();
	}
};

#endif