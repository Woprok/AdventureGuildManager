#ifndef ADVENTURER_ENTITIES_HPP
#define ADVENTURER_ENTITIES_HPP

#include <algorithm>
#include <memory>
#include <random>
#include <string>
#include <unordered_set>

#include "BasicEntities.hpp"
#include "../Interfaces/ISkills.hpp"

enum class AdventurerRarity
{
	Commoner = 0,
	Adventurer = 1,
	Hero = 2,
	Innkeeper = 3,
	God = 4,
	DungeonMaster = 10
};

typedef std::unordered_set<int> quest_set;

class Adventurer : public IdNameEntity
{
public:
	Adventurer(std::string& new_name, AdventurerRarity new_rarity, int new_experience,
		int new_recruit_cost, int new_retire_cost, int new_living_cost, skill_set& new_skill_set)
		: IdNameEntity(new_name, auto_id++), rarity(new_rarity), recruit_cost(new_recruit_cost),
		  retire_cost(new_retire_cost), living_cost(new_living_cost), experience(new_experience)
	{
		set_skills(new_skill_set);
	}

	virtual ~Adventurer() = default;
	
	GetSetEntity<AdventurerRarity> rarity;
	GetSetEntity<int> recruit_cost;
	GetSetEntity<int> retire_cost;
	GetSetEntity<int> living_cost;
	ChangeEntity<int> experience;

	int get_retire_fame() const { return std::clamp(success_quests.size() - failure_quests.size(), 1ull, 100ull); }

	int get_level() const { return std::clamp(1 + experience.get_value() / 1000, 1, 10); }

	int get_level_recruit_cost() const { return get_level() * recruit_cost.get_value(); }
	int get_level_retire_cost() const { return get_level() * retire_cost.get_value(); }
	int get_level_retire_fame() const { return get_level() * get_retire_fame(); }
	
	quest_set& get_success_quests() { return success_quests; }
	quest_set& set_success_quests(int value) { success_quests.insert(value); return success_quests; }
	quest_set& get_failure_quests() { return failure_quests; }
	quest_set& set_failure_quests(int value) { failure_quests.insert(value); return failure_quests; }

	skill_set& get_skills() { return skills; }
	skill_set& set_skills(std::unique_ptr<ISkill>&& new_skill) { skills.insert(std::move(new_skill)); return skills; }
	skill_set& set_skills(skill_set& new_skill_set)	{ skills.merge(new_skill_set); return skills; }
	/// <summary>
	/// Attempt to remove del_count of skills from adventurer in random order.
	/// </summary>
	void rmv_skill(int del_count)
	{
		for (int i = 0; i < del_count; ++i)
		{
			if (!skills.empty())
			{
				std::uniform_int_distribution<unsigned> d(0, skills.size() - 1);

				// returns a random number from [0, skills.size() - 1]
				unsigned r = d(Adventurer::rng);
				
				// iterates through the container to the r-th element
				auto it = skills.begin();
				for (; it != skills.end() && r > 0; ++it, r--) {}

				skills.erase(it);
			}
		}
	}
protected:
	inline static int auto_id = 0;
	quest_set success_quests{};
	quest_set failure_quests{};
	skill_set skills {};
	inline static std::mt19937 rng{ std::random_device{}() }; // this class generator
};

typedef std::vector<std::unique_ptr<Adventurer>> adventurer_collection;

#endif