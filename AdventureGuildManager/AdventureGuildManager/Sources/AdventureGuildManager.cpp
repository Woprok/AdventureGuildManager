#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <random>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "../Headers/GameManagers.hpp"
#include "../Headers/Generators.hpp"

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