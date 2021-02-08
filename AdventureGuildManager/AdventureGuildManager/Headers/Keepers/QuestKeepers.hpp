#ifndef QUEST_KEEPERS_HPP
#define QUEST_KEEPERS_HPP

#include "../Entities/QuestEntities.hpp"
#include "../Helpers/CollectionIterators.hpp"
#include "../Helpers/Generators.hpp"

class QuestKeeper
{
public:
	std::unique_ptr<Quest> create_quest(EncyclopediaKeeper& keep)
	{
		auto&& quest = std::make_unique<Quest>(name_generator.create_quest_name());
		quest->get_reward().set_gold(100);
		quest->get_reward().set_fame(10);
		quest->get_penalty().set_gold(100);
		quest->get_penalty().set_fame(10);
		quest->set_difficulty(2);
		quest->set_rarity(QuestRarity::Epic);
		quest->set_quest_types(keep.generate_from_rarity(quest->get_rarity()));
		return std::move(quest);
	}
	void generate(EncyclopediaKeeper& keep, int count)
	{
		for (int i = 0; i < count; ++i)
		{
			available.push_back(create_quest(keep));
		}
	}
	void clear()
	{
		available.clear();
		reserved.clear();
		completed.clear();
		failed.clear();
	}
	bool take(int quest_id)
	{
		return CollectionIterators::transfer(available, reserved, quest_id);
	}
	bool complete(int quest_id)
	{
		return CollectionIterators::transfer(reserved, completed, quest_id);
	}
	bool fail(int quest_id)
	{
		return CollectionIterators::transfer(reserved, failed, quest_id);
	}

	const quest_collection& get_available() { return available; }
	const quest_collection& get_reserved() { return reserved; }
	const quest_collection& get_completed() { return completed; }
	const quest_collection& get_failed() { return failed; }
private:
	quest_collection available;
	quest_collection reserved;
	quest_collection completed;
	quest_collection failed;
	NameGenerator name_generator;
};

#endif