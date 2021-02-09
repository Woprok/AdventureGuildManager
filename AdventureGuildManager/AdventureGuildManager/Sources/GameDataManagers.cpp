#include "../Headers/GameDataManagers.hpp"

/// <summary>
/// Basically you need gold, so there is only one way to get gold at start...
/// Due to this we can say that any setting can be done before.
/// And as there is no reason to reset them, they will be kept.
/// </summary>
void GameDataManager::start_game()
{
	GameDataManager::reset_game();
	game_state->change_progress_state(true);
}

void GameDataManager::end_game()
{
	game_state->change_progress_state(false);
}

void GameDataManager::wait_turn()
{
	game_state->turns.add_value(1);

	substract_quest_wait_fees();
	substract_adventurer_wait_fees();
	
	GameDataManager::progress_game();
}

void alter_wait_change(perk_set& perks, int& total_sum)
{
	for (auto&& item : perks)
	{
		item->execute_wait_change(total_sum);
	}
}

void GameDataManager::substract_quest_wait_fees()
{
	const int quest_completed = quests->get_completed().size();
	const int quest_failed = quests->get_failed().size();
	double fee_multiplicator = (quest_failed + 1) / (quest_completed + 1);
	fee_multiplicator = std::clamp(fee_multiplicator,0.5, 1.5);
	
	const int quest_reserved = quests->get_reserved().size();
	int sum = (quest_reserved * DEFAULT_QUEST_RESERVATION_GOLD_RENT) * fee_multiplicator;
	
	alter_wait_change(guild->get_perks(), sum);
	
	guild->base_stats.gold.rmv_value(sum);
	
}
void GameDataManager::substract_adventurer_wait_fees()
{
	int pay_cost = 0;
	for (auto && adventurer : adventurers->get_hired())
	{
		pay_cost += adventurer->living_cost.get_value();
	}
	alter_wait_change(guild->get_perks(), pay_cost);
	
	guild->base_stats.gold.rmv_value(pay_cost);
}

void GameDataManager::progress_game()
{
	const int quest_count = quests->get_available().size();
	if (quest_count <= MIN_QUEST_COUNT)
	{
		const int max_quest_to_generate = MAX_QUEST_COUNT - quest_count;
		const int min_quest_to_generate = std::clamp(MIN_QUEST_COUNT - quest_count, 0, MAX_QUEST_COUNT);
		UniformGenerator generator(min_quest_to_generate, max_quest_to_generate);
		generate_quests(generator.get_next());
	}
	int adventurer_count = adventurers->get_available().size();
	if (adventurer_count <= MIN_ADVENTURER_COUNT)
	{
		const int max_adventurer_to_generate = MAX_ADVENTURER_COUNT - adventurer_count;
		const int min_adventurer_to_generate = std::clamp(MIN_ADVENTURER_COUNT - adventurer_count, 0, MAX_ADVENTURER_COUNT);
		UniformGenerator generator(min_adventurer_to_generate, max_adventurer_to_generate);
		generate_adventurers(generator.get_next());
	}
}

void GameDataManager::generate_quests(int quest_count)
{
	auto&& quest_rarity = guild->max_quest_rarity.get_value();
	auto&& quest_difficulty = game_state->get_difficulty();
	for (int i = 0; i < quest_count; ++i)
	{
		quests->add_new_quest(gen_quests->create_quest(quest_difficulty, quest_rarity));
	}
}

void GameDataManager::generate_adventurers(int adventurer_count)
{
	for (int i = 0; i < adventurer_count; ++i)
	{
		adventurers->add_new_adventurer(gen_adventurers->create_adventurer());
	}
}

void GameDataManager::reset_game()
{
	game_state->reset();
	quests->reset();
	adventurers->reset();
	guild->reset_progress();
}

bool GameDataManager::rename_guild(const std::string& new_guild_name) const
{
	if (new_guild_name.empty())
		return false;
	guild->set_name(new_guild_name);
	return true;
}

int GameDataManager::change_difficulty(const int new_difficulty)
{
	return game_state->set_difficulty(new_difficulty);
}

bool GameDataManager::take_quest(const int quest_id)
{
	return quests->take(quest_id);
}

bool GameDataManager::hire_adventurer(const int adventurer_id)
{
	const auto adventurer = adventurers->find_available(adventurer_id);

	if (adventurer != nullptr && guild->base_stats.gold.get_value() >= adventurer->get_level_recruit_cost())
	{
		// Substract recruit cost
		guild->base_stats.gold.rmv_value(adventurer->get_level_recruit_cost());

		return adventurers->recruit(adventurer_id);
	}

	return false;
}

void alter_retirement_change(perk_set& perks, int& total_sum, int& total_fame)
{
	for (auto&& item : perks)
	{
		item->execute_retirement_change(total_sum, total_fame);
	}
}

bool GameDataManager::pension_adventurer(const int adventurer_id)
{
	const auto adventurer = adventurers->find_hired(adventurer_id);
	int retire_cost = adventurer->get_level_retire_cost();
	int retire_fame = adventurer->get_level_retire_fame();
	alter_retirement_change(guild->get_perks(), retire_cost, retire_fame);
	
	if (adventurer != nullptr && guild->base_stats.gold.get_value() >= retire_cost)
	{
		// Substract retirement cost
		guild->base_stats.gold.rmv_value(retire_cost);
		guild->base_stats.fame.add_value(retire_fame);

		return adventurers->pension(adventurer_id);
	}
	
	return false;
}

