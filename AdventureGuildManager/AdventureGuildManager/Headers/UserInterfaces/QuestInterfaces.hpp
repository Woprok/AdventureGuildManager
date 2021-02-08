#ifndef QUEST_INTERFACES_HPP
#define QUEST_INTERFACES_HPP

#include "../Entities/QuestEntities.hpp"

class QuestInterfaces : public IDisplayeableInterfaces
{
public:
	QuestInterfaces() = default;
	~QuestInterfaces() override = default;
	std::string display_default() override
	{
		std::ostringstream result_stream;
		result_stream << "Quest Commands:\n";
		result_stream << "\t- quest: help for quest commands.\n";
		result_stream << "\t- quest available: show available quests.\n";
		result_stream << "\t- quest reserved: show reserved quests.\n";
		result_stream << "\t- quest completed: show completed quests.\n";
		result_stream << "\t- quest failed: show failed quests.\n";
		result_stream << "\t- quest take \"quest id\": transfers available quest to reserved quests.\n";
		result_stream << "\t- quest dispatch \"adventurer id\" \"quest id\": dispatches adventure on quest.\n";
		return result_stream.str();
	}
	
	std::string display_available(GameDataManager& game_data_manager) const
	{
		std::ostringstream result_stream;
		result_stream << "*****Quest board!*****" << "\n";
		result_stream << "Available quests for taking:" << "\n";
		result_stream << list_quests(game_data_manager, game_data_manager.quests.get_available());
		return result_stream.str();
	}
	std::string display_reserved(GameDataManager& game_data_manager) const
	{
		std::ostringstream result_stream;
		result_stream << "*****Quest board!*****" << "\n";
		result_stream << "Reserved quests for adventurers:" << "\n";
		result_stream << list_quests(game_data_manager, game_data_manager.quests.get_reserved());
		return result_stream.str();
	}
	std::string display_completed(GameDataManager& game_data_manager) const
	{
		std::ostringstream result_stream;
		result_stream << "*****Quest board!*****" << "\n";
		result_stream << "Completed quest by adventurers:" << "\n";
		result_stream << list_quests(game_data_manager, game_data_manager.quests.get_completed());
		return result_stream.str();
	}
	std::string display_failed(GameDataManager& game_data_manager) const
	{
		std::ostringstream result_stream;
		result_stream << "*****Quest board!*****" << "\n";
		result_stream << "Failed quests by adventurers:" << "\n";
		result_stream << list_quests(game_data_manager, game_data_manager.quests.get_failed());
		return result_stream.str();
	}

	std::string display_quest_info(GameDataManager& game_data_manager, int quest_id) const
	{
		std::ostringstream result_stream;
		result_stream << "*****Quest board receptionist!*****" << "\n";
		result_stream << "We successfully reserved this quest for your adventurer." << "\n";
		result_stream << quest_reservation_detail(game_data_manager, quest_id);
		return result_stream.str();
	}

	std::string display_quest_result(GameDataManager& game_data_manager, int quest_id) const
	{
		std::ostringstream result_stream;
		result_stream << "*****Quest board receptionist!*****" << "\n";
		
		result_stream << quest_dispatch_detail(game_data_manager, quest_id);
		return result_stream.str();
	}

	std::string display_quest_reservation_failed(int quest_id)
	{
		std::ostringstream result_stream;
		result_stream << "*****Quest board receptionist!*****" << "\n";
		result_stream << "Selected quest id ";
		result_stream << "(";
		result_stream << quest_id;
		result_stream << ") ";
		result_stream << "is not valid:";
		result_stream << "\n";
		return result_stream.str();
	}
	std::string display_quest_dispatch_failed(int adventurer_id, int quest_id)
	{
		std::ostringstream result_stream;
		result_stream << "*****Quest board receptionist!*****" << "\n";
		result_stream << "Selected adventurer id or quest id ";
		result_stream << "(";
		result_stream << adventurer_id << ", " << quest_id;
		result_stream << ") ";
		result_stream << "is not valid:";
		result_stream << "\n";
		return result_stream.str();
	}
	
	int get_adventurer_id_value(std::string&& cs)
	{
		return InputInterfaces::get_num(cs, "adventurer id");
	}
	int get_quest_id_value(std::string&& cs)
	{
		return InputInterfaces::get_num(cs, "quest id");
	}
private:
	std::string list_quests(GameDataManager& game_data_manager, const quest_collection& collection)
	{
		std::ostringstream result;
		for (auto&& quest : collection)
		{
			result << quest_detail(game_data_manager, *quest);
		}
		return result.str();
	}

