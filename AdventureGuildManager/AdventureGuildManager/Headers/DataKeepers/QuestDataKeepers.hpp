#ifndef QUEST_DATA_KEEPERS_HPP
#define QUEST_DATA_KEEPERS_HPP

#include <unordered_set>
#include <vector>

#include "../Helpers/CollectionIterators.hpp"
#include "../Entities/QuestEntities.hpp"

class QuestDataKeeper
{
public:
	QuestDataKeeper()
	{
		fill_quest_types();
		fill_quest_rarities();
	}
	~QuestDataKeeper() = default;
	const quest_type_set& get_quest_types() const { return quest_types; }
	const quest_rarity_vector& get_quest_rarities() const { return quest_rarities; }
	const quest_collection& get_available() const { return available; }
	const quest_collection& get_reserved() const { return reserved; }
	const quest_collection& get_completed() const { return completed; }
	const quest_collection& get_failed() const { return failed; }

	bool take(int quest_id)	{ return CollectionIterators::transfer(available, reserved, quest_id); }
	bool complete(int quest_id)	{ return CollectionIterators::transfer(reserved, completed, quest_id); }
	bool fail(int quest_id)	{ return CollectionIterators::transfer(reserved, failed, quest_id); }
	void reset()
	{
		available.clear();
		reserved.clear();
		completed.clear();
		failed.clear();
	}
	void add_new_quest(std::unique_ptr<Quest>&& new_quest) { available.push_back(std::move(new_quest)); }
	Quest* find_available(int quest_id) const { return CollectionIterators::find(available, quest_id); }
	Quest* find_reserved(int quest_id) const { return CollectionIterators::find(reserved, quest_id); }
	Quest* find_completed(int quest_id) const { return CollectionIterators::find(completed, quest_id); }
	Quest* find_failed(int quest_id) const { return CollectionIterators::find(failed, quest_id); }
	Quest* find_quest(int quest_id) const
	{
		auto result = CollectionIterators::find(failed, quest_id);
		if (result == nullptr)
			result = CollectionIterators::find(completed, quest_id);
		if (result == nullptr)
			result = CollectionIterators::find(reserved, quest_id);
		if (result == nullptr)
			result = CollectionIterators::find(available, quest_id);
		return result;
	}
protected:
	quest_type_set quest_types;
	quest_rarity_vector quest_rarities;
	quest_collection available;
	quest_collection reserved;
	quest_collection completed;
	quest_collection failed;
	
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
	void fill_quest_rarities()
	{
		quest_rarities.push_back(QuestRarity::Common);
		quest_rarities.push_back(QuestRarity::Uncommon);
		quest_rarities.push_back(QuestRarity::Rare);
		quest_rarities.push_back(QuestRarity::Epic);
		quest_rarities.push_back(QuestRarity::War);
		quest_rarities.push_back(QuestRarity::Legendary);
		quest_rarities.push_back(QuestRarity::Campaign);
		quest_rarities.push_back(QuestRarity::Special);
	}
};

#endif