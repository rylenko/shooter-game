#pragma once

#include "screen.h"
#include "saver.h"
#include "score_storage.h"

namespace menu {

class Menu {
	protected:
		bool _need_to_quit = false;
		bool _need_to_start = false;

	public:
		virtual ~Menu() = default;

		bool need_to_quit() const noexcept;
		bool need_to_start() const noexcept;
		void need_to_start(bool value) noexcept;

		virtual void process(
			game::Game* g,
			saver::Saver* saver,
			score_storage::ScoreStorage* score_storage,
			screen_::Screen* screen,
			char key
		) = 0;
};

}
