#ifndef ADVENTURER_KEEPERS_HPP
#define ADVENTURER_KEEPERS_HPP

#include <memory>

#include "../Helpers/CollectionIterators.hpp"
#include "../Entities/AdventurerEntities.hpp"

class AdventurerDataKeeper
{
public:
	AdventurerDataKeeper()
	{
		fill_adventurer_rarities();
	}
	~AdventurerDataKeeper() = default;
	const adventurer_rarity_vector& get_adventurer_rarities() const { return adventurer_rarities; }
	const adventurer_collection& get_hired() const { return hired; }
	const adventurer_collection& get_available() const { return available; }
	const adventurer_collection& get_dead() const { return dead; }
	const adventurer_collection& get_inactive() const { return inactive; }
	bool recruit(int adventurer_id) { return CollectionIterators::transfer(available, hired, adventurer_id); }
	bool pension(int adventurer_id) { return CollectionIterators::transfer(hired, inactive, adventurer_id); }
	bool kill(int adventurer_id) { return CollectionIterators::transfer(hired, dead, adventurer_id); }
	bool revive(int adventurer_id) { return CollectionIterators::transfer(dead, hired, adventurer_id); }
	void reset()
	{
		available.clear();
		hired.clear();
		dead.clear();
		inactive.clear();
	}
	void add_new_adventurer(std::unique_ptr<Adventurer>&& new_adventurer) { available.push_back(std::move(new_adventurer)); }
	Adventurer* find_available(int adventurer_id) const { return CollectionIterators::find(available, adventurer_id); }
	Adventurer* find_hired(int adventurer_id) const { return CollectionIterators::find(hired, adventurer_id); }
	Adventurer* find_retired(int adventurer_id) const { return CollectionIterators::find(inactive, adventurer_id); }
	Adventurer* find_dead(int adventurer_id) const { return CollectionIterators::find(dead, adventurer_id); }
protected:
	adventurer_rarity_vector adventurer_rarities;
	adventurer_collection available;
	adventurer_collection hired;
	adventurer_collection dead;
	adventurer_collection inactive;
	void fill_adventurer_rarities()
	{
		adventurer_rarities.push_back(AdventurerRarity::Commoner);
		adventurer_rarities.push_back(AdventurerRarity::Adventurer);
		adventurer_rarities.push_back(AdventurerRarity::Hero);
		adventurer_rarities.push_back(AdventurerRarity::Innkeeper);
		adventurer_rarities.push_back(AdventurerRarity::God);
		adventurer_rarities.push_back(AdventurerRarity::DungeonMaster);
	}
};

#endif