	std::string join_state(QuestStateEnum quest_state) const
	{
		switch (quest_state)
		{
			case QuestStateEnum::Success: return "Success";
			case QuestStateEnum::Failure: return "Failure";
			case QuestStateEnum::Undefined: return "Ignored";
			default: return "Undefined";
		}
	}
	std::string join_rarity(QuestRarity quest_rarity) const
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
	std::string join_types(QuestType quest_type) const
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
	std::string join_difficulty(int difficulty) const
	{
		return std::to_string(difficulty);
	}
	std::string join_quest_types(const quest_type_set& quest_types) const
	{
		std::unordered_set<std::string> list_of_types;
		for (auto && type : quest_types)
		{
			list_of_types.insert(join_types(type));
		}
		return StringContext::merge(list_of_types, ", ");
	}
	std::string join_adventurer(GameDataManager& game_data_manager, int adventurer_id) const
	{
		const auto&& adventurer = game_data_manager.adventurers.get_adventurer(adventurer_id);
		return adventurer != nullptr ? adventurer.get_name() : "No attempt recorded.";
	}
	std::string join_reward(GoldFameData& reward) const
	{
		std::ostringstream result_stream;
		result_stream << reward.gold.get_value() << " gold, ";
		result_stream << reward.fame.get_value() << " fame";
		return result_stream.str();
	}
	std::string join_penalty(GoldFameDeadlyData& penalty) const
	{
		std::ostringstream result_stream;
		result_stream << penalty.gold.get_value() << " gold, ";
		result_stream << penalty.fame.get_value() << " fame, ";
		if (penalty.deadly.get_value())
			result_stream << "deadly.";
		return result_stream.str();
	}

	std::string quest_detail(GameDataManager& game_data_manager, Quest& quest) const
	{
		std::ostringstream result_stream;
		result_stream << "\t" << quest.get_id() << " - " << quest.get_name() << "\n";
		result_stream << "\t\t" << "- state: " << join_state(quest.state.get_value()) << "\n";
		result_stream << "\t\t" << "- rarity: " << join_rarity(quest.rarity.get_value()) << "\n";
		result_stream << "\t\t" << "- difficulty: " << join_difficulty(quest.get_difficulty()) << "\n";
		result_stream << "\t\t" << "- quest types: " << join_quest_types(quest.get_quest_types()) << "\n";
		result_stream << "\t\t" << "- adventurer: " << join_adventurer(game_data_manager, quest.adventurer.get_value()) << "\n";
		result_stream << "\t\t" << "- reward: " << join_reward(quest.reward) << "\n";
		result_stream << "\t\t" << "- penalty: " << join_penalty(quest.penalty) << "\n";
		return result_stream.str();
	}

	std::string quest_reservation_detail(GameDataManager& game_data_manager, int quest_id)
	{
		return quest_detail(game_data_manager, game_data_manager.quests.get_quest(quest_id));
	}
	
	std::string quest_dispatch_detail(GameDataManager& game_data_manager, int quest_id)
	{
		const auto&& quest = game_data_manager.quests.get_quest(quest_id);
		
		return (quest.state.get_value() == QuestStateEnum::Success)
			? "You have completed this quest with your adventurer.\n" + quest_detail(game_data_manager, quest)
			: "You have failed this quest with your adventurer.\n" + quest_detail(game_data_manager, quest);
	}
};

/*/
class QuestTypeWrapper : public NamedEntity
{
public:
	QuestTypeWrapper(QuestType type, std::string type_name, std::string type_desc) : NamedEntity(type_name), desc(type_desc), self(type) { }
	const std::string& get_description() const { return desc; }
	QuestType get_self() const { return self; }
	bool operator==(const QuestTypeWrapper& qtw) const { return qtw.self == self; }
	size_t operator()(const QuestTypeWrapper& qtw) const { return static_cast<size_t>(qtw.self); }
private:
	std::string desc;
	QuestType self;
};

namespace std
{
	template<> struct hash<QuestTypeWrapper>
	{
		std::size_t operator()(QuestTypeWrapper const& s) const noexcept
		{
			return static_cast<size_t>(s.get_self());
		}
	};
}
const std::unordered_set<QuestTypeWrapper>& get_quest_types() const { return quest_type_definitions; }
std::unordered_set<QuestTypeWrapper> quest_type_definitions;
quest_type_definitions.insert(QuestTypeWrapper(QuestType::Minions, "Minions", "Multiple enemies."));
quest_type_definitions.insert(QuestTypeWrapper(QuestType::Boss, "Boss", "Big guy."));
quest_type_definitions.insert(QuestTypeWrapper(QuestType::Poison, "Poison", "Danger of poison is guaranteed."));
quest_type_definitions.insert(QuestTypeWrapper(QuestType::Bleeding, "Bleeding", "You will bleed out quite fast."));
quest_type_definitions.insert(QuestTypeWrapper(QuestType::Curse, "Curse", "You will end harmed on this quest in many ways."));
quest_type_definitions.insert(QuestTypeWrapper(QuestType::Elfs, "Elfs", "See dwarfs."));
quest_type_definitions.insert(QuestTypeWrapper(QuestType::Dwarfs, "Dwarfs", "See elfs."));
quest_type_definitions.insert(QuestTypeWrapper(QuestType::Fairies, "Fairies", "Little jokers."));
quest_type_definitions.insert(QuestTypeWrapper(QuestType::Magical, "Magical", "Atla is alive."));
quest_type_definitions.insert(QuestTypeWrapper(QuestType::Darkness, "Darkness", "Why did you not bring torch ?"));
quest_type_definitions.insert(QuestTypeWrapper(QuestType::Wilderness, "Wilderness", "Location is filled with primordial beings."));
quest_type_definitions.insert(QuestTypeWrapper(QuestType::Dankness, "Dankness", "Dank."));
quest_type_definitions.insert(QuestTypeWrapper(QuestType::Memes, "Memes", "Dark side of internet."));
quest_type_definitions.insert(QuestTypeWrapper(QuestType::Mimes, "Mimes", "Annoying."));
/**/
#endif