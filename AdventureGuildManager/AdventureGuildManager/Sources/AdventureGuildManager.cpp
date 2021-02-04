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
class FAdventurer
{
public:

	explicit Adventurer(std::string name) : name(std::move(name)) { }

	void set_name(std::string adventurer_name) { name = adventurer_name; }
	const std::string& get_name() const { return name; }
private:
	std::string name = "Adventurer_Name";
};
if (command.get_body()[1] == "adventurer")
if (command.get_body()[2] == "show")
if (command.get_body()[2] == "recruits")
*/