#ifndef CONSOLE_PROCESSORS_HPP
#define CONSOLE_PROCESSORS_HPP

#include "ConsoleHelpers.hpp"

class ConsoleProcessors
{
public:
	/// <summary>
	/// Hopefully covers most stupid space cases. Other characters are considered legit even.
	/// </summary>
	static inline std::vector<std::string> get_next_command()
	{
		return ConsoleHelpers::split_string(ConsoleHelpers::read_normalized_line(), ' ');
	}
	/// <summary>
	/// This might need more work as there is no standard way how to do it correctly on each platform.
	/// </summary>
	static void clean_interface()
	{
#if defined _WIN32
		system("cls");
		//clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
		system("clear");
		//std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#endif
	}

	/// <summary>
	/// Input is required to end with new line, this does not append '\\n'.
	/// </summary>
	static void print_interface(const std::string& interface)
	{
		std::cout << interface;
	}

	/// <summary>
	/// Input is required to end with new line, this does not append '\\n'.
	/// </summary>
	static void clean_and_print(const std::string& interface)
	{
		clean_interface();
		print_interface(interface);

	}

	static void print_debug(const std::string& body)
	{
		std::cout << "DEBUG:" << body << "\n";
	}
	static void print_debug(const std::vector<std::string>& content)
	{
		std::cout << "DEBUG:";
		for (auto&& body : content)
			std::cout << "[" + body + "] ";
		std::cout << "\n";
	}
};

#endif