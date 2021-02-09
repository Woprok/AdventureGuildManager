#ifndef GUILD_INTERFACES_HPP
#define GUILD_INTERFACES_HPP

#include "InputInterfaces.hpp"

class GuildInterfaces : public IDisplayeableInterfaces
{
public:
	GuildInterfaces() = default;
	~GuildInterfaces() override = default;
	std::string display_default() override
	{
		std::ostringstream result_stream;
		result_stream << "Guild Commands:\n";
		result_stream << "\t- guild: help for commands.\n";
		result_stream << "\t- guild info: show guild informations.\n";
		result_stream << "\t- guild rename \"My Guild Name\": rename guild to your desired name.\n";
		result_stream << "\t- guild wait: advances to next turn.\n";
		return result_stream.str();
	}
	std::string display_informations(GameDataManager& game_data_manager) const
	{
		std::ostringstream result_stream;
		result_stream << "*****Guild!*****" << "\n";
		result_stream << "\t" << "- name: " << game_data_manager.guild->get_name() << "\n";
		result_stream << "\t" << "- gold: " << game_data_manager.guild->base_stats.gold.get_value() << "\n";
		result_stream << "\t" << "- fame: " << game_data_manager.guild->base_stats.fame.get_value() << "\n";
		result_stream << "\t" << "- level: " << game_data_manager.guild->get_prestige_level() << "\n";
		result_stream << "\t" << "- quest rarity: " << convert_to_quest_rarity(game_data_manager.guild->max_quest_rarity.get_value()) << "\n";
		result_stream << "\t" << "- perks: " << display(game_data_manager.guild->get_perks()) << "\n";
		return result_stream.str();
	}
	std::string display_no_rename(std::string& failed_name) const
	{
		std::ostringstream result_stream;
		result_stream << "*****Guild!*****" << "\n";
		result_stream << "Selected name ";
		result_stream << "(";
		result_stream << failed_name;
		result_stream << ") ";
		result_stream << "is not valid:";
		result_stream << "\n";
		return result_stream.str();
	}
	std::string display_wait(GameDataManager& game_data_manager) const
	{
		std::ostringstream result_stream;
		result_stream << "*****Guild!*****" << "\n";
		result_stream << "You and all adventurers decided to take week off." << "\n";
		result_stream << "Adventurers living expenses were paid." << "\n";
		result_stream << "Quest reservation expenses were paid." << "\n";
		result_stream << "\t" << "- name: " << game_data_manager.guild->get_name() << "\n";
		result_stream << "\t" << "- gold: " << game_data_manager.guild->base_stats.gold.get_value() << "\n";
		result_stream << "\t" << "- fame: " << game_data_manager.guild->base_stats.fame.get_value() << "\n";
		result_stream << "\t" << "- level: " << game_data_manager.guild->get_prestige_level() << "\n";
		result_stream << "\t" << "- quest rarity: " << convert_to_quest_rarity(game_data_manager.guild->max_quest_rarity.get_value()) << "\n";
		result_stream << "\t" << "- perks: " << display(game_data_manager.guild->get_perks()) << "\n";
		return result_stream.str();
	}
	std::string get_name()
	{
		return InputInterfaces::get_str("name");
	}
};

#endif