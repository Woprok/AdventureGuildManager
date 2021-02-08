#ifndef GAME_STATES_HPP
#define GAME_STATES_HPP

class GameState
{
public:
	bool is_exit_requested() const { return exit_requested; }
	bool request_exit(bool value) { exit_requested = value; return exit_requested; }
	bool get_progress_state() const { return is_progressing; }
	bool change_progress_state(bool value) { is_progressing = value; return is_progressing; }
	void clear()
	{
		request_exit(false);
		change_progress_state(false);
	}
private:
	bool exit_requested = false;
	bool is_progressing = false;
};

#endif