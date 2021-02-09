#ifndef GAME_STATES_HPP
#define GAME_STATES_HPP

constexpr int MIN_DIFFICULTY = 1;
constexpr int MAX_DIFFICULTY = 10;

class GameState
{
public:
	bool is_exit_requested() const { return exit_requested; }
	bool request_exit(bool value) { exit_requested = value; return exit_requested; }
	bool get_progress_state() const { return is_progressing; }
	bool change_progress_state(bool value) { is_progressing = value; return is_progressing; }

	int get_difficulty() const { return difficulty.get_value(); }
	int set_difficulty(int value) { difficulty.set_value(std::clamp(value, MIN_DIFFICULTY, MAX_DIFFICULTY)); return difficulty.get_value(); }

	ChangeEntity<int> turns {0 };

	void reset()
	{
		request_exit(false);
		change_progress_state(false);
		turns.set_value(0);
	}
private:
	bool exit_requested = false;
	bool is_progressing = false;
	GetSetEntity<int> difficulty = GetSetEntity<int>(1);
};

#endif