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
	std::string display_default() override
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
		result_stream << "\t" << "TODO:" << "\n";
		return result_stream.str();
	}
};

#endif