#ifndef GUILDS_HPP
#define GUILDS_HPP

#include <algorithm>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "BasicEntities.hpp"
#include "CommonDataEntities.hpp"
#include "../Interfaces/IPerks.hpp"

typedef std::unordered_set<std::unique_ptr<IPerk>> perk_set;

class Guild : public IdNameEntity
{
public:
	Guild(std::string& new_name, GoldFameData& new_base_stats, int new_difficulty)
		: IdNameEntity(new_name, auto_id++), base_stats(new_base_stats), difficulty(new_difficulty) { }
	~Guild() = default;

	GoldFameData base_stats;
	GetSetEntity<int> max_quest_rarity = GetSetEntity<int>(5);
	
	int get_difficulty() const { return difficulty.get_value(); }
	int set_difficulty(int value) { difficulty.set_value(std::clamp(value, 1, 10)); return difficulty.get_value(); }

	int get_level() const { return std::clamp(1 + base_stats.fame.get_value() / 1000, 1, 10); }
	
	perk_set& get_perks() { return perks; }
	perk_set& set_perks(std::unique_ptr<IPerk>&& new_perk) { perks.insert(std::move(new_perk)); return perks; }

protected:
	inline static int auto_id = 0;
	GetSetEntity<int> difficulty = GetSetEntity<int>(1);
	perk_set perks {};
};

#endif