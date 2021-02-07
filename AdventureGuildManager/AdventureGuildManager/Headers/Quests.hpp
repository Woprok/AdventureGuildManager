#ifndef QUESTS_HPP
#define QUESTS_HPP

#include <algorithm>
#include <unordered_set>

#include "GenericEntities.hpp"

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

class QuestTypeWrapper : public NamedEntity
{
public:
	QuestTypeWrapper(QuestType type, std::string type_name, std::string type_desc) : NamedEntity(type_name), desc(type_desc), self(type) { }
	const std::string& get_description() const { return desc; }
	QuestType get_self() const { return self; }
	bool operator==(const QuestTypeWrapper& qtw) const { return qtw.self == self; }
	size_t operator()(const QuestTypeWrapper& qtw) const { return static_cast<size_t>(qtw.self); }
private:
	std::string desc;
	QuestType self;
};

namespace std
{
	template<> struct hash<QuestTypeWrapper>
	{
		std::size_t operator()(QuestTypeWrapper const& s) const noexcept
		{
			return static_cast<size_t>(s.get_self());
		}
	};
}

enum class QuestStateEnum
{
	Success,
	Failure,
	Undefined
};

class Reward
{
public:
	int get_gold() const { return gold; }
	int set_gold(int value) { gold = value; return gold; }
	int get_fame() const { return fame; }
	int set_fame(int value) { fame = value; return fame; }
private:
	int gold = 0;
	int fame = 0;
};

class Penalty : public Reward
{
public:
	bool get_deadly() const { return deadly; }
	bool set_deadly(bool value) { deadly = value; return deadly; }
private:
	bool deadly = true;
};

class Quest : public NamedUniqueEntity
{
public:
	Quest(std::string quest_name) : NamedUniqueEntity(quest_name) {}
	Reward& get_reward() { return reward; }
	Penalty& get_penalty() { return penalty; }
	int get_adventurer_id() const { return adventurer_id; }
	int set_adventurer_id(int value) { adventurer_id = value; return adventurer_id; }
	QuestStateEnum get_state() const { return state; }
	QuestStateEnum set_state(QuestStateEnum value) { state = value; return state; }
	int get_difficulty() const { return difficulty; }
	int set_difficulty(int value) { difficulty = std::clamp(value, 1, 10); return difficulty; }
	std::unordered_set<QuestType>& get_quest_types() { return types; }
	std::unordered_set<QuestType>& set_quest_types(QuestType value) { types.insert(value); return types; }
	bool has_quest_type(QuestType value) { return types.contains(value); }
	QuestRarity get_rarity() const { return rarity; }
	QuestRarity set_rarity(QuestRarity value) { rarity = value; return rarity; }
private:
	Reward reward;
	Penalty penalty;
	QuestStateEnum state = QuestStateEnum::Undefined;
	int adventurer_id = -1;
	int difficulty = 1;
	QuestRarity rarity = QuestRarity::Common;
	std::unordered_set<QuestType> types;
};

#endif