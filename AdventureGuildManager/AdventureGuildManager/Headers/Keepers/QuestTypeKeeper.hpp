#ifndef ENCYCLOPEDIA_KEEPERS_HPP
#define ENCYCLOPEDIA_KEEPERS_HPP

#include <iterator>
#include <random>
#include <unordered_set>

#include "../Entities/QuestEntities.hpp"

typedef std::unordered_set<QuestType> QuestTypeSet;

class QuestTypeKeeper
{
public:
	QuestTypeKeeper()
	{
		fill_quest_types();
	}
	~QuestTypeKeeper() = default;
	QuestTypeSet generate(int count)
	{
		return generate_quest_types(count);
	}
	QuestTypeSet generate(QuestRarity quest_rarity)
	{
		return generate_quest_types(static_cast<int>(quest_rarity));
	}
protected:
	QuestTypeSet quest_types;
	
	void fill_quest_types()
	{
		quest_types.insert(QuestType::Minions);
		quest_types.insert(QuestType::Boss);
		quest_types.insert(QuestType::Poison);
		quest_types.insert(QuestType::Bleeding);
		quest_types.insert(QuestType::Curse);
		quest_types.insert(QuestType::Elfs);
		quest_types.insert(QuestType::Dwarfs);
		quest_types.insert(QuestType::Fairies);
		quest_types.insert(QuestType::Magical);
		quest_types.insert(QuestType::Darkness);
		quest_types.insert(QuestType::Wilderness);
		quest_types.insert(QuestType::Dankness);
		quest_types.insert(QuestType::Memes);
		quest_types.insert(QuestType::Mimes);
	}	
private:
	QuestTypeSet generate_quest_types(int count)
	{
		QuestTypeSet result;
		std::sample(quest_types.begin(),
			quest_types.end(),
			std::inserter(result, result.begin()),
			std::clamp(count, 0, static_cast<int>(quest_types.size())),
			std::mt19937{ std::random_device{}() });
		return result;
	}
};

#endif