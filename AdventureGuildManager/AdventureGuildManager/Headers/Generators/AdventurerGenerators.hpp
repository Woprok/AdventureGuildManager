#ifndef ADVENTURER_GENERATORS_HPP
#define ADVENTURER_GENERATORS_HPP

#include <iostream>

#include "NeutralGenerators.hpp"
#include "../DataKeepers/AdventurerDataKeepers.hpp"
#include "../DataKeepers/SkillDataKeepers.hpp"

/// <summary>
/// Keeps reference to actual data.
/// </summary>
class AdventurerGenerator
{
public:
	AdventurerGenerator(AdventurerDataKeeper& current_adventurer_data, SkillDataKeeper& current_skill_data)
		: adventurer_data(current_adventurer_data), skill_data((current_skill_data)) {}
	~AdventurerGenerator() = default;
	AdventurerGenerator(const AdventurerGenerator&) = delete;
	AdventurerGenerator& operator=(AdventurerGenerator) = delete;
	AdventurerRarity generate_rarity() const
	{
		int gen_rarity = rarity_generator.get_next();
		if (gen_rarity >= 149 && rarity_generator.get_next() >= 149 * 0.9) // 149
			return adventurer_data.get_adventurer_rarities()[5];
		if (gen_rarity >= 147) // 147 - 148
			return adventurer_data.get_adventurer_rarities()[4];
		if (gen_rarity >= 105) // 105 - 129
			return adventurer_data.get_adventurer_rarities()[3];
		if (gen_rarity >= 75) // 75 - 104
			return adventurer_data.get_adventurer_rarities()[2];
		if (gen_rarity >= 40) // 40 - 74
			return adventurer_data.get_adventurer_rarities()[1];
		// 0 - 39
		return adventurer_data.get_adventurer_rarities()[0];
	}
	int generate_difficulty(int min_difficulty) const
	{
		return std::clamp(rarity_generator.get_next(), min_difficulty, MAX_QUEST_DIFFICULTY);
	}

	std::unique_ptr<Adventurer> create_adventurer()
	{
		std::string&& name = name_generator.create_person_name();

		AdventurerRarity&& rarity = generate_rarity();
		const int rarity_as_int = static_cast<int>(rarity);
		skill_set&& skills = skill_data.generate(rarity_as_int);
		int&& experience = generate_experience(rarity_as_int);
		int&& recruit = generate_recruit(rarity_as_int);
		int&& retire = generate_retire(rarity_as_int);
		int&& living = generate_living(rarity_as_int);

		return std::make_unique<Adventurer>(std::move(name), rarity, experience, recruit, retire, living, std::move(skills));
	}
	int generate_experience(int rarity) const
	{
		return rarity * rarity_up_generator.get_next() + experience_generator.get_next();
	}
	int generate_recruit(int rarity) const
	{
		return rarity * rarity_up_generator.get_next() + recruit_generator.get_next();
	}
	int generate_retire(int rarity) const
	{
		return rarity * rarity_up_generator.get_next() + retire_generator.get_next();
	}
	int generate_living(int rarity) const
	{
		return rarity * rarity_up_generator.get_next() + living_generator.get_next();
	}

protected:
	AdventurerDataKeeper& adventurer_data;
	SkillDataKeeper& skill_data;
	UniformGenerator rarity_generator{ 0, 149 };
	UniformGenerator experience_generator{ 0, 1000 };
	UniformGenerator rarity_up_generator{ 1, 100 };
	UniformGenerator recruit_generator{ 50, 100 };
	UniformGenerator retire_generator{ 100, 200 };
	UniformGenerator living_generator{ 10, 20 };
	NameGenerator name_generator;
};
#endif