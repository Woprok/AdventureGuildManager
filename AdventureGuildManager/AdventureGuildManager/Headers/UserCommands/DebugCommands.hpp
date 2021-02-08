#ifndef DEBUG_COMMANDS_HPP
#define DEBUG_COMMANDS_HPP

#include "../Interfaces/ICommands.hpp"

class DebugCommand : public ICommand
{
public:
	DebugCommand(string_context& command_context) : ICommand(command_context) { }
	~DebugCommand() override = default;
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 1
			&& command_context[0] == "debug";
	}
	std::string execute(GameDataManager& game_data_manager) override
	{
		return "Runtime debugging command completed!\n";
	}
/*/
private:
	void debug_level_up_down(GameData& game_data)
	{
		const auto adventurer = CollectionIterators::find(game_data.adventurers.get_hired(), 1);
		auto old_lvl = adventurer->get_level();
		adventurer->add_experience(-10000);
		auto new_lvl = adventurer->get_level();
		game_data.resolve_level(adventurer, old_lvl, new_lvl);
	}
	void debug_rarity_quest(GameData& game_data)
	{
		auto&& types = game_data.encyclopedia.generate_from_rarity(QuestRarity::War);
		for (auto&& type : types)
		{
			std::cout << static_cast<int>(type) << "\n";
		}
	}
	void debug_rarity_adventurer(GameData& game_data)
	{
		skill_collection collection;
		collection.insert(std::make_unique<Hoarder>(1));
		auto&& types = game_data.encyclopedia.generate_from_rarity(static_cast<int>(AdventurerRarity::Innkeeper), collection);
		for (auto&& type : types)
		{
			std::cout << type->get_name() << "\n";
		}
	}
/**/
};

#endif