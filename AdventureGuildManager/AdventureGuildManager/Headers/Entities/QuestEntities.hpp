#ifndef QUEST_ENTITIES_HPP
#define QUEST_ENTITIES_HPP

#include <algorithm>
#include <memory>
#include <string>
#include <unordered_set>

#include "BasicEntities.hpp"
#include "CommonDataEntities.hpp"

constexpr int MIN_QUEST_DIFFICULTY = 1;
constexpr int MAX_QUEST_DIFFICULTY = 10;

enum class QuestRarity
{
	Common = 0,
	Uncommon = 1,
	Rare = 2,
	Epic = 3,
	War = 4, 
	Legendary = 5,
	Campaign = 6,
	Special = 7,
};

enum class QuestStateEnum
{
	Success,
	Failure,
	Undefined
};

enum class QuestType
{
	Minions = 1,
	Boss = 2,
	Poison = 3,
	Bleeding = 4,
	Curse = 5,
	Elfs = 6,
	Dwarfs = 7,
	Fairies = 8,
	Magical = 9,
	Darkness = 10,
	Wilderness = 11,
	Dankness = 12,
	Memes = 13,
	Mimes = 14,
};

typedef std::vector<QuestRarity> quest_rarity_vector;
typedef std::unordered_set<QuestType> quest_type_set;

class Quest : public IdNameEntity
{
public:
	Quest(std::string& new_name, GoldFameData& reward_data, GoldFameDeadlyData& penalty_data, 
		  QuestRarity new_rarity, int new_difficulty, quest_type_set& new_set_of_types)
		: IdNameEntity(new_name, auto_id++), reward(reward_data), penalty(penalty_data), adventurer(-1),
		  rarity(new_rarity), state(QuestStateEnum::Undefined)
	{
		difficulty.set_value(new_difficulty);
		set_quest_types(new_set_of_types);
	}

	virtual ~Quest() = default;
	GoldFameData reward;
	GoldFameDeadlyData penalty;
	GetSetEntity<int> adventurer;
	GetSetEntity<QuestRarity> rarity;
	GetSetEntity<QuestStateEnum> state;
	
	int get_difficulty() const { return difficulty.get_value(); }
	int set_difficulty(int value) { difficulty.set_value(std::clamp(value, MIN_QUEST_DIFFICULTY, MAX_QUEST_DIFFICULTY)); return difficulty.get_value(); }

	quest_type_set& get_quest_types() { return types; }
	quest_type_set& set_quest_types(QuestType new_value) { types.insert(new_value); return types; }
	quest_type_set& set_quest_types(quest_type_set& new_set_of_types)
	{
		types.merge(new_set_of_types);
		return types;
	}
	bool has_quest_type(QuestType find_type) const { return types.contains(find_type); }

protected:
	inline static int auto_id = 0;
	GetSetEntity<int> difficulty = GetSetEntity<int>(1);
	quest_type_set types {};
};

typedef std::vector<std::unique_ptr<Quest>> quest_collection;

#endif