#ifndef GUILD_INTERFACES_HPP
#define GUILD_INTERFACES_HPP

#include "InputInterfaces.hpp"

class GuildInterfaces : public IDisplayeableInterfaces
{
public:
	GuildInterfaces() = default;
	~GuildInterfaces() override = default;
	std::string display_default() const override
	{
		std::ostringstream result_stream;
		result_stream << "Guild Commands:\n";
		result_stream << "\t- guild: help for commands.\n";
		result_stream << "\t- guild info: show guild informations.\n";
		result_stream << "\t- guild rename \"My Guild Name\": rename guild to your desired name.\n";
		result_stream << "\t- guild wait: advances to next turn. Quest rent and hired adventurer living expenses are paid.\n";
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
		result_stream << "\t" << "- quest rarity: " << SharedConvertors::translate_quest_rarity(game_data_manager.guild->max_quest_rarity.get_value()) << "\n";
		result_stream << "\t" << "- perks: " << join_perks(game_data_manager.guild->get_perks()) << "\n";
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
		result_stream << "\t" << "- quest rarity: " << SharedConvertors::translate_quest_rarity(game_data_manager.guild->max_quest_rarity.get_value()) << "\n";
		result_stream << "\t" << "- perks: " << join_perks(game_data_manager.guild->get_perks()) << "\n";
		return result_stream.str();
	}
	
	std::string get_name() const
	{
		return InputInterfaces::get_str("name");
	}
protected:
	std::string join_perks(const perk_set& perks) const
	{
		std::unordered_set<std::string> list_of_perks;
		for (auto&& item : perks)
		{
			list_of_perks.insert(item->get_name());
		}
		return StringContext::merge(list_of_perks, ", ");
	}
};

#endif