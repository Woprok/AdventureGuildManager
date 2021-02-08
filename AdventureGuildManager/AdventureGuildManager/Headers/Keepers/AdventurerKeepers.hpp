#ifndef ADVENTURER_KEEPERS_HPP
#define ADVENTURER_KEEPERS_HPP
#include <memory>

#include "../Helpers/CollectionIterators.hpp"

class AdventurerKeeper
{
public:
	std::unique_ptr<Adventurer> create_adventurer(EncyclopediaKeeper& keep)
	{
		auto&& adventurer = std::make_unique<Adventurer>(name_generator.create_person_name());
		adventurer->set_recruitment_cost(50);
		adventurer->set_retirement_cost(10);
		adventurer->set_living_expenses(50);
		adventurer->set_experience(995);
		adventurer->set_rarity(AdventurerRarity::Innkeeper);
		adventurer->set_skills(keep.generate_from_rarity(static_cast<int>(adventurer->get_rarity())));

		return std::move(adventurer);
	}
	void generate(EncyclopediaKeeper& keep, int count)
	{
		for (int i = 0; i < count; ++i)
		{
			available.push_back(create_adventurer(keep));
		}
	}
	void clear()
	{
		available.clear();
		hired.clear();
		dead.clear();
		inactive.clear();
	}
	bool recruit(int adventurer_id)
	{
		return CollectionIterators::transfer(available, hired, adventurer_id);
	}
	bool pension(int adventurer_id)
	{
		return CollectionIterators::transfer(hired, inactive, adventurer_id);
	}
	bool kill(int adventurer_id)
	{
		return CollectionIterators::transfer(hired, dead, adventurer_id);
	}
	bool revive(int adventurer_id)
	{
		return CollectionIterators::transfer(dead, hired, adventurer_id);
	}
	const adventurer_collection& get_hired() { return hired; }
	const adventurer_collection& get_available() { return available; }
	const adventurer_collection& get_dead() { return dead; }
	const adventurer_collection& get_inactive() { return inactive; }
private:
	adventurer_collection available;
	adventurer_collection hired;
	adventurer_collection dead;
	adventurer_collection inactive;
	NameGenerator name_generator;
};

#endif