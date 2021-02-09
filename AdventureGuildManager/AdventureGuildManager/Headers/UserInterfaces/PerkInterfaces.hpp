#ifndef PERK_INTERFACES_HPP
#define PERK_INTERFACES_HPP

#include <string>

#include "../Interfaces/IDisplayableInterfaces.hpp"
#include "../UserInterfaces/AdventurerInterfaces.hpp"

class PerkInterfaces : public AdventurerInterfaces
{
public:
	PerkInterfaces() = default;
	~PerkInterfaces() override = default;

	std::string display_default() override
	{
		std::ostringstream result_stream;
		result_stream << "Perk Commands:\n";
		result_stream << "\t- perk: help for perk commands.\n";
		result_stream << "\t- perk trade_fame \"fame amount\": trade fame for gold.\n";
		result_stream << "\t- perk requalification_course \"hired adventurer id\": randomize adventurer skills.\n";
		result_stream << "\t- perk armory \"hired adventurer id\": upgrade adventurer rarity.\n";
		result_stream << "\t- perk church_of_heroes \"dead adventurer id\": revive dead adventurer.\n";
		result_stream << "\t- perk madness_of_master \"hired adventurer id\": upgrade adventurer.\n";
		result_stream << "\t- perk buy \"perk id\": buy perk.\n";
		return result_stream.str();
	}

	std::string display_trade_fame(GameDataManager& game_data_manager, int fame_amount) const
	{
		std::ostringstream result_stream;
		result_stream << "*****Perk board receptionist!*****" << "\n";
		result_stream << fame_amount << "fame was traded for gold." << "\n";
		result_stream << display_informations(game_data_manager);
		return result_stream.str();
	}
	std::string display_requalification_course(GameDataManager& game_data_manager, int adventurer_id)
	{
		std::ostringstream result_stream;
		result_stream << "*****Perk board receptionist!*****" << "\n";
		result_stream << "Adventurer was requalified." << "\n";
		result_stream << find_adventurer_detail(game_data_manager, adventurer_id);
		return result_stream.str();
	}
	std::string display_armory(GameDataManager& game_data_manager, int adventurer_id)
	{
		std::ostringstream result_stream;
		result_stream << "*****Perk board receptionist!*****" << "\n";
		result_stream << "Adventurer was correctly equipped with overpowered artifact." << "\n";
		result_stream << find_adventurer_detail(game_data_manager, adventurer_id);
		return result_stream.str();
	}
	std::string display_madness_of_master(GameDataManager& game_data_manager, int adventurer_id)
	{
		std::ostringstream result_stream;
		result_stream << "*****Perk board receptionist!*****" << "\n";
		result_stream << "Did master really send him to slay a god ?." << "\n";
		result_stream << find_adventurer_detail(game_data_manager, adventurer_id);
		return result_stream.str();
	}
	std::string display_church_of_heroes(GameDataManager& game_data_manager, int adventurer_id)
	{
		std::ostringstream result_stream;
		result_stream << "*****Perk board receptionist!*****" << "\n";
		result_stream << "What is not forbidden is legal play." << "\n";
		result_stream << find_adventurer_detail(game_data_manager, adventurer_id);
		return result_stream.str();
	}

	int get_fame_value(std::string&& cs)
	{
		return InputInterfaces::get_num(cs, "fame");
	}
	int get_perk_id_value(std::string&& cs)
	{
		return InputInterfaces::get_num(cs, "perk id");
	}
	std::string display_trade_action_failed(int fame_amount)
	{
		std::ostringstream result_stream;
		result_stream << "*****Perk board receptionist!*****" << "\n";
		result_stream << "Selected fame amount ";
		result_stream << "(";
		result_stream << fame_amount;
		result_stream << ") ";
		result_stream << "is not valid:";
		result_stream << "\n";
		return result_stream.str();
	}
	std::string display_perk_action_failed(int perk_id)
	{
		std::ostringstream result_stream;
		result_stream << "*****Perk board receptionist!*****" << "\n";
		result_stream << "Selected perk id ";
		result_stream << "(";
		result_stream << perk_id;
		result_stream << ") ";
		result_stream << "is not valid:";
		result_stream << "\n";
		return result_stream.str();
	}
private:
	std::string display_informations(GameDataManager& game_data_manager) const
	{
		std::ostringstream result_stream;
		result_stream << "*****Guild!*****" << "\n";
		result_stream << "\t" << "- name: " << game_data_manager.guild->get_name() << "\n";
		result_stream << "\t" << "- gold: " << game_data_manager.guild->base_stats.gold.get_value() << "\n";
		result_stream << "\t" << "- fame: " << game_data_manager.guild->base_stats.fame.get_value() << "\n";
		return result_stream.str();
	}
};

#endif