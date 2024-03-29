#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <random>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_set>
#include <utility>
#include <vector>

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