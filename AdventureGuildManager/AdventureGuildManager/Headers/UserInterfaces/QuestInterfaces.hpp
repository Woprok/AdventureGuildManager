#ifndef QUEST_INTERFACES_HPP
#define QUEST_INTERFACES_HPP

#include "SharedConvertors.hpp"
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


	std::string join_difficulty(int difficulty) const
	{
		return std::to_string(difficulty);
	}
	std::string join_quest_types(const quest_type_set& quest_types) const
	{
		std::unordered_set<std::string> list_of_types;
		for (auto && type : quest_types)
		{
			list_of_types.insert(SharedConvertors::translate_quest_type(type));
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
		result_stream << "\t\t" << "- state: " << SharedConvertors::translate_state(quest.state.get_value()) << "\n";
		result_stream << "\t\t" << "- rarity: " << SharedConvertors::translate_quest_rarity(quest.rarity.get_value()) << "\n";
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
#endif