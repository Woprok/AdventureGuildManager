#ifndef QUESTS_HPP
#define QUESTS_HPP

#include <algorithm>
#include <unordered_set>

#include "GenericEntities.hpp"

enum class QuestType
{
	Minions,
	Boss,
	Poison,
	Bleeding,
	Curse,
	Elfs,
	Dwarfs,
	Fairies,
	Magical,
	Darkness,
	Wilderness,
	Dankness,
	Memes,
	Mimes,
};

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
private:
	Reward reward;
	Penalty penalty;
	QuestStateEnum state = QuestStateEnum::Undefined;
	int adventurer_id = -1;
	int difficulty = 1;
	std::unordered_set<QuestType> types;
};

#endif