#ifndef CONSOLE_HELPERS_HPP
#define CONSOLE_HELPERS_HPP

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class ConsoleHelpers
{
public:
	/// <summary>
	/// Trim from start (in place)
	/// </summary>
	static inline void left_trim(std::string& str)
	{
		str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch)
			{
				return !std::isspace(ch);
			}));
	}
	/// <summary>
	/// Trim from end (in place)
	/// </summary>
	static inline void right_trim(std::string& str)
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
		left_trim(str);
		right_trim(str);
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
	/// Checks if contains non space character
	/// </summary>
	static inline bool is_valid_body(const std::string& str)
	{
		return std::all_of(str.begin(), str.end(), isspace);
	}
	/// <summary>
	/// Wrapper around getline in case we will need to read commands from something else
	/// </summary>
	static inline std::string read_line()
	{
		std::string single_line;
		std::getline(std::cin, single_line);
		return single_line;
	}
	/// <summary>
	/// Returns line as it's expected that one line = one command. Removes empty lines as they are not valid.
	/// </summary>
	static inline std::string read_normalized_line()
	{
		std::string line;
		do
		{
			line = read_line();
			// Remove case when string is empty. Also purge all stupid spaces from line.
			normalize_spaces(line);
			trim_string(line);
		} while (line.empty());
		return line;
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
};

#endif