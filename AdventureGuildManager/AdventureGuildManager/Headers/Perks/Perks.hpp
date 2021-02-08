﻿#ifndef GUILD_PERKS_HPP
#define GUILD_PERKS_HPP

#include "../Interfaces/IPerks.hpp"

/// <summary>
/// Reduce fame and increase gold.
/// </summary>
class TradeFame : public IPerk
{
public:
	TradeFame() : IPerk("Rough Job", 0, 
		"Sacrifice fame for gold.", 2) { }
	~TradeFame() override = default;
};
/// <summary>
/// Randomize skills of selected adventurer.
/// </summary>
class RequalificationCourse : public IPerk
{
public:
	RequalificationCourse() : IPerk("Requalification Course", 1,
		"Trader provided us with manual of many things.", 4) { }
	~RequalificationCourse() override = default;
};
/// <summary>
/// Upgrade adventurer rarity.
/// </summary>
class Armory : public IPerk
{
public:
	Armory() : IPerk("Armory", 2,
		"Some heroes are born genius, other are equipped with many artifacts.", 6) { }
	~Armory() override = default;
};
/// <summary>
/// Grant ability to revive heroes.
/// </summary>
class ChurchOfHeroes : public IPerk
{
public:
	ChurchOfHeroes() : IPerk("Foundation of religion", 3,
		"Did somebody said we can't bring back corpses ?", 8) { }
	~ChurchOfHeroes() override = default;
};
/// <summary>
/// Grant new skill to a selected hero.
/// </summary>
class MadnessOfMaster : public IPerk
{
public:
	MadnessOfMaster() : IPerk("Master and guide to hypemaster", 4,
		"Certainly something good will come from this?", 10) { }
	~MadnessOfMaster() override = default;
};

/// <summary>
/// Increase experience from quest.
/// </summary>
class SharedExperience : public IPerk
{
public:
	SharedExperience() : IPerk("Veterans", 5, 
		"One tip can save life or improve growth.", 3) { }
//	void execute_quest_perk(Reward& reward, Penalty& penalty) override
//	{
//		reward.set_gold(reward.get_gold() * gold_reward_multiplayer);
//		penalty.set_gold(penalty.get_gold() * gold_penalty_multiplayer);
//	}
private:
	const double gold_reward_multiplayer = 1.25;
	const double gold_penalty_multiplayer = 0.75;
};
/// <summary>
/// Reduce retirement cost and living expenses.
/// </summary>
class RetirementSavings : public IPerk
{
public:
	RetirementSavings() : IPerk("Retirement fund", 6,
		"More money for guild is always better.", 5) { }
};
/// <summary>
/// Increase max quest rarity
/// </summary>
class DangerousExpeditions : public IPerk
{
public:
	DangerousExpeditions() : IPerk("Dangerous Expeditions", 7,
		"You said we can't go ? Well let's go.", 7) { }
	//	void execute_quest_perk(Reward& reward, Penalty& penalty) override
	//	{
	//		guild.set_max_quest_rarity(max_quest_rarity);
	//	}
	//private:
	//	const int max_quest_rarity = static_cast<int>(QuestRarity::Special);
};
/// <summary>
/// Increase fame gain from retirement.
/// </summary>
class LegendaryHeroes : public IPerk
{
public:
	LegendaryHeroes() : IPerk("Legendary Heroes", 8,
		"Bard do your job or you will be thrown to jail.", 9) { }
	//	void execute_quest_perk(Reward& reward, Penalty& penalty) override
	//	{
	//		reward.set_fame(reward.get_fame()* fame_reward_multiplayer);
	//		penalty.set_fame(penalty.get_fame()* fame_penalty_multiplayer);
	//	}
	//private:
	// const double fame_reward_multiplayer = 3.0;
	// const double fame_penalty_multiplayer = 0.33;
};

#endif