#ifndef ADVENTURERS_HPP
#define ADVENTURERS_HPP

#include <memory>

#include "Skills.hpp"

enum class AdventurerRarity
{
	Adventurer = 1,
	Hero = 2,
	Innkeeper = 3,
	DungeonMaster = 5
};

class Adventurer : public NamedUniqueEntity
{
public:
	Adventurer(std::string adventurer_name) : NamedUniqueEntity(adventurer_name) {}
	std::unordered_set<int>& get_succ_quest_ids() { return succ_quest_ids; }
	std::unordered_set<int>& set_succ_quest_id(int value) { succ_quest_ids.insert(value); return succ_quest_ids; }
	std::unordered_set<int>& get_fail_quest_ids() { return fail_quest_ids; }
	std::unordered_set<int>& set_fail_quest_id(int value) { fail_quest_ids.insert(value); return fail_quest_ids; }
	int get_recruitment_cost() const { return recruitment_cost; }
	int set_recruitment_cost(int value) { recruitment_cost = value; return recruitment_cost; }
	int get_retirement_cost() const { return retirement_cost; }
	int set_retirement_cost(int value) { retirement_cost = value; return retirement_cost; }
	int get_living_expenses() const { return living_expenses; }
	int set_living_expenses(int value) { living_expenses = value; return living_expenses; }
	int get_experience() const { return experience; }
	int set_experience(int value) { experience = value; return experience; }
	int add_experience(int value) { experience += value; return experience; }
	int rmv_experience(int value) { experience -= value; return experience; }
	int get_retirement_fame() { return std::clamp(succ_quest_ids.size() - fail_quest_ids.size(), 1ull, 100ull); }
	int get_level() { return std::clamp(1 + experience / 1000, 1, 10); }
	int get_level_recruitment_cost() { return get_level() * recruitment_cost; }
	int get_level_retirement_fame() { return get_level() * get_retirement_fame(); }
	int get_level_retirement_cost() { return get_level() * retirement_cost; }
	skill_collection& get_skills() { return skills; }
	skill_collection& set_skills(std::unique_ptr<ISkill>&& value) { skills.insert(std::move(value)); return skills; }
	AdventurerRarity get_rarity() const { return rarity; }
	AdventurerRarity set_rarity(AdventurerRarity value) { rarity = value; return rarity; }
private:
	std::unordered_set<int> succ_quest_ids;
	std::unordered_set<int> fail_quest_ids;
	int recruitment_cost = 0;
	int retirement_cost = 0;
	int living_expenses = 0;
	int experience = 0;
	AdventurerRarity rarity = AdventurerRarity::Adventurer;
	skill_collection skills;
};

#endif