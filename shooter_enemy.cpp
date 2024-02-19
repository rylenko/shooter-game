#include "shooter_enemy.h"

namespace shooter_enemy {

ShooterEnemy::ShooterEnemy(screen_::Point point)
noexcept: game::Activity(point) {
	this->_color_id = (rand() % 2 == 0) ? this->_COLOR_ID_1 : this->_COLOR_ID_2;
}

screen_::Point ShooterEnemy::face() noexcept {
	std::vector<std::string> symbol_lines = this->symbol_lines();
	return screen_::Point(
		this->_point.x() + symbol_lines.back().size() / 2,
		this->_point.y() + symbol_lines.size() + 1
	);
}

void ShooterEnemy::process(game::Game* g, screen_::Screen* s, char key) {
	// First process
	if (this->_first_process) {
		this->_first_process = false;
		s->init_color(this->_COLOR_ID_1, this->_COLOR_FG_1, this->_COLOR_BG);
		s->init_color(this->_COLOR_ID_2, this->_COLOR_FG_2, this->_COLOR_BG);
	}

	// Move
	steady_clock_t now = steady_clock::now();
	if ((now - this->_last_time) / 1ms > this->_MOVE_DELAY) {
		int random = rand();
		if (random % 10 == 0) {
			this->_point.x(this->_point.x() - 1);
		} else if (random % 10 == 1) {
			this->_point.x(this->_point.x() + 1);
		}
		this->_point.y(this->_point.y() + 1);
		this->_last_time = now;
	}
	if (
		this->_point.y() + this->symbol_lines_count() >= s->height()
		|| this->_point.y() + this->symbol_lines_count() < 0
	) {
		this->_status = game::Status::Trash;
		return;
	}

	// Draw
	s->set_color(this->_color_id);
	s->out(this->_point, this->symbol());
	s->unset_color(this->_color_id);
}

std::string ShooterEnemy::symbol() noexcept {
	return this->_SYMBOL;
}

}
