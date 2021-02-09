#ifndef GUILD_PERKS_HPP
#define GUILD_PERKS_HPP

#include "../Interfaces/IPerks.hpp"

constexpr int GODSLAYER_ID = 0;
constexpr int TRADE_FAME_PERK = 0;
constexpr int REQUALIFICATION_COURSE_PERK = 1;
constexpr int ARMORY_PERK = 2;
constexpr int CHURCH_OF_HEROES_PERK = 3;
constexpr int MADNESS_OF_MASTER_PERK = 4;
constexpr int SHARED_EXPERIENCE_PERK = 5;
constexpr int RETIREMENT_SAVINGS_PERK = 6;
constexpr int DANGEROUS_EXPEDITION_PERK = 7;
constexpr int LEGENDARY_HEROES_PERK = 8;

/// <summary>
/// Reduce fame and increase gold.
/// </summary>
class TradeFame : public IPerk
{
public:
	TradeFame() : IPerk("Rough Job", TRADE_FAME_PERK,
		"Sacrifice fame for more gold.", 2) { }
	~TradeFame() override = default;
};
/// <summary>
/// Randomize skills of selected adventurer.
/// </summary>
class RequalificationCourse : public IPerk
{
public:
	RequalificationCourse() : IPerk("Requalification Course", REQUALIFICATION_COURSE_PERK,
		"Trader provided us with manual of many things. Randomize skill of adventurer.", 4) { }
	~RequalificationCourse() override = default;
};
/// <summary>
/// Upgrade adventurer rarity.
/// </summary>
class Armory : public IPerk
{
public:
	Armory() : IPerk("Armory", ARMORY_PERK,
		"Some heroes are born genius, other are equipped with many artifacts. Upgrade rarity of adventurer.", 6) { }
	~Armory() override = default;
};
/// <summary>
/// Grant ability to revive heroes.
/// </summary>
class ChurchOfHeroes : public IPerk
{
public:
	ChurchOfHeroes() : IPerk("Foundation of religion", CHURCH_OF_HEROES_PERK,
		"Did somebody said we can't bring back corpses ? Resurrect dead adventurer.", 8) { }
	~ChurchOfHeroes() override = default;
};
/// <summary>
/// Grant new skill to a selected hero.
/// </summary>
class MadnessOfMaster : public IPerk
{
public:
	MadnessOfMaster() : IPerk("Master and guide to hypemaster", MADNESS_OF_MASTER_PERK,
		"Certainly something good will come from this? Obtain special skill for adventurer.", 10) { }
	~MadnessOfMaster() override = default;
};

/// <summary>
/// Increase experience from quest.
/// </summary>
class SharedExperience : public IPerk
{
public:
	SharedExperience() : IPerk("Veterans", SHARED_EXPERIENCE_PERK,
		"One tip can save life or improve growth.", 3) { }
	void execute_reward_change(GoldFameData& data, int& experience) override
	{
		experience = experience * experience_reward_multiplayer;
	}
	void execute_penalty_change(GoldFameDeadlyData& data, int& experience) override
	{
		experience = experience * experience_penalty_multiplayer;
	}
private:
	const double experience_reward_multiplayer = 1.25;
	const double experience_penalty_multiplayer = 0.75;
};
/// <summary>
/// Reduce retirement cost and living & reserve expenses.
/// </summary>
class RetirementSavings : public IPerk
{
public:
	RetirementSavings() : IPerk("Retirement fund", RETIREMENT_SAVINGS_PERK,
		"More money for guild is always better. Reduce retirement cost and guild expenses during wait.", 5) { }
	void execute_wait_change(int& expenses_total) override
	{
		expenses_total = expenses_total * wait_cost_reduction;
	}
	void execute_retirement_change(int& retirement_total, int& retirement_fame) override
	{
		retirement_total = retirement_total * retire_cost_reduction;
	}
private:
	const double wait_cost_reduction = 0.75;
	const double retire_cost_reduction = 0.25;
};
/// <summary>
/// Increase max quest rarity
/// Grant fame each time a perk is gained.
/// </summary>
class DangerousExpeditions : public IPerk
{
public:
	DangerousExpeditions() : IPerk("Dangerous Expeditions", DANGEROUS_EXPEDITION_PERK,
		"You said we can't go ? Well let's go.", 7) { }
	void execute_gain_change(GoldFameData& data, int& max_quest_rarity) override
	{
		data.fame.set_value(data.fame.get_value() + bonus_fame);
		max_quest_rarity = up_max_quest_rarity;
	}
private:
	const int bonus_fame = 500;
	const int up_max_quest_rarity = static_cast<int>(QuestRarity::Special);
};
/// <summary>
/// Increase fame gain from retirement and quests.
/// </summary>
class LegendaryHeroes : public IPerk
{
public:
	LegendaryHeroes() : IPerk("Legendary Heroes", LEGENDARY_HEROES_PERK,
		"Bard do your job or you will be thrown to jail. More fame from quest and retirement. Failed quests are less harsh on fame.", 9) { }
	void execute_reward_change(GoldFameData& data, int& experience) override
	{
		data.fame.set_value(data.fame.get_value() * bonus_fame_factor);
	}
	void execute_penalty_change(GoldFameDeadlyData& data, int& experience) override
	{
		data.fame.set_value(data.fame.get_value() * reduction_fame_factor);
	}
	void execute_retirement_change(int& retirement_total, int& retirement_fame) override
	{
		retirement_fame = retirement_fame * retire_fame_bonus;
	}
private:
	const double bonus_fame_factor = 3.0;
	const double reduction_fame_factor = 0.33;
	const double retire_fame_bonus = 5.0;
};

#endif