#ifndef GENERATORS_HPP
#define GENERATORS_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <random>

class NameGenerator
{
public:
	std::string get_from(std::vector<std::string> collection)
	{
		std::vector<std::string> result;
		std::sample(collection.begin(), 
			collection.end(), 
			std::back_inserter(result),
			1, 
			std::mt19937{ std::random_device{}()});
		return result[0];
	}
	
	std::string create_person_name()
	{
		return get_from(pos1) + get_from(pos2) + get_from(pos3);
	}
	std::string create_quest_name()
	{
		return get_from(qst1) + " " + get_from(qst2) + " " + get_from(qst3);
	}
private:
	std::vector<std::string> pos1 = {
		"A", "Be", "De", "El", "Fa",
		"Jo", "Ki", "La", "Ma", "Na",
		"O", "Pa", "Re", "Si", "Ta",
		"Va"
	};
	std::vector<std::string> pos2 = {
		"bar", "ched", "dell", "far", "gran",
		"hal", "jen", "kel", "lim", "mor",
		"net", "penn", "quil", "rond", "sark",
		"shen", "tur", "vash", "yor", "zen"
	};
	std::vector<std::string> pos3 = {
		"a", "ac", "ai", "al", "am",
		"an", "ar", "ea", "el", "er",
		"ess", "ett", "ik", "id", "il",
		"in", "is", "or", "us"
	};
	std::vector<std::string> qst1 = {
		"Search", "Find", "Kill", "Assasinate", "Protect"
	};
	std::vector<std::string> qst2 = {
		"the", "a"
	};
	std::vector<std::string> qst3 = {
		"Mountains", "Hills", "Monster", "Merchant"
	};
};

#endif