#pragma once

#include "game.h"
#include "sound_player.h"

namespace shooter_bullet {

enum Direction {
	Down = 0,
	Up = 1,
};

class ShooterBullet: public game::Activity {
	private:
		static const int _COLOR_ID = 2;
		static const color::Color _COLOR_BG = color::Color::Black;
		static const color::Color _COLOR_FG = color::Color::Red;
		inline static const std::string _SYMBOL = "|\n|";
		static const int _MOVE_DELAY = 35;

		Direction _direction;
		steady_clock_t _last_time;

	public:
		ShooterBullet(screen_::Point, Direction direction) noexcept;

		Direction direction() const noexcept;
		void direction(Direction value) noexcept;

		void process(game::Game* g, screen_::Screen* s, char key) override;
		std::string symbol() noexcept override;
};

}
