#ifndef INPUT_INTERFACES_HPP
#define INPUT_INTERFACES_HPP

#include "../Helpers/ConsoleHelpers.hpp"
#include "../Helpers/ConsoleProcessors.hpp"
#include "../Interfaces/IDisplayableInterfaces.hpp"

/// <summary>
/// Set of interfaces for additional inputs.
/// </summary>
class InputInterfaces
{
public:
	static std::string get_str(const std::string& what)
	{
		ConsoleProcessors::print_interface("Enter a " + what + ": ");
		return ConsoleHelpers::read_line();
	}
	static int get_num(std::string& possible_num, const std::string& what)
	{
		int id = -1;
		if (!possible_num.empty())
		{
			try
			{
				id = std::stoi(possible_num);
			}
			catch (...)
			{
				ConsoleProcessors::print_interface("Last argument is not a proper " + what + ".\n");
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
				ConsoleProcessors::print_interface("Not a proper " + what + ".\n");
				id = -1;
			}
		}
		return id;
	}
};

#endif