#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>

static void debug(const std::string& body)
{
	std::cout << "DEBUG:" << body << "\n";
}
static void debug(const std::vector<std::string>& content)
{
	std::cout << "DEBUG:";
	for (auto&& body : content)
		std::cout  << "[" + body + "] ";
	std::cout << "\n";
}


class Command
{
public:
	Command(std::vector<std::string>&& full_command_body)
	{
		full_command = full_command_body;
	}
	const std::string& get_name() const
	{
		return full_command[0];
	}
	const std::vector<std::string>& get_body() const
	{
		return full_command;
	}
private:
	std::vector<std::string> full_command;
};

class InputParser
{
public:
	/// <summary>
	/// Trim from start (in place)
	/// </summary>
	static inline void ltrim(std::string& str)
	{
		str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch)
			{
				return !std::isspace(ch);
			}));
	}
	/// <summary>
	/// Trim from end (in place)
	/// </summary>
	static inline void rtrim(std::string& str)
	{
		str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch)
			{
				return !std::isspace(ch);
			}).base(), str.end());
	}
	/// <summary>
	/// Trim from both ends(in place)
	/// </summary>
	static inline void trim_string(std::string& str)
	{
		ltrim(str);
		rtrim(str);
	}
	static inline bool is_valid_body(const std::string& str)
	{
		return std::all_of(str.begin(), str.end(), isspace);
	}
	static inline std::string read_line()
	{
		std::string single_line;
		std::getline(std::cin, single_line);
		return single_line;
	}
	/// <summary>
	/// Remove isspace in between bodies and replace them with single character.
	/// </summary>
	static inline void normalize_spaces(std::string& str)
	{
		std::transform(str.begin(), str.end(), str.begin(), [](char ch)
			{
				return isspace(ch) ? ' ' : ch;
			});
	}
	/// <summary>
	/// Tokenize command and remove all spaces from command as they are used as separator.
	/// </summary>
	static inline std::vector<std::string> split_string(const std::string& content, const char delimiter)
	{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(content);
		while (std::getline(tokenStream, token, delimiter))
		{
			if (!is_valid_body(token))
				tokens.push_back(token);
		}
		return tokens;
	}
	/// <summary>
	/// Returns line as it's expected that one line = one command. Removes empty lines as they are not valid.
	/// </summary>
	static inline std::string read_single_command()
	{
		std::string line;
		do
		{
			line = read_line();
			// Remove case when string is empty. Also purge all stupid spaces from line.
			normalize_spaces(line);
			trim_string(line);
		}
		while (line.empty());
		return line;
	}
	/// <summary>
	/// Hopefully covers most stupid space cases. Other characters are considered legit even.
	/// </summary>
	static inline Command get_next_command()
	{
		std::vector<std::string> full_command = split_string(read_single_command(), ' ');
		return Command(std::move(full_command));
	}	
};

class CommandController
{
public:
	bool process_command(Command& command)
	{
		if (command.get_name() == "guild")
		{
			return true;
		}
	}

};

class OutputPrinter
{
	
};


class DisplayeableInterface
{
public:
	virtual ~DisplayeableInterface() = default;

	virtual std::string get_interface()
	{
		return "Not found!\n";
	}
};

class HelpInterface : DisplayeableInterface
{
public:
	std::string get_interface() override
	{
		return "Help!\n Following commands are allowed: help, exit.\n";
	}
};
class IntroInterface : DisplayeableInterface
{
public:
	std::string get_interface() override
	{
		return "Adventure Guild Manager!\n";
	}
};
class ExitInterface : DisplayeableInterface
{
public:
	std::string get_interface() override
	{
		return "You decided to left your adventuring life behind!\n";
	}
};
class ErrorInterface : DisplayeableInterface
{
public:
	std::string get_interface() override
	{
		return "Invalid Command!\n";
	}
};
class CommandInterface : DisplayeableInterface
{
public:
	std::string get_interface() override
	{
		return "Valid Command!\n";
	}
};

class UserInterfaceController
{
public:
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
};



void display_command(std::string command, std::string command_result)
{
	UserInterfaceController::clean_interface();
	UserInterfaceController::print_interface(command_result);
}

class GameState
{
public:
	std::string process_command(const std::string& command)
	{
		if (command == "help")
			return HelpInterface().get_interface();
		if (command == "exit")
		{
			exit_requested = true;
			return ExitInterface().get_interface();
		}
		if (command == "command")
			return CommandInterface().get_interface();
		// "Error"
		return ErrorInterface().get_interface();
	}
	bool can_continue() const
	{
		return is_alive() && !is_exit_requested();
	}
	bool is_alive() const
	{
		return alive;
	}
	bool is_exit_requested() const
	{
		return exit_requested;
	}
private:
	bool alive = true;
	bool exit_requested = false;
	
};

class GameInstance
{
public:
	void run_game()
	{
		UserInterfaceController::print_interface(IntroInterface().get_interface() + "\n");
		while (game_state.can_continue())
		{
			Command command = InputParser::get_next_command();

			
			std::string command_result = game_state.process_command(command.get_name());
			display_command(command.get_name(), command_result);

			debug(command.get_body());

		}
	}
private:
	GameState game_state;
};


int main()
{
	GameInstance game_instance;
	game_instance.run_game();

	return 0;
}