bool GameDataManager::trade(int fame_to_convert)
{
	const auto perk = guild->find_perk(TRADE_FAME_PERK);
	
	// block negative and insufficient fame funds
	if (perk != nullptr && fame_to_convert > 0 && guild->base_stats.fame.get_value() >= fame_to_convert)
	{
		// Substract fame and add gold
		guild->base_stats.fame.rmv_value(fame_to_convert);
		guild->base_stats.gold.add_value(fame_to_convert * DEFAULT_FAME_TO_GOLD_RATE);
		return true;
	}
	
	return false;
}

bool GameDataManager::resurrect(int adventurer_id)
{
	const auto perk = guild->find_perk(CHURCH_OF_HEROES_PERK);
	const auto adventurer = adventurers->find_dead(adventurer_id);
	if (adventurer == nullptr || perk == nullptr)
		return false;
	const int revive_cost = adventurer->get_level_recruit_cost() + DEFAULT_RESSURECTION_COST;

	if (guild->base_stats.gold.get_value() >= revive_cost)
	{
		// Substract revive cost
		guild->base_stats.gold.rmv_value(revive_cost);
		// resurrect
		return adventurers->revive(adventurer_id);
	}
	return false;
}

bool GameDataManager::retrain(int adventurer_id)
{
	const auto perk = guild->find_perk(REQUALIFICATION_COURSE_PERK);
	const auto adventurer = adventurers->find_hired(adventurer_id);
	if (adventurer == nullptr || perk == nullptr)
		return false;
	const int adventurer_skill_count = adventurer->get_skills().size();
	const int retrain_cost = adventurer_skill_count * DEFAULT_RETRAIN_COST_PER_SKILL;

	if (guild->base_stats.gold.get_value() >= retrain_cost)
	{
		// Substract retrain cost
		guild->base_stats.gold.rmv_value(retrain_cost);
		// retrain is remove and add (chance that some skill stay is completely fine)
		adventurer->rmv_skill(adventurer_skill_count);
		adventurer->set_skills(std::move(skills->generate(adventurer_skill_count)));
		return true;
	}
	return false;
}

bool GameDataManager::upgrade(int adventurer_id)
{
	const auto perk = guild->find_perk(ARMORY_PERK);
	const auto adventurer = adventurers->find_hired(adventurer_id);
	if (adventurer == nullptr || perk == nullptr)
		return false;
	const int rarity_diff = std::clamp(static_cast<int>(AdventurerRarity::Innkeeper) - static_cast<int>(adventurer->rarity.get_value()),
			0, 10);
	if (rarity_diff <= 0)
		return false;
	const int upgrade_cost = rarity_diff * DEFAULT_UPGRADE_COST_PER_RARITY_DIFF;

	if (guild->base_stats.gold.get_value() >= upgrade_cost)
	{
		// Substract retrain cost
		guild->base_stats.gold.rmv_value(upgrade_cost);
		// retrain is remove and add (chance that some skill stay is completely fine)
		adventurer->rarity.set_value(AdventurerRarity::Innkeeper);
		adventurer->set_skills(std::move(skills->generate(rarity_diff, adventurer->get_skills())));
		return true;
	}
	return false;
}

bool GameDataManager::grant_godslayer(int adventurer_id)
{
	const auto perk = guild->find_perk(MADNESS_OF_MASTER_PERK);
	const auto adventurer = adventurers->find_hired(adventurer_id);
	if (adventurer == nullptr || perk == nullptr)
		return false;
	const int godslayer_cost = DEFAULT_GODSLAYER_COST;

	if (guild->base_stats.fame.get_value() >= godslayer_cost)
	{
		// Substract slayer cost
		guild->base_stats.fame.rmv_value(godslayer_cost);

		// Upgrade to god status
		const int rarity_diff = static_cast<int>(AdventurerRarity::God) - static_cast<int>(adventurer->rarity.get_value());
		if (rarity_diff > 0)
		{
			adventurer->rarity.set_value(AdventurerRarity::God);
			adventurer->set_skills(std::move(skills->generate(rarity_diff, adventurer->get_skills())));
		}

		adventurer->set_skills(skills->create_skill(GODSLAYER_ID));
		return true;
	}
	return false;
}

void alter_guild_stats(Guild* guild)
{
	int change_rarity = guild->max_quest_rarity.get_value();

	for (auto&& item : guild->get_perks())
	{
		item->execute_gain_change(guild->base_stats, change_rarity);
	}
	guild->max_quest_rarity.set_value(change_rarity);
}

bool GameDataManager::buy_perk(int perk_id)
{
	if (guild->find_perk(perk_id) != nullptr)
		return false;
	auto&& created_perk = perks->create_perk(perk_id);
	const int perk_cost = DEFAULT_COST_PER_LEVEL_PERK * created_perk->level_requirement.get_value();
	if (guild->base_stats.gold.get_value() >= perk_cost && guild->get_prestige_level() >= created_perk->level_requirement.get_value())
	{
		// Substract slayer cost
		guild->base_stats.gold.rmv_value(perk_cost);
		guild->set_perks(std::move(created_perk));
				
		alter_guild_stats(guild.get());
		return true;
	}
	return false;
}