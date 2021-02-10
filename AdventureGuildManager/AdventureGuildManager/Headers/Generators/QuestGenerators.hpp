#ifndef QUEST_GENERATORS_HPP
#define QUEST_GENERATORS_HPP

#include "NeutralGenerators.hpp"
#include "../DataKeepers/QuestDataKeepers.hpp"
#include "../Helpers/StringContexts.hpp"

constexpr int GOLD_REWARD_BASE_PER_RARITY = 300;
constexpr int FAME_REWARD_BASE_PER_RARITY = 50;
constexpr int GOLD_PENALTY_BASE_PER_RARITY = 150;
constexpr int FAME_PENALTY_BASE_PER_RARITY = 25;

class QuestNameGenerator : public NameGenerator
{
public:
	QuestNameGenerator() = default;
	~QuestNameGenerator() override = default;
	QuestNameGenerator(const QuestNameGenerator&) = delete;
	QuestNameGenerator& operator=(QuestNameGenerator) = delete;
	std::string generate_name() const
	{
		switch (switch_value.get_next())
		{
			case 0:
				return get_random_item(pieceful) + " the " + create_person_name() + "'s " + get_random_item(where);
			case 1: 
				return get_random_item(neutral) + " " + get_random_item(who) + " named " + create_person_name();
			case 2: 
				return get_random_item(covert) + " " + create_person_name() + "'s " + get_random_item(what);
			case 3: 
				return get_random_item(dangerous) + " " + get_random_item(targets);
			default: 
				return "Missing quest header";
		}
	}
private:
	UniformGenerator switch_value { 0, 3 };
	const std::vector<std::string> pieceful =
	{
		"Search", "Find", "Locate"
	};
	const std::vector<std::string> neutral =
	{
		"Rescue", "Protect", "Find"
	};
	const std::vector<std::string> covert =
	{
		"Steal", "Destroy",
	};
	const std::vector<std::string> dangerous =
	{
		"Kill", "Assassinate", "Murder",
	};
	const std::vector<std::string> where =
	{
		"mountains", "village", "town", "woods", "cave", "island", "shelter"
	};
	const std::vector<std::string> who =
	{
		"boy", "girl", "man", "woman", "merchant", "noble"
	};
	const std::vector<std::string> targets =
	{
		"man", "woman", "merchant", "noble", "dragon", "unknown monster", "general"
	};
	const std::vector<std::string> what =
	{
		"artifact", "tools", "armor", "weapons",
	};
};

/// <summary>
/// Keeps reference to actual data.
/// </summary>
class QuestGenerator
{
public:
	QuestGenerator(QuestDataKeeper& current_quest_data) : quest_data(current_quest_data) {}
	~QuestGenerator() = default;
	QuestGenerator(const QuestGenerator&) = delete;
	QuestGenerator& operator=(QuestGenerator) = delete;
	quest_type_set generate_types(int count) const { return generate_quest_types(count); }
	quest_type_set generate_types(QuestRarity quest_rarity) const { return generate_quest_types(static_cast<int>(quest_rarity)); }
	QuestRarity generate_rarity(int max_rarity) const
	{
		int gen_rarity = rarity_generator.get_next();
		if (gen_rarity >= 175 && max_rarity >= 7) // 175 - 179
			return quest_data.get_quest_rarities()[7];
		if (gen_rarity >= 165 && max_rarity >= 6) // 165 - 174
			return quest_data.get_quest_rarities()[6];
		if (gen_rarity >= 150 && max_rarity >= 5) // 150 - 164
			return quest_data.get_quest_rarities()[5];
		if (gen_rarity >= 130 && max_rarity >= 4) // 130 - 149
			return quest_data.get_quest_rarities()[4];
		if (gen_rarity >= 105 && max_rarity >= 3) // 105 - 129
			return quest_data.get_quest_rarities()[3];
		if (gen_rarity >= 75 && max_rarity >= 2) // 75 - 104
			return quest_data.get_quest_rarities()[2];
		if (gen_rarity >= 40 && max_rarity >= 1) // 40 - 74
			return quest_data.get_quest_rarities()[1];
		// 0 - 39
		return quest_data.get_quest_rarities()[0];
	}
	int generate_difficulty(int min_difficulty, int max_difficulty) const
	{
		return std::min(std::clamp(difficulty_generator.get_next(), min_difficulty, MAX_QUEST_DIFFICULTY), max_difficulty);
	}
	
	std::unique_ptr<Quest> create_quest(int min_difficulty, int max_difficulty, int max_quest_rarity)
	{
		std::string&& name = quest_name_generator.generate_name();

		QuestRarity&& rarity = generate_rarity(max_quest_rarity);
		int&& difficulty = generate_difficulty(min_difficulty, max_difficulty);

		GoldFameData&& reward = generate_reward(static_cast<int>(rarity));
		GoldFameDeadlyData&& penalty = generate_penalty(static_cast<int>(rarity), difficulty);

		quest_type_set&& quest_types = generate_quest_types(difficulty);
		
		return std::make_unique<Quest>(std::move(name), reward, penalty, rarity, difficulty, quest_types);
	}

	GoldFameData generate_reward(int rarity) const
	{
		auto&& gold = GOLD_REWARD_BASE_PER_RARITY * rarity + gold_divergence.get_next();
		auto&& fame = FAME_REWARD_BASE_PER_RARITY * rarity + fame_divergence.get_next();
		return GoldFameData(gold, fame);
	}
	GoldFameDeadlyData generate_penalty(int rarity, int difficulty) const
	{
		auto&& gold = GOLD_PENALTY_BASE_PER_RARITY * rarity + gold_divergence.get_next();
		auto&& fame = FAME_PENALTY_BASE_PER_RARITY * rarity + fame_divergence.get_next();
		auto&& is_deadly = difficulty >= difficulty_generator.get_next();
		
		return GoldFameDeadlyData(gold, fame, is_deadly);
	}
	
protected:
	QuestDataKeeper& quest_data;
	UniformGenerator rarity_generator { 0, 179 };
	UniformGenerator difficulty_generator { MIN_QUEST_DIFFICULTY, MAX_QUEST_DIFFICULTY };
	UniformGenerator gold_divergence { 0, 200 };
	UniformGenerator fame_divergence { 0, 20 };
	QuestNameGenerator quest_name_generator;
private:
	quest_type_set generate_quest_types(int count) const
	{
		quest_type_set result;
		std::sample(quest_data.get_quest_types().begin(),
			quest_data.get_quest_types().end(),
			std::inserter(result, result.begin()),
			std::clamp(count, 0, static_cast<int>(quest_data.get_quest_types().size())),
			std::mt19937{ std::random_device{}() });
		return result;
	}
};

#endif