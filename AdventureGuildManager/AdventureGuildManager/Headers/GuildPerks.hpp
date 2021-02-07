#ifndef GUILD_PERKS_HPP
#define GUILD_PERKS_HPP

#include "Commands.hpp"
#include "GameEntities.hpp"

// Definition of all guild perk should be here:
// Perk has to be bought by player
// Once bought it will remain until end of game
// Some perks can be bought multiple-times

/*
2-> (Enable Command) Trade fame for gold ?
3->Adventurer Experience gain increased by X % ? (cca 25 ? )
4-> (Enable Command) Retrain adventurer skills randomly ?
5->Can obtain quest of rarity >= 5 ?
6-> (EnableCommand)Upgrade adventurer rarity for X gold ?
7->Fame from retirement increased by X % (like 300 %)
8-> (EnableCommand)Resurrect adventurer for X* level gold ?
9-> Godslayers (Lot of fame gain/lose, can't die, no gold gain/lose)
10-> Overlord of Country
*/

class Godslayer : public ISkill
{
public:
	Godslayer(int id) : ISkill(id, "Hoarder") {}
	void execute_skill(bool& result, Quest& quest, Reward& reward, Penalty& penalty) override
	{
		reward.set_gold(reward.get_gold() * gold_multi);
		reward.set_fame(reward.get_fame() * fame_multi);
		penalty.set_deadly(false);
		penalty.set_gold(penalty.get_gold() *gold_multi);
		penalty.set_fame(penalty.get_fame() * fame_multi);
		
		ChanceGenerator chance;
		result = result || chance.get_chance() > min_to_success;
	}
private:
	const double fame_multi = 10;
	const double gold_multi = 0;
	const int min_to_success = 10;
};

class PerkInterface : public IDisplayeableInterface
{
public:
	std::string to_string() override
	{
		return "Welcome to perk overview!\n";
	}
};

class GuildPerk
{
public:
	GuildPerk(int level_restriction) : guild_level_required(level_restriction) {}
	virtual ~GuildPerk() = default;
	virtual bool fulfill_requirements(GameData& game_data)
	{
		return game_data.current_guild.get_level() >= guild_level_required;
	}
	virtual void execute_guild_perk(Guild& guild) {}
	virtual void execute_quest_perk(Reward& reward, Penalty& penalty) {}
private:
	const int guild_level_required;
};

class PerkTradeFameForGold : public GuildPerk
{
public:
	PerkTradeFameForGold() : GuildPerk(2) { } 
};
class PerkExperienceBonus : public GuildPerk
{
public:
	PerkExperienceBonus() : GuildPerk(3) { }
	void execute_quest_perk(Reward& reward, Penalty& penalty) override
	{
		reward.set_gold(reward.get_gold() * gold_reward_multiplayer);
		penalty.set_gold(penalty.get_gold() * gold_penalty_multiplayer);
	}
private:
	const double gold_reward_multiplayer = 1.25;
	const double gold_penalty_multiplayer = 0.75;
};
class PerkRetrainAdventurer : public GuildPerk
{
public:
	PerkRetrainAdventurer() : GuildPerk(4) { }
};
class PerkQuestRarityUpgrade : public GuildPerk
{
public:
	PerkQuestRarityUpgrade() : GuildPerk(5) { }
	void execute_guild_perk(Guild& guild) override
	{
		guild.set_max_quest_rarity(max_quest_rarity);
	}
private:
	const int max_quest_rarity = static_cast<int>(QuestRarity::Special);
};

class PerkUpgradeAdventurerRarity : public GuildPerk
{
public:
	PerkUpgradeAdventurerRarity() : GuildPerk(6) { }
};

class PerkFamousAdventurers : public GuildPerk
{
public:
	PerkFamousAdventurers() : GuildPerk(7) { }
	void execute_quest_perk(Reward& reward, Penalty& penalty) override
	{
		reward.set_fame(reward.get_fame() * fame_reward_multiplayer);
		penalty.set_fame(penalty.get_fame() * fame_penalty_multiplayer);
	}
private:
	const double fame_reward_multiplayer = 3.0;
	const double fame_penalty_multiplayer = 0.33;
};

class PerkResurrectAdventurer : public GuildPerk
{
public:
	PerkResurrectAdventurer() : GuildPerk(8) { }
};

class PerkGrantGodslayers : public GuildPerk
{
public:
	PerkGrantGodslayers() : GuildPerk(9) { }
};

class PerkOverlordOfCountry : public GuildPerk
{
public:
	PerkOverlordOfCountry() : GuildPerk(10) { }
};


class PerkCommand : public ICommand
{
public:
	PerkCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 1
			&& (command_context[0] == "perk" || command_context[0] == "p");
	}
	std::string execute(GameData& game_data) override
	{
		return interface.to_string();
	}
private:
	PerkInterface interface;
};
class PerkTradeFameToGoldCommand : public ICommand
{
public:
	PerkTradeFameToGoldCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& (command_context[0] == "perk" || command_context[0] == "p")
			&& (command_context[0] == "trade" || command_context[0] == "-t");
	}
	std::string execute(GameData& game_data) override
	{
		int fame_to_convert = InputInterface::get_id(context.size() == 3 ? context[2] : "");
		
		if (trade(game_data, fame_to_convert))
		{

		}
		return interface.to_string();
	}
