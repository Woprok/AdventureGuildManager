#ifndef ENCYCLOPEDIA_INTERFACES_HPP
#define ENCYCLOPEDIA_INTERFACES_HPP
#include "../Entities/QuestEntities.hpp"

class EncyclopediaInterfaces : public IDisplayeableInterfaces
{
public:
	EncyclopediaInterfaces() = default;
	~EncyclopediaInterfaces() override = default;

	std::string display_default() override
	{
		std::ostringstream result_stream;
		result_stream << "Encyclopedia Commands:\n";
		result_stream << "\t- encyclopedia: help for encyclopedia commands.\n";
		result_stream << "\t- encyclopedia quest_types: show quest types and their description.\n";
		result_stream << "\t- encyclopedia quest_rarities: show quest rarities and their description.\n";
		result_stream << "\t- encyclopedia adventurer_rarities: show adventurer rarities and their description.\n";
		result_stream << "\t- encyclopedia skills: show skills and their description.\n";
		result_stream << "\t- encyclopedia perks: show perks and their description.\n";
		return result_stream.str();
	}

	std::string display_quest_types(GameDataManager& game_data_manager) const
	{
		std::ostringstream result_stream;
		result_stream << "*****Encyclopedia!*****" << "\n";
		result_stream << "Currently we register following quest types:" << "\n";
		result_stream << list_quest_types(game_data_manager);
		return result_stream.str();
	}
	std::string display_quest_rarities(GameDataManager& game_data_manager) const
	{
		std::ostringstream result_stream;
		result_stream << "*****Encyclopedia!*****" << "\n";
		result_stream << "Currently we register quest rarities:" << "\n";
		result_stream << list_quest_rarities(game_data_manager);
		return result_stream.str();
	}
		std::string display_adventurer_rarities(GameDataManager& game_data_manager) const
	{
		std::ostringstream result_stream;
		result_stream << "*****Encyclopedia!*****" << "\n";
		result_stream << "Currently we register adventurer rarities:" << "\n";
		result_stream << list_adventurer_rarities(game_data_manager);
		return result_stream.str();
	}
	std::string display_skills(GameDataManager& game_data_manager) const
	{
		std::ostringstream result_stream;
		result_stream << "*****Encyclopedia!*****" << "\n";
		result_stream << "Currently we register following skills:" << "\n";
		result_stream << list_skills(game_data_manager);
		return result_stream.str();
	}
	std::string display_perks(GameDataManager& game_data_manager) const
	{
		std::ostringstream result_stream;
		result_stream << "*****Encyclopedia!*****" << "\n";
		result_stream << "Currently we register following perks:" << "\n";
		result_stream << list_perks(game_data_manager);
		return result_stream.str();
	}
private:
	std::string quest_type_detail(QuestType item)
	{
		return "\t" + std::to_string(static_cast<int>(item)) + " - " + SharedConvertors::translate_quest_type(item) + "\n"
			+ "\t\t" + SharedConvertors::translate_quest_type_description() + "\n";
	}
	std::string quest_rarities_detail(QuestRarity item)
	{
		return "\t" + std::to_string(static_cast<int>(item)) + " - " + SharedConvertors::translate_quest_rarity(item) + "\n"
			+ "\t\t" + SharedConvertors::translate_quest_rarity_description() + "\n";
	}
	std::string adventurer_rarities_detail(AdventurerRarity item)
	{
		return "\t" + std::to_string(static_cast<int>(item)) + " - " + SharedConvertors::translate_adventurer_rarity(item) + "\n"
			+ "\t\t" + SharedConvertors::translate_adventurer_rarity_description() + "\n";
	}
	std::string skill_detail(const std::unique_ptr<ISkill>& item)
	{
		return "\t" + std::to_string(item->get_id()) + " - " + item->get_name() + "\n"
			+ "\t\t" + item->get_description() + "\n";
	}
	std::string perk_detail(const std::unique_ptr<IPerk>& item)
	{
		return "\t" + std::to_string(item->get_id()) + " - " + item->get_name() + "\n"
			 + "\t\t" + item->get_description() + "\n";
	}
	
	std::string list_quest_types(const GameDataManager& game_data_manager) const
	{
		std::ostringstream result;
		for (auto&& item : collection)
		{
			result << quest_type_detail(item);
		}
		return result.str();
	}
	std::string list_quest_rarities(const GameDataManager& game_data_manager) const
	{
		std::ostringstream result;
		for (auto&& item : collection)
		{
			result << quest_rarities_detail(item);
		}
		return result.str();
	}
	std::string list_adventurer_rarities(const GameDataManager& game_data_manager) const
	{
		std::ostringstream result;
		for (auto&& item : collection)
		{
			result << adventurer_rarities_detail(item);
		}
		return result.str();
	}
	std::string list_skills(const GameDataManager& game_data_manager) const
	{
		std::ostringstream result;
		for (auto&& item : collection)
		{
			result << skill_detail(item);
		}
		return result.str();
	}
	std::string list_perks(const GameDataManager& game_data_manager) const
	{
		std::ostringstream result;
		for (auto&& item : collection)
		{
			result << perk_detail(item);
		}
		return result.str();
	}
private:
	
};
#endif