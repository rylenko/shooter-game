#include <random>
#include "shooter_enemy.h"
#include "shooter_enemies.h"

namespace shooter_enemies {

void ShooterEnemies::process(game::Game* g, screen_::Screen* s, char key) {
	// Check game over
	if (g->is_over()) {
		this->_status = game::Status::Trash;
		return;
	}

	// Spawn enemies
	steady_clock_t now = steady_clock::now();
	if ((now - this->_last_time) / 1ms > this->_SPAWN_DELAY) {
		int part = s->width() / this->_SPAWN_CENTER_PART;
		g->add_activity(
			std::make_unique<shooter_enemy::ShooterEnemy>(
				screen_::Point(rand() % part + (s->width() - part) / 2, 0)
			)
		);
		this->_last_time = now;
	}
}

}
