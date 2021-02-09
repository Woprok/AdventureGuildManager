#ifndef ADVENTURER_INTERFACES_HPP
#define ADVENTURER_INTERFACES_HPP

#include "InputInterfaces.hpp"
#include "SharedConvertors.hpp"
#include "../Entities/AdventurerEntities.hpp"
#include "../Interfaces/IDisplayableInterfaces.hpp"

class AdventurerInterfaces : public IDisplayeableInterfaces
{
public:
	AdventurerInterfaces() = default;
	~AdventurerInterfaces() override = default;
	std::string display_default() override
	{
		std::ostringstream result_stream;
		result_stream << "Adventurer Commands:\n";
		result_stream << "\t- adventurer: help for adventurer commands.\n";
		result_stream << "\t- adventurer available: show available adventurers.\n";
		result_stream << "\t- adventurer hired: show hired adventurers.\n";
		result_stream << "\t- adventurer dead: show dead adventurers.\n";
		result_stream << "\t- adventurer inactive: show retired adventurers.\n";
		result_stream << "\t- adventurer recruit \"adventurer id\": transfers available adventurer to hired. Full level based recruitment cost is paid.\n";
		result_stream << "\t- adventurer pension \"adventurer id\" \"quest id\": retires adventure. Full level based retirement cost is paid. Fame is gained.\n";
		return result_stream.str();
	}

	std::string display_available(GameDataManager& game_data_manager)
	{
		std::ostringstream result_stream;
		result_stream << "*****Adventurer board!*****" << "\n";
		result_stream << "Available adventurers for hiring:" << "\n";
		result_stream << list_adventurers(game_data_manager, game_data_manager.adventurers->get_available());
		return result_stream.str();
	}
	std::string display_hired(GameDataManager& game_data_manager)
	{
		std::ostringstream result_stream;
		result_stream << "*****Adventurer board!*****" << "\n";
		result_stream << "Hired adventurers:" << "\n";
		result_stream << list_adventurers(game_data_manager, game_data_manager.adventurers->get_hired());
		return result_stream.str();
	}
	std::string display_dead(GameDataManager& game_data_manager)
	{
		std::ostringstream result_stream;
		result_stream << "*****Adventurer board!*****" << "\n";
		result_stream << "Killed in action adventurers:" << "\n";
		result_stream << list_adventurers(game_data_manager, game_data_manager.adventurers->get_dead());
		return result_stream.str();
	}
	std::string display_inactive(GameDataManager& game_data_manager)
	{
		std::ostringstream result_stream;
		result_stream << "*****Adventurer board!*****" << "\n";
		result_stream << "Retired adventurers:" << "\n";
		result_stream << list_adventurers(game_data_manager, game_data_manager.adventurers->get_inactive());
		return result_stream.str();
	}
	
	std::string display_adventurer_hired(GameDataManager& game_data_manager, int adventurer_id)
	{
		std::ostringstream result_stream;
		result_stream << "*****Adventurer board receptionist!*****" << "\n";
		result_stream << "We successfully hired this adventurer." << "\n";
		result_stream << find_adventurer_detail(game_data_manager, adventurer_id);
		return result_stream.str();
	}
	std::string display_adventurer_retired(GameDataManager& game_data_manager, int adventurer_id)
	{
		std::ostringstream result_stream;
		result_stream << "*****Adventurer board receptionist!*****" << "\n";
		result_stream << "We successfully hired this adventurer." << "\n";
		result_stream << find_adventurer_detail(game_data_manager, adventurer_id);
		return result_stream.str();
	}

	std::string display_adventurer_action_failed(int adventurer_id)
	{
		std::ostringstream result_stream;
		result_stream << "*****Adventurer board receptionist!*****" << "\n";
		result_stream << "Selected adventurer id ";
		result_stream << "(";
		result_stream << adventurer_id;
		result_stream << ") ";
		result_stream << "is not valid:";
		result_stream << "\n";
		return result_stream.str();
	}

	int get_adventurer_id_value(std::string&& cs)
	{
		return InputInterfaces::get_num(cs, "adventurer id");
	}
protected:
	std::string list_adventurers(GameDataManager& game_data_manager, const adventurer_collection& collection)
	{
		std::ostringstream result;
		for (auto&& adventurer : collection)
		{
			result << adventurer_detail(game_data_manager, *adventurer);
		}
		return result.str();
	}

	std::string join_level(int level) const
	{
		return std::to_string(level);
	}
	std::string join_quest(GameDataManager& game_data_manager, const quest_set& quests) const
	{
		std::unordered_set<std::string> list_of_types;
		for (auto&& quest_id : quests)
		{
			const auto&& quest = game_data_manager.quests->find_quest(quest_id);
			list_of_types.insert(quest->get_name());
		}
		return StringContext::merge(list_of_types, ", ");
	}
	std::string join_skill(const skill_set& skills) const
	{
		std::unordered_set<std::string> list_of_types;
		for (auto&& skill : skills)
		{
			list_of_types.insert(skill->get_name());
		}
		return StringContext::merge(list_of_types, ", ");
	}
	std::string join_experience(int experience) const
	{
		return std::to_string(experience);
	}
	std::string join_base_total(int base, int total) const
	{
		return std::to_string(total) + " from base " + std::to_string(base);
	}

	std::string adventurer_detail(GameDataManager& game_data_manager, Adventurer& adventurer) const
	{
		std::ostringstream result_stream;
		result_stream << "\t" << adventurer.get_id() << " - " << adventurer.get_name() << "\n";
		result_stream << "\t\t" << "- rarity: " << SharedConvertors::translate_adventurer_rarity(adventurer.rarity.get_value()) << "\n";
		result_stream << "\t\t" << "- level: " << join_level(adventurer.get_level()) << "\n";
		result_stream << "\t\t" << "- experience: " << join_experience(adventurer.experience.get_value()) << "\n";
		result_stream << "\t\t" << "- recruit cost: "
			<< join_base_total(adventurer.recruit_cost.get_value(), adventurer.get_level_recruit_cost()) << "\n";
		result_stream << "\t\t" << "- retirement cost: "
			<< join_base_total(adventurer.retire_cost.get_value(), adventurer.get_level_retire_cost()) << "\n";
		result_stream << "\t\t" << "- retirement fame: "
			<< join_base_total(adventurer.get_retire_fame(), adventurer.get_level_retire_fame()) << "\n";
		result_stream << "\t\t" << "- skills: " << join_skill(adventurer.get_skills()) << "\n";
		result_stream << "\t\t" << "- quest completed: " << join_quest(game_data_manager, adventurer.get_success_quests()) << "\n";
		result_stream << "\t\t" << "- quest failed: " << join_quest(game_data_manager, adventurer.get_failure_quests()) << "\n";
		return result_stream.str();
	}

	std::string find_adventurer_detail(GameDataManager& game_data_manager, int adventurer_id)
	{
		return adventurer_detail(game_data_manager, *game_data_manager.adventurers->find_adventurer(adventurer_id));
	}
};

#endif