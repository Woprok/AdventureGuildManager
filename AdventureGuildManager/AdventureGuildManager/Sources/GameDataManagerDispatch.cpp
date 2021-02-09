#include "../Headers/GameDataManagers.hpp"

constexpr int QUEST_COMPARE_BASE_MINPOINT = 10;
constexpr int QUEST_COMPARE_BASE_MIDPOINT = 51;
constexpr int QUEST_COMPARE_BASE_MAXPOINT = 90;

int GameDataManager::get_experience_change(int quest_difficulty, int adventurer_level)
{
	const int base = 1000;
	const int quest_multiplier = MAX_QUEST_DIFFICULTY + 1 - quest_difficulty; // Reverse the value
	const int quest_reward = std::clamp((base / quest_multiplier), MIN_QUEST_EXPERIENCE_CHANGE_BASE, MAX_QUEST_EXPERIENCE_CHANGE_BASE);
	const int level_bonus = quest_difficulty / adventurer_level;
	return quest_reward * level_bonus;
}

void GameDataManager::resolve_level(Adventurer* adventurer, int old_lvl, int new_lvl)
{
	const int skill_count = new_lvl / 5 - old_lvl / 5;
	if (skill_count > 0)
	{
		adventurer->set_skills(skills->generate(skill_count, adventurer->get_skills()));
	}
	else if (skill_count < 0) // level down at 5 and 10 does something
	{
		adventurer->rmv_skill(-skill_count); // lose last skill obtained, sorry :)
	}
}

bool calculate_success(unsigned long long chance, unsigned long long base)
{
	return chance >= base;
}

bool GameDataManager::get_final_result(unsigned long long compare_point, int adventurer_level, int quest_difficulty)
{
	bool final_result;

	if (adventurer_level - quest_difficulty > 0) // x:1 is advantage, first success is result
	{
		final_result = false;
		for (int i = 0; i < adventurer_level - quest_difficulty + 1 && final_result == false; ++i)
		{
			final_result = calculate_success(chance_generator.get_next(), compare_point);
		}
	}
	else if (adventurer_level - quest_difficulty < 0) // 1:x is disadvantage, first fail is result
	{
		final_result = true;
		for (int i = 0; i < quest_difficulty - adventurer_level + 1 && final_result == true; ++i)
		{
			final_result = calculate_success(chance_generator.get_next(), compare_point);
		}
	}
	else // 1:1, base roll is returned
	{
		final_result = calculate_success(chance_generator.get_next(), compare_point);
	}
	return final_result;
}

int get_final_compare_point(Adventurer* adventurer)
{
	int compare_value = adventurer->get_failure_quests().size() + QUEST_COMPARE_BASE_MIDPOINT - adventurer->get_success_quests().size();

	compare_value = std::clamp(compare_value, QUEST_COMPARE_BASE_MINPOINT, QUEST_COMPARE_BASE_MAXPOINT);

	return compare_value;
}

void alter_roll_calculation(Adventurer* adventurer, int& adventurer_level)
{
	for (auto && skill : adventurer->get_skills())
	{
		skill->execute_roll_calculation_change(adventurer_level);
	}
}
void alter_roll_result(Adventurer* adventurer, const quest_type_set& quest_types, bool& result)
{
	for (auto&& skill : adventurer->get_skills())
	{
		skill->execute_roll_result_change(quest_types, result);
	}
}
void alter_reward(skill_set& skills, perk_set& perks, GoldFameData& data, int& experience)
{
	for (auto&& item : skills)
	{
		item->execute_reward_change(data, experience);
	}
	for (auto&& item : perks)
	{
		item->execute_reward_change(data, experience);
	}
}
void alter_penalty(skill_set& skills, perk_set& perks, GoldFameDeadlyData& data, int& experience)
{
	for (auto&& item : skills)
	{
		item->execute_penalty_change(data, experience);
	}
	for (auto&& item : perks)
	{
		item->execute_penalty_change(data, experience);
	}
}

bool GameDataManager::on_success_quest(Adventurer* adventurer, Quest* quest)
{
	GoldFameData gold_fame_data {quest->reward};
	int experience_gain = get_experience_change(quest->get_difficulty(), adventurer->get_level());

	alter_reward(adventurer->get_skills(), guild->get_perks(), gold_fame_data, experience_gain);

	// Get Reward
	guild->base_stats.gold.add_value(gold_fame_data.gold.get_value());
	guild->base_stats.fame.add_value(gold_fame_data.fame.get_value());
	
	// Update experience
	const auto old_lvl = adventurer->get_level();
	adventurer->experience.add_value(experience_gain);
	const auto new_lvl = adventurer->get_level();
	resolve_level(adventurer, old_lvl, new_lvl);

	// Assign Quest - Adventurer and complete quest
	quest->adventurer.set_value(adventurer->get_id());
	adventurer->set_success_quests(quest->get_id());
	quests->complete(quest->get_id());
	
	quest->state.set_value(QuestStateEnum::Success);
	quests->complete(quest->get_id());
	
	return true;
}
bool GameDataManager::on_failure_quest(Adventurer* adventurer, Quest* quest)
{
	GoldFameDeadlyData gold_fame_deadly_data{ quest->penalty };
	int experience_loss = get_experience_change(quest->get_difficulty(), adventurer->get_level());

	alter_penalty(adventurer->get_skills(), guild->get_perks(), gold_fame_deadly_data, experience_loss);

	// Get Penalty
	guild->base_stats.gold.rmv_value(gold_fame_deadly_data.gold.get_value());
	guild->base_stats.fame.rmv_value(gold_fame_deadly_data.fame.get_value());

	// Update experience
	const auto old_lvl = adventurer->get_level();
	adventurer->experience.add_value(experience_loss);
	const auto new_lvl = adventurer->get_level();
	resolve_level(adventurer, old_lvl, new_lvl);

	// Try to kill him.
	if (gold_fame_deadly_data.deadly.get_value())
	{
		adventurers->kill(adventurer->get_id());
	}
	
	// Assign Quest - Adventurer and fail quest
	quest->adventurer.set_value(adventurer->get_id());
	adventurer->set_failure_quests(quest->get_id());
	quests->fail(quest->get_id());
	
	quest->state.set_value(QuestStateEnum::Failure);
	quests->fail(quest->get_id());
	
	return true;
}

bool GameDataManager::embark_on_quest(Adventurer* adventurer, Quest* quest)
{
	int final_compare_point = get_final_compare_point(adventurer);

	int adventurer_level = adventurer->get_level();
	int quest_level = quest->get_difficulty();

	alter_roll_calculation(adventurer, adventurer_level);
	
	bool first_result = get_final_result(final_compare_point, adventurer_level, quest_level);

	alter_roll_result(adventurer, quest->get_quest_types(), first_result);

	return first_result
		? on_success_quest(adventurer, quest)
		: on_failure_quest(adventurer, quest);
}

bool GameDataManager::dispatch(const int adventurer_id, const int quest_id)
{
	auto adventurer = adventurers->find_hired(adventurer_id);
	auto quest = quests->find_reserved(quest_id);
	if (adventurer == nullptr || quest == nullptr)
		return false;

	if (guild->base_stats.gold.get_value() < adventurer->living_cost.get_value())
		return false;
	// Pay required sum, and continue on quest.
	guild->base_stats.gold.rmv_value(adventurer->living_cost.get_value());

	return embark_on_quest(adventurer, quest);
}