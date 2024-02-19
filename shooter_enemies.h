#pragma once

#include "game.h"
#include "time.h"

namespace shooter_enemies {

class ShooterEnemies: public game::Activity {
	private:
		static const int _SPAWN_DELAY = 1250;
		static const int _SPAWN_CENTER_PART = 4;

		steady_clock_t _last_time = steady_clock::now();

	public:
		void process(game::Game* g, screen_::Screen* s, char key) override;
};

}
