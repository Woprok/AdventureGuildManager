#ifndef GAME_ENTITIES_HPP
#define GAME_ENTITIES_HPP

#include <memory>

#include "Entities/AdventurerEntities.hpp"
#include "Entities/QuestEntities.hpp"
#include "Entities/GuildEntitiess.hpp"
#include "Entities/GameStates.hpp"

#include "DataKeepers/AdventurerDataKeepers.hpp"
#include "DataKeepers/PerkDataKeepers.hpp"
#include "DataKeepers/SkillDataKeepers.hpp"
#include "DataKeepers/PerkDataKeepers.hpp"
#include "DataKeepers/QuestDataKeepers.hpp"

#include "Generators/AdventurerGenerators.hpp"
#include "Generators/QuestGenerators.hpp"

#include "Perks/Perks.hpp"

constexpr int MIN_QUEST_COUNT = 5;
constexpr int MAX_QUEST_COUNT = 10;
constexpr int MIN_ADVENTURER_COUNT = 3;
constexpr int MAX_ADVENTURER_COUNT = 10;
constexpr int MIN_QUEST_EXPERIENCE_CHANGE_BASE = 100;
constexpr int MAX_QUEST_EXPERIENCE_CHANGE_BASE = 1000;
constexpr int DEFAULT_QUEST_RESERVATION_GOLD_RENT = 50;
constexpr int DEFAULT_FAME_TO_GOLD_RATE = 10;
constexpr int DEFAULT_RESSURECTION_COST = 1000;
constexpr int DEFAULT_RETRAIN_COST_PER_SKILL = 250;
constexpr int DEFAULT_UPGRADE_COST_PER_RARITY_DIFF = 250;
constexpr int DEFAULT_GODSLAYER_COST = 500;
constexpr int DEFAULT_COST_PER_LEVEL_PERK = 500;
constexpr int MIN_CHANCE_GENERATOR = 1;
constexpr int MAX_CHANCE_GENERATOR = 100;

class GameDataManager
{
public:
	GameDataManager()
	{
		game_state = std::make_unique<GameState>();
		guild = std::make_unique<Guild>("My first guild", GoldFameData(0, 0));
		quests = std::make_unique<QuestDataKeeper>();
		skills = std::make_unique<SkillDataKeeper>();
		adventurers = std::make_unique<AdventurerDataKeeper>();
		gen_quests = std::make_unique<QuestGenerator>(*quests);
		gen_adventurers = std::make_unique<AdventurerGenerator>(*adventurers, *skills);
		perks = std::make_unique<PerkDataKeeper>();
	}
	~GameDataManager() = default;
	GameDataManager(const GameDataManager&) = delete;
	GameDataManager& operator=(GameDataManager) = delete;
	std::unique_ptr<GameState> game_state;
	std::unique_ptr<Guild> guild;
	std::unique_ptr<QuestDataKeeper> quests;
	std::unique_ptr<AdventurerDataKeeper> adventurers;
	std::unique_ptr<QuestGenerator> gen_quests;
	std::unique_ptr<AdventurerGenerator> gen_adventurers;
	std::unique_ptr<SkillDataKeeper> skills;
	std::unique_ptr<PerkDataKeeper> perks;
	
	/// <summary>
	/// Create new game.
	/// </summary>
	void start_game();
	/// <summary>
	/// Progress game to next turn.
	/// </summary>
	void wait_turn();
	/// <summary>
	/// End current game.
	/// </summary>
	void end_game();
	/// <summary>
	/// Change guild name. Return is mostly true, rare cases false.
	/// </summary>
	bool rename_guild(const std::string& new_guild_name) const;
	/// <summary>
	/// Change difficulty. Return is true value of new difficulty.
	/// </summary>
	int change_difficulty(const int new_difficulty);
	/// <summary>
	/// Accept quest. Return is true or false if quest was not found in available.
	/// </summary>
	bool take_quest(const int quest_id);
	/// <summary>
	/// Hire adventurer. Return is true or false if adventurer was not found in available.
	/// </summary>
	bool hire_adventurer(const int adventurer_id); //true on did something, else false
	/// <summary>
	/// Retire adventurer. Return is true or false if adventurer was not found in hired or not enough money.
	/// </summary>
	bool pension_adventurer(const int adventurer_id);

	/// <summary>
	/// Trade fame for gold. Return is true or false if not enough.
	/// </summary>
	bool trade(int fame_to_convert);
	/// <summary>
	/// Ressurect adventurer for gold. Return is true or false if not dead or found.
	/// </summary>
	bool resurrect(int adventurer_id);
	/// <summary>
	/// Retrain adventurer skills for gold. Return is true or false if not hired or found.
	/// </summary>
	bool retrain(int adventurer_id);
	/// <summary>
	/// Upgrade adventurer rarity for gold. Return is true or false if not hired or found.
	/// Up to Innkeeper.
	/// </summary>
	bool upgrade(int adventurer_id);
	/// <summary>
	/// Grant adventurer special skill for gold. Return is true or false if not hired or found.
	/// Adventurer becomes god.
	/// </summary>
	bool grant_godslayer(int adventurer_id);
	/// <summary>
	/// Buy perk for a guild.
	/// Adventurer becomes god.
	/// </summary>
	bool buy_perk(int perk_id);

	/// <summary>
	/// This literally does everything the game is about.
	/// </summary>
	bool dispatch(const int adventurer_id, const int quest_id);
	bool win_condition() const;
	bool lose_condition() const;
protected:
	/// <summary>
	/// Clear current game state.
	/// </summary>
	void reset_game();
	/// <summary>
	/// Progress game by generating new quests and adventurers.
	/// </summary>
	void progress_game();
	void generate_quests(int quest_count);
	void generate_adventurers(int adventurer_count);
	void substract_quest_wait_fees();
	void substract_adventurer_wait_fees();

	int get_experience_change(int quest_difficulty, int adventurer_level);
	void resolve_level(Adventurer* adventurer, int old_lvl, int new_lvl);
	bool get_final_result(int compare_point, int adventurer_level, int quest_difficulty);
	bool embark_on_quest(Adventurer* adventurer, Quest* quest);
	bool on_success_quest(Adventurer* adventurer, Quest* quest);
	bool on_failure_quest(Adventurer* adventurer, Quest* quest);
	
	UniformGenerator chance_generator{ MIN_CHANCE_GENERATOR,MAX_CHANCE_GENERATOR };
};

#endif