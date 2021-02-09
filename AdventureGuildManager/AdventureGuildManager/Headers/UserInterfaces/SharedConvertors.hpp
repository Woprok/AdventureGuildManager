#ifndef SHARED_CONVERTORS_HPP
#define SHARED_CONVERTORS_HPP

#include "../Entities/AdventurerEntities.hpp"
#include "../Entities/QuestEntities.hpp"

class SharedConvertors
{
public:
	static std::string translate_state(QuestStateEnum quest_state)
	{
		switch (quest_state)
		{
			case QuestStateEnum::Success: return "Success";
			case QuestStateEnum::Failure: return "Failure";
			case QuestStateEnum::Undefined: return "Ignored";
			default: return "Undefined";
		}
	}
	static std::string translate_quest_rarity(QuestRarity quest_rarity)
	{
		switch (quest_rarity)
		{
			case QuestRarity::Common: return "Common";
			case QuestRarity::Uncommon: return "Uncommon";
			case QuestRarity::Rare: return "Rare";
			case QuestRarity::Epic: return "Epic";
			case QuestRarity::War: return "War";
			case QuestRarity::Legendary: return "Legendary";
			case QuestRarity::Campaign: return "Campaign";
			case QuestRarity::Special: return "Special";
			default: return "Undefined";
		}
	}
	static std::string translate_quest_rarity_description(QuestRarity quest_rarity)
	{
		switch (quest_rarity)
		{
			case QuestRarity::Common: return "Peasant requests. Not worth of much.";
			case QuestRarity::Uncommon: return "Mayor requests. Clearly town needs us.";
			case QuestRarity::Rare: return "Noble requests. At least it pays well.";
			case QuestRarity::Epic: return "Killing rat was never as epic as this.";
			case QuestRarity::War: return "Why are we participating in war ?";
			case QuestRarity::Legendary: return "Search for a way how to engrave your name in history.";
			case QuestRarity::Campaign: return "Did you decided that you can finish a whole campaign ?";
			case QuestRarity::Special: return "God spoke and so we do as he wishes.";
			default: return "Undefined";
		}
	}
	static std::string translate_quest_type(QuestType quest_type)
	{
		switch (quest_type)
		{
			case QuestType::Minions: return "Minions";
			case QuestType::Boss: return "Boss";
			case QuestType::Poison: return "Poison";
			case QuestType::Bleeding: return "Bleeding";
			case QuestType::Curse: return "Curse";
			case QuestType::Elfs: return "Elfs";
			case QuestType::Dwarfs: return "Dwarfs";
			case QuestType::Fairies: return "Fairies";
			case QuestType::Magical: return "Magical";
			case QuestType::Darkness: return "Darkness";
			case QuestType::Wilderness: return "Wilderness";
			case QuestType::Dankness: return "Darkness";
			case QuestType::Memes: return "Memes";
			case QuestType::Mimes: return "Mimes";
			default: return "Undefined";
		}
	}
	static std::string translate_quest_type_description(QuestType quest_type)
	{
		switch (quest_type)
		{
			case QuestType::Minions: return "Swarm of enemies.";
			case QuestType::Boss: return "Villain worthy to face your champion.";
			case QuestType::Poison: return "Please do not consume or get in contact with.";
			case QuestType::Bleeding: return "Pointy things are too dangerous for you.";
			case QuestType::Curse: return "It was not brightest idea to desecrate graves.";
			case QuestType::Elfs: return "Humans with pointy ears.";
			case QuestType::Dwarfs: return "Humans with long beards.";
			case QuestType::Fairies: return "Humans with wing and glitters";
			case QuestType::Magical: return "Magical runes are fun.";
			case QuestType::Darkness: return "Are you saying darkvision does not work here ?";
			case QuestType::Wilderness: return "Unexplored lands are easy to survive.";
			case QuestType::Dankness: return "This town is super strange.";
			case QuestType::Memes: return "This group is worse then old hag curse.";
			case QuestType::Mimes: return "In seven layers of hell, what are you doing here ?";
			default: return "Undefined";
		}
	}
	static std::string translate_adventurer_rarity(AdventurerRarity rarity)
	{
		switch (rarity)
		{
			case AdventurerRarity::Commoner: return "Commoner";
			case AdventurerRarity::Adventurer: return "Adventurer";
			case AdventurerRarity::Hero: return "Hero";
			case AdventurerRarity::Innkeeper: return "Innkeeper";
			case AdventurerRarity::God: return "God";
			case AdventurerRarity::DungeonMaster: return "DungeonMaster";
			default: return "Undefined";
		}
	}
	static std::string translate_adventurer_rarity_description(AdventurerRarity rarity)
	{
		switch (rarity)
		{
			case AdventurerRarity::Commoner: return "Recruiting young folks is like hiring meat shield.";
			case AdventurerRarity::Adventurer: return "This guy already survived his first goblin.";
			case AdventurerRarity::Hero: return "Why all heroes wear shiny armors?";
			case AdventurerRarity::Innkeeper: return "Seriously do not engage this one.";
			case AdventurerRarity::God: return "How did god become adventurer ?";
			case AdventurerRarity::DungeonMaster: return "Rock falls, you die.";
			default: return "Undefined";
		}
	}
};

#endif