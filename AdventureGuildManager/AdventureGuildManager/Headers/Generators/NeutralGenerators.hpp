#ifndef GENERATORS_HPP
#define GENERATORS_HPP

#include <algorithm>
#include <chrono>
#include <iterator>
#include <random>
#include <string>
#include <vector>

/// <summary>
/// Generates numbers from min_value to max_value included.
/// </summary>
class UniformGenerator final
{
public:
	UniformGenerator(int min_value, int max_value) : distribution(0, max_value) { }
	int get_next() const { return distribution(rng); }
protected:
	std::uniform_int_distribution<unsigned> distribution;
	inline static std::mt19937 rng{ std::random_device{}() };
};

class NameGenerator
{
public:
	NameGenerator() = default;
	virtual ~NameGenerator() = default;
	std::string get_random_item(const std::vector<std::string>& collection) const
	{
		std::vector<std::string> result;
		std::sample(collection.begin(), 
			collection.end(), 
			std::back_inserter(result),
			1, 
			std::mt19937{ std::random_device{}()});
		return result[0];
	}
	
	std::string create_person_name() const
	{
		return get_random_item(name_start) + get_random_item(name_middle) + get_random_item(name_end);
	}
private:
	const std::vector<std::string> name_start = {
		"A", "Be", "De", "El", "Fa",
		"Jo", "Ki", "La", "Ma", "Na",
		"O", "Pa", "Re", "Si", "Ta",
		"Va"
	};
	const std::vector<std::string> name_middle = {
		"bar", "ched", "dell", "far", "gran",
		"hal", "jen", "kel", "lim", "mor",
		"net", "penn", "quil", "rond", "sark",
		"shen", "tur", "vash", "yor", "zen"
	};
	const std::vector<std::string> name_end = {
		"a", "ac", "ai", "al", "am",
		"an", "ar", "ea", "el", "er",
		"ess", "ett", "ik", "id", "il",
		"in", "is", "or", "us"
	};
};

#endif