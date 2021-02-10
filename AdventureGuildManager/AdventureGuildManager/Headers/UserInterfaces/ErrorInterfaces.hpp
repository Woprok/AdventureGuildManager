#ifndef ERROR_INTERFACES_HPP
#define ERROR_INTERFACES_HPP

#include <sstream>
#include <string>

#include "../GameDataManagers.hpp"
#include "../Helpers/StringContexts.hpp"
#include "../Interfaces/IDisplayableInterfaces.hpp"

class ErrorInterfaces final : public IDisplayeableInterfaces
{
public:
	ErrorInterfaces() = default;
	~ErrorInterfaces() override = default;
	std::string display_default() const override
	{
		std::ostringstream result_stream;
		result_stream << "Error Commands:\n";
		result_stream << "\t- error: displays error message.\n";
		return result_stream.str();
	}
	  std::string display_error(string_context& command_context) const
	  {
		  std::ostringstream result_stream;
		  result_stream << "*****Error!*****" << "\n";
		  result_stream << "Following command was not recognized:" << "\n";
		  result_stream << "\t";
		  result_stream << StringContext::merge(command_context, 0, " ");
		  result_stream << "\n";
		  return result_stream.str();
	  }
};

#endif