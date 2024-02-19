#include "curses_screen.h"
#include "shooter_game.h"
#include "shooter_menu.h"
#include "shooter_saver.h"
#include "shooter_score_storage.h"
#include "utils.h"

int main() {
	shooter_menu::ShooterMenu m;
	shooter_game::ShooterGame g;
	shooter_saver::ShooterSaver saver;
	shooter_score_storage::ShooterScoreStorage score_storage;
	curses_screen::CursesScreen s;
	utils::loop(&m, &g, &saver, &score_storage, &s);
	return 0;
}
