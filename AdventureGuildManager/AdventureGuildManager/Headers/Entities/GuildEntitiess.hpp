#ifndef GUILDS_HPP
#define GUILDS_HPP

#include <algorithm>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "BasicEntities.hpp"
#include "CommonDataEntities.hpp"
#include "../Helpers/CollectionIterators.hpp"
#include "../Interfaces/IPerks.hpp"

constexpr int MIN_GUILD_LEVEL = 1;
constexpr int MAX_GUILD_LEVEL = 10;
constexpr int DEFAULT_GUILD_QUEST_RARITY = 3;
constexpr int DEFAULT_GUILD_GOLD_COUNT = 2000;
constexpr int DEFAULT_GUILD_FAME_COUNT = 100;

class Guild : public IdNameEntity
{
public:
	Guild(std::string&& new_name, GoldFameData&& new_base_stats)
		: IdNameEntity(std::move(new_name), auto_id++), base_stats(new_base_stats) { }
	~Guild() = default;

	GoldFameData base_stats;
	GetSetEntity<int> max_quest_rarity = GetSetEntity<int>(DEFAULT_GUILD_QUEST_RARITY);
	
	int get_prestige_level() const { return std::clamp(1 + base_stats.fame.get_value() / 1000, MIN_GUILD_LEVEL, MAX_GUILD_LEVEL); }
	
	perk_set& get_perks() { return perks; }
	perk_set& set_perks(std::unique_ptr<IPerk>&& new_perk) { perks.insert(std::move(new_perk)); return perks; }
	void reset_progress()
	{
		perks.clear();
		base_stats.gold.set_value(DEFAULT_GUILD_GOLD_COUNT);
		base_stats.fame.set_value(DEFAULT_GUILD_FAME_COUNT);
		max_quest_rarity.set_value(DEFAULT_GUILD_QUEST_RARITY);
	}

	void add_new_perk(std::unique_ptr<IPerk>&& new_perk) { perks.insert(std::move(new_perk)); }

	IPerk* find_perk(int perk_id) const { return CollectionIterators::find(perks, perk_id); }
protected:
	inline static int auto_id = 0;
	perk_set perks {};
};

#endif