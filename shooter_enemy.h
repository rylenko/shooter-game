#pragma once

#include "game.h"
#include "time.h"

namespace shooter_enemy {

class ShooterEnemy: public game::Activity {
	private:
		static const int _COLOR_ID_1 = 123;
		static const int _COLOR_ID_2 = 124;
		static const color::Color _COLOR_BG = color::Color::Black;
		static const color::Color _COLOR_FG_1 = color::Color::Green;
		static const color::Color _COLOR_FG_2 = color::Color::Magenta;
		inline static const std::string _SYMBOL = "\\-o.o-/\n \\---/";

		static const int _MOVE_DELAY = 75;

		int _color_id;
		bool _first_process = true;
		steady_clock_t _last_time;

	public:
		ShooterEnemy(screen_::Point point) noexcept;
		screen_::Point face() noexcept;

		void process(game::Game* g, screen_::Screen* s, char key) override;
		std::string symbol() noexcept override;
};

}
