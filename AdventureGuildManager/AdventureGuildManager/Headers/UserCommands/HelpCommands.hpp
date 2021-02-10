#ifndef HELP_COMMANDS_HPP
#define HELP_COMMANDS_HPP

#include "../GameDataManagers.hpp"
#include "../Interfaces/ICommands.hpp"
#include "../UserInterfaces/HelpInterfaces.hpp"
#include "../UserInterfaces/MenuInterfaces.hpp"
#include "../UserInterfaces/ExitInterfaces.hpp"
#include "../UserInterfaces/ErrorInterfaces.hpp"
#include "../UserInterfaces/EncyclopediaInterfaces.hpp"
#include "../UserInterfaces/GuildInterfaces.hpp"
#include "../UserInterfaces/PerkInterfaces.hpp"
#include "../UserInterfaces/AdventurerInterfaces.hpp"
#include "../UserInterfaces/QuestInterfaces.hpp"

class HelpCommand : public ICommand
{
public:
	HelpCommand(string_context& command_context) : ICommand(command_context) { }
	~HelpCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 1
			&& (command_context[0] == "help" || command_context[0] == "h");
	}
	std::string execute([[maybe_unused]] GameDataManager& game_data_manager) override
	{
		std::ostringstream result;
		result << help.display_default();
		result << menu.display_default();
		result << exit.display_default();
		result << error.display_default();
		result << encyclopedia.display_default();
		result << guild.display_default();
		result << perk.display_default();
		result << adventurer.display_default();
		result << quest.display_default();
		return result.str();
	}
private:
	HelpInterfaces help;
	MenuInterfaces menu;
	ExitInterfaces exit;
	ErrorInterfaces error;
	EncyclopediaInterfaces encyclopedia;
	GuildInterfaces guild;
	PerkInterfaces perk;
	AdventurerInterfaces adventurer;
	QuestInterfaces quest;
};

#endif