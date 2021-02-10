#ifndef HELP_INTERFACES_HPP
#define HELP_INTERFACES_HPP
#include "../Interfaces/IDisplayableInterfaces.hpp"

class HelpInterfaces : public IDisplayeableInterfaces
{
public:
	HelpInterfaces() = default;
	~HelpInterfaces() override = default;
	std::string display_default() const override
	{
		std::ostringstream result_stream;
		result_stream << "Help Commands:\n";
		result_stream << "\t- help: shows all help.\n";
		return result_stream.str();
	}
};

#endif