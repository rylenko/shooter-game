#include "shooter_bullet.h"

namespace shooter_bullet {

static bool _first_process_ever = true;
sound_player::SoundPlayer _sound_player("../resources/shooter_bullet.ogg");

ShooterBullet::ShooterBullet(screen_::Point point, Direction direction)
noexcept: game::Activity(point), _direction(direction) {
	_sound_player.play();
}

Direction ShooterBullet::direction() const noexcept {
	return this->_direction;
}

void ShooterBullet::direction(Direction value) noexcept {
	this->_direction = value;
}

void ShooterBullet::process(game::Game* g, screen_::Screen* s, char _key) {
	// First process ever
	if (_first_process_ever) {
		_first_process_ever = false;
		s->init_color(this->_COLOR_ID, this->_COLOR_FG, this->_COLOR_BG);
	}

	// Move
	steady_clock_t now = steady_clock::now();
	if ((now - this->_last_time) / 1ms > this->_MOVE_DELAY) {
		if (this->_direction == Direction::Up) {
			this->_point.y(this->_point.y() - 1);
		} else {
			this->_point.y(this->_point.y() + 1);
		}
		this->_last_time = now;
	}
	if (
		(this->_direction == Direction::Up && this->_point.y() < 0)
		|| (
			this->_direction == Direction::Down
			&& this->_point.y() > s->height() - 1
		)
	) {
		this->_status = game::Status::Trash;
		return;
	}

	// Draw
	s->set_color(this->_COLOR_ID);
	s->out(this->_point, this->symbol());
	s->unset_color(this->_COLOR_ID);
}

std::string ShooterBullet::symbol() noexcept {
	return this->_SYMBOL;
}

}
