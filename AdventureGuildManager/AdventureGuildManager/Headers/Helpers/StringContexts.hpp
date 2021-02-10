#ifndef STRING_CONTEXTS_HPP
#define STRING_CONTEXTS_HPP

#include <numeric>
#include <string>
#include <vector>

typedef std::vector<std::string> string_context;

class StringContext
{
public:
	static std::string merge(std::vector<std::string>& context, int offset, const std::string& delimeter)
	{
		std::string result;
		return std::accumulate(context.begin() + offset, context.end(), result,
			[delimeter](const std::string& a, const std::string& b) { return a + delimeter + b; });
	}


	static std::string merge(std::unordered_set<std::string>& context, const std::string& delimeter)
	{
		std::string result;
		return std::accumulate(context.begin(), context.end(), result,
			[delimeter](const std::string& a, const std::string& b) { return a + delimeter + b; });
	}

};

#endif