private:
	bool trade(GameData& game_data, int fame_to_convert)
	{
		if (game_data.current_guild.check_perk())
		{
			// block negative and insufficient fame funds
			if (fame_to_convert > 0 && game_data.current_guild.get_fame() >= fame_to_convert)
			{
				// Substract fame and add gold
				game_data.current_guild.rmv_fame(fame_to_convert);
				game_data.current_guild.add_gold(fame_to_convert * fame_conversion_rate);
				return true;
			}
		}
		return false;
	}
	const int fame_conversion_rate = 10;
	PerkInterface interface;
};
class PerkRetrainAdventurerCommand : public ICommand
{
public:
	PerkRetrainAdventurerCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& (command_context[0] == "perk" || command_context[0] == "p")
			&& (command_context[0] == "retrain" || command_context[0] == "-ret");
	}
	std::string execute(GameData& game_data) override
	{
		int adventurer_id = InputInterface::get_id(context.size() == 3 ? context[2] : "");

		if (retrain(game_data, adventurer_id))
		{

		}
		return interface.to_string();
	}
private:
	bool retrain(GameData& game_data, int adventurer_id)
	{
		if (game_data.current_guild.check_perk())
		{
			const auto adventurer = CollectionIterators::find(game_data.adventurers.get_hired(), adventurer_id);
			const int adventurer_skill_count = adventurer->get_skills().size();
			const int retrain_cost = adventurer_skill_count * retrain_per_skill;
			if (adventurer != nullptr && game_data.current_guild.get_gold() >= retrain_cost)
			{
				// Substract retrain cost
				game_data.current_guild.rmv_gold(retrain_cost);
				// retrain is remove and add (chance that some skill stay is completely fine)
				adventurer->rmv_skill(adventurer_skill_count);
				adventurer->set_skills(game_data.encyclopedia.generate_from_rarity(adventurer_skill_count, adventurer->get_skills()));
				return true;
			}
		}
		return false;
	}
	const int retrain_per_skill = 250;
	PerkInterface interface;
};
class PerkUpgradeAdventurerRarityCommand : public ICommand
{
public:
	PerkUpgradeAdventurerRarityCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& (command_context[0] == "perk" || command_context[0] == "p")
			&& (command_context[0] == "upgrade" || command_context[0] == "-u");
	}
	std::string execute(GameData& game_data) override
	{
		int adventurer_id = InputInterface::get_id(context.size() == 3 ? context[2] : "");

		if (upgrade(game_data, adventurer_id))
		{

		}
		return interface.to_string();
	}
private:
	bool upgrade(GameData& game_data, int adventurer_id)
	{
		if (game_data.current_guild.check_perk())
		{
			const auto adventurer = CollectionIterators::find(game_data.adventurers.get_hired(), adventurer_id);
			const int upgrade_cost = get_cost_multiplayer(adventurer->get_rarity()) * upgrade_cost_per_level;
			if (adventurer != nullptr && game_data.current_guild.get_gold() >= upgrade_cost)
			{
				// Substract upgrade cost
				game_data.current_guild.rmv_gold(upgrade_cost);
				// upgrade
				const int skill_gain = get_skill_gain(adventurer->get_rarity());
				adventurer->set_rarity(AdventurerRarity::DungeonMaster);
				adventurer->set_skills(game_data.encyclopedia.generate_from_rarity(skill_gain, adventurer->get_skills()));
				return true;
			}
		}
		return false;
	}
	int get_cost_multiplayer(AdventurerRarity rarity) const
	{
		return std::clamp(static_cast<int>(AdventurerRarity::DungeonMaster) - static_cast<int>(rarity), 0, 10);
	}
	int get_skill_gain(AdventurerRarity rarity) const
	{
		return std::clamp(static_cast<int>(AdventurerRarity::DungeonMaster) - static_cast<int>(rarity), 0, INT32_MAX);
	}
	const int upgrade_cost_per_level = 250;
	PerkInterface interface;
};
class PerkResurrectAdventurerCommand : public ICommand
{
public:
	PerkResurrectAdventurerCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& (command_context[0] == "perk" || command_context[0] == "p")
			&& (command_context[0] == "resurrect" || command_context[0] == "-res");
	}
	std::string execute(GameData& game_data) override
	{
		int adventurer_id = InputInterface::get_id(context.size() == 3 ? context[2] : "");
		
		if (resurrect(game_data, adventurer_id))
		{
			
		}
		return interface.to_string();
	}
private:
	bool resurrect(GameData& game_data, int adventurer_id)
	{
		if (game_data.current_guild.check_perk())
		{
			const auto adventurer = CollectionIterators::find(game_data.adventurers.get_dead(), adventurer_id);
			const int revive_cost = adventurer->get_level_recruitment_cost() + ressurection_cost;
			if (adventurer != nullptr && game_data.current_guild.get_gold() >= revive_cost)
			{
				// Substract revive cost
				game_data.current_guild.rmv_gold(revive_cost);
				// resurrect
				return game_data.adventurers.revive(adventurer_id);
			}
		}
		return false;
	}
	const int ressurection_cost = 1000;
	PerkInterface interface;
};

class PerkGrantGodslayerCommand : public ICommand
{
public:
	PerkGrantGodslayerCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() >= 2
			&& (command_context[0] == "perk" || command_context[0] == "p")
			&& (command_context[0] == "grant" || command_context[0] == "-g");
	}
	std::string execute(GameData& game_data) override
	{
		int adventurer_id = InputInterface::get_id(context.size() == 3 ? context[2] : "");

		if (grant_godslayer(game_data, adventurer_id))
		{

		}
		return interface.to_string();
	}
private:
	bool grant_godslayer(GameData& game_data, int adventurer_id)
	{
		if (game_data.current_guild.check_perk())
		{
			const auto adventurer = CollectionIterators::find(game_data.adventurers.get_hired(), adventurer_id);
			if (adventurer != nullptr)
			{
				// Grant skill
				adventurer->set_skills(std::make_unique<Godslayer>(1000));
				// Remove option ??? note in perk ??? TODO
				return true;
			}
		}
		return false;
	}
	const int ressurection_cost = 1000;
	PerkInterface interface;
};
#endif