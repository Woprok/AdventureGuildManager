#ifndef I_DISPLAYABLE_INTERFACES_HPP
#define I_DISPLAYABLE_INTERFACES_HPP

#include <sstream>
#include <string>

class IDisplayeableInterfaces
{
public:
	IDisplayeableInterfaces() = default;
	virtual ~IDisplayeableInterfaces() = default;
	/// <summary>
	/// Summarize all commands under this interface.
	/// </summary>
	virtual std::string display_default()
	{
		std::ostringstream result_stream;
		result_stream << "*****Undefined user interface.*****" << "\n";
		return result_stream.str();
	}
};

#endif