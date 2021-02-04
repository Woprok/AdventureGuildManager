#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <string_view>

#include "../Headers/GameManagers.hpp"

/// <summary>
/// Call's game manager and that's it.
/// </summary>
int main()
{
	GameManager game_manager;
	game_manager.force_menu();
	game_manager.run_game();
	return 0;
}
/*
class Adventurer
{
public:

	explicit Adventurer(std::string name) : name(std::move(name)) { }

	void set_name(std::string adventurer_name) { name = adventurer_name; }
	const std::string& get_name() const { return name; }
private:
	std::string name = "Adventurer_Name";
};

class Guild
{
public:
	void set_difficulty(int guild_difficulty) { difficulty = guild_difficulty; }
	int get_difficulty() const { return difficulty; }
	void set_fame(int guild_fame) { fame = guild_fame; }
	int get_fame() const { return fame;	}
	void set_gold(int guild_gold) { gold = guild_gold; }
	int get_gold() const { return gold; }
	void set_name(std::string guild_name) { name = guild_name; }
	const std::string& get_name() const	{ return name; }
private:
	std::string name = "Guild_Name";
	int difficulty = 0;
	int fame = 0;
	int gold = 0;
	std::vector<Adventurer> adventurers;
};

class World
{
public:
	void set_name(std::string world_name) { name = world_name; }
	const std::string& get_name() const { return name; }
	void add_adventurer(Adventurer adventurer_name) { adventurers.push_back(adventurer_name); }
private:
	std::string name = "World_Name";
	std::vector<Adventurer> adventurers;
};


class DisplayeableInterface
{
public:
	virtual ~DisplayeableInterface() = default;

	virtual std::string get_interface()
	{
		return "Not found!\n";
	}
};


class CommandInterface : DisplayeableInterface
{
public:
	std::string get_interface() override
	{
		return "Valid Command!\n";
	}
};
class GuildInterface : DisplayeableInterface
{
public:
	void set_guild(const Guild& new_guild)
	{
		guild = new_guild;
	}
	std::string get_interface() override
	{
		return "Valid Guild Command!\n Guild name: " + guild.get_name() + "-->"
		+ "[NAME:" + guild.get_name() + "]"
		+ "[DIFF:" + std::to_string(guild.get_difficulty()) + "]"
		+ "[FAME:" + std::to_string(guild.get_fame()) + "]"
		+ "[GOLD:" + std::to_string(guild.get_gold()) + "]"
		+ "\n";
	}
private:
	Guild guild;
};
class WorldInterface : DisplayeableInterface
{
public:
	void set_world(const World& new_world)
	{
		world = new_world;
	}
	std::string get_interface() override
	{
		return "Valid Guild Command!\n Guild name: " + world.get_name() + "-->"
			+ "[NAME:" + world.get_name() + "]"
			+ "\n";
	}
private:
	World world;
};

class GameState
{
public:
	bool attempt_command(Command& command)
	{
		if (command.get_name() == "world")
		{
			current_world.add_adventurer(Adventurer("Bob"));
			current_world.add_adventurer(Adventurer("Nick"));
			current_world.add_adventurer(Adventurer("Joe"));
			return true;
		}
		if (command.get_name() == "guild")
		{
			if (command.get_body().size() == 1)
			{
				return true;
			}
			if (command.get_body().size() == 2)
			{
				if (command.get_body()[1] == "info")
					return true;
			}
			if (command.get_body().size() == 3)
			{
				if (command.get_body()[1] == "adventurer")
				{
					if (command.get_body()[2] == "show")
					{
						return true;
					}
					if (command.get_body()[2] == "recruits")
					{
						return true;
					}
					return false;
				}				
				if (command.get_body()[1] == "new")
				{
					current_guild.set_name(command.get_body()[2]);
					current_guild.set_fame(0);
					current_guild.set_gold(1000);
					return true;
				}
				if (command.get_body()[1] == "difficulty")
				{
					try
					{
						int val = std::stoi(command.get_body()[2]);
						current_guild.set_difficulty(val);
					}
					catch (...)
					{
						return false;
					}
					return true;
				}
			}			
		}
		return false;
	}	
	std::string process_command(Command& command)
	{
		if (command.get_name() == "help")
			return HelpInterface().get_interface();
		if (command.get_name() == "exit")
		{
			exit_requested = true;
			return ExitInterface().get_interface();
		}
		if (attempt_command(command))
		{
			if (command.get_name() == "world")
			{
				WorldInterface inter;
				inter.set_world(current_world);
				return inter.get_interface();
			}
			if (command.get_name() == "guild")
			{
				GuildInterface inter;
				inter.set_guild(current_guild);
				return inter.get_interface();
			}
			return CommandInterface().get_interface();
		}
		// "Error"
		return ErrorInterface().get_interface();
	}	
	bool can_continue() const
	{
		return is_alive() && !is_exit_requested();
	}
	bool is_alive() const
	{
		return alive;
	}
	bool is_exit_requested() const
	{
		return exit_requested;
	}
private:
	bool alive = true;
	bool exit_requested = false;
	Guild current_guild;
	World current_world;
};

class GameInstance
{
public:
	void run_game()
	{
		UserInterfaceController::print_interface(IntroInterface().get_interface() + "\n");
		while (game_state.can_continue())
		{
			Command command = InputParser::get_next_command();

			
			std::string command_result = game_state.process_command(command);
			display_command(command.get_name(), command_result);

			debug(command.get_body());

		}
	}
private:
	GameState game_state;
};

*/