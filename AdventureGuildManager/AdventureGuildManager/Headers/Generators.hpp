#ifndef GENERATORS_HPP
#define GENERATORS_HPP

#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include <vector>

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

class ChanceGenerator
{
public:
	ChanceGenerator(int minimumValue = 1, int maximumValue = 100) : distrib(minimumValue, maximumValue)
	{
		seed = rd() ^ (
			static_cast<std::mt19937::result_type>(std::chrono::duration_cast<std::chrono::seconds>(
					std::chrono::system_clock::now().time_since_epoch())
				.count()) +
			static_cast<std::mt19937::result_type>(std::chrono::duration_cast<std::chrono::microseconds>(
					std::chrono::high_resolution_clock::now().time_since_epoch())
				.count()));
		
		gen = std::move(std::make_unique<std::mt19937>(seed));
	}
	unsigned long long get_chance() const
	{
		return distrib(*gen);
	}
private:
	std::random_device rd;
	std::mt19937::result_type seed;
	std::unique_ptr<std::mt19937> gen;
	std::uniform_int_distribution<unsigned> distrib;
};

#endif