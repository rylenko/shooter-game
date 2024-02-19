#include "utils.h"

namespace utils {

void loop(
	menu::Menu* m,
	game::Game* g,
	saver::Saver* saver,
	score_storage::ScoreStorage* score_storage,
	screen_::Screen* s
) {
	// Process menu
	while (!m->need_to_quit()) {
		int ch = s->read();
		s->clear();
		m->process(g, saver, score_storage, s, ch);
		s->refresh();

		if (m->need_to_start()) {
			// Process game
			bool processed = false;
			while (!g->need_to_quit()) {
				int ch = s->read();
				s->clear();
				g->process(s, ch);
				s->refresh();
			}
		}
	}
}

}
