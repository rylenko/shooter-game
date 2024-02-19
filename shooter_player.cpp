#include <algorithm>
#include "shooter_player.h"

namespace shooter_player {

screen_::Point ShooterPlayer::face() noexcept {
	return screen_::Point(
		this->_point.x() + this->symbol().find('\n') / 2,
		this->_point.y() - 1
	);
}

int ShooterPlayer::hp() const noexcept {
	return this->_hp;
}

void ShooterPlayer::hp(int value) noexcept {
	this->_hp = value < 0 ? 0 : value;
}

void ShooterPlayer::process(game::Game* g, screen_::Screen* s, char key) {
	if (this->_hp <= 0) {
		g->over();
		this->_status = game::Status::Dangle;
		return;
	}

	// First process
	if (this->_first_process) {
		this->_first_process = false;

		s->init_color(
			this->_HIGH_HP_COLOR_ID, this->_HIGH_HP_COLOR_FG, this->_HIGH_HP_COLOR_BG
		);
		s->init_color(
			this->_LOW_HP_COLOR_ID, this->_LOW_HP_COLOR_FG, this->_LOW_HP_COLOR_BG
		);

		// Change default position
		if (this->_point.x() == 0 && this->_point.y() == 0) {
			this->_point.x((s->width() - this->symbol().size() - 1) / 2);
			this->_point.y(s->height() - 2);
		}
	}

	// Handle key
	switch (key) {
	case 'k':
		this->_point.y(this->_point.y() - 1);
		break;
	case 'j':
		this->_point.y(this->_point.y() + 1);
		break;
	case 'h':
		this->_point.x(this->_point.x() - 2);
		break;
	case 'l':
		this->_point.x(this->_point.x() + 2);
		break;
	}

	// Clamp coordinates
	std::vector<std::string> symbol_lines = this->symbol_lines();
	size_t max_width = 0;
	for (const std::string& line : symbol_lines) {
		if (line.size() > max_width) {
			max_width = line.size();
		}
	}
	this->_point.x(std::clamp(
		this->_point.x(), 0, s->width() - static_cast<int>(max_width)
	));
	this->_point.y(std::clamp(
		this->_point.y(), 0, s->height() - static_cast<int>(symbol_lines.size())
	));

	// Draw
	int color_id = this->_hp > this->_HP / 2
		? this->_HIGH_HP_COLOR_ID : this->_LOW_HP_COLOR_ID;
	s->set_bold();
	s->set_color(color_id);
	s->out(this->_point, this->symbol());
	s->unset_color(color_id);
	s->unset_bold();
}

long ShooterPlayer::score() const noexcept {
	return this->_score;
}

void ShooterPlayer::score(long value) noexcept {
	this->_score = value;
}

std::string ShooterPlayer::symbol() noexcept {
	steady_clock_t now = steady_clock::now();
	if ((now - this->_animation_time) / 1ms < this->_SYMBOL1_DELAY) {
		return this->_SYMBOL1;
	} else if (
		(now - this->_animation_time) / 1ms
		< this->_SYMBOL1_DELAY + this->_SYMBOL2_DELAY
	) {
		return this->_SYMBOL2;
	}
	this->_animation_time = now;
	return this->_SYMBOL1;
}

}
