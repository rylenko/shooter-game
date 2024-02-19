#pragma once

#include "game.h"
#include "menu.h"
#include "saver.h"
#include "score_storage.h"
#include "screen.h"

namespace utils {

void loop(
	menu::Menu* m,
	game::Game* g,
	saver::Saver* saver,
	score_storage::ScoreStorage* score_storage,
	screen_::Screen* s
);

}
