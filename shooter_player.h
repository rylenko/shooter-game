#pragma once

#include "game.h"
#include "time.h"

namespace shooter_player {

class ShooterPlayer: public game::Activity {
	private:
		static const int _HIGH_HP_COLOR_ID = 100;
		static const color::Color _HIGH_HP_COLOR_BG = color::Color::Black;
		static const color::Color _HIGH_HP_COLOR_FG = color::Color::White;
		static const int _LOW_HP_COLOR_ID = 101;
		static const color::Color _LOW_HP_COLOR_BG = color::Color::Black;
		static const color::Color _LOW_HP_COLOR_FG = color::Color::Red;
		static const int _HP = 100;

		static const int _SYMBOL1_DELAY = 1000;
		static const int _SYMBOL2_DELAY = 1000;
		inline static const std::string _SYMBOL1 = " /.\\\n/...\\";
		inline static const std::string _SYMBOL2 = " /x\\\n/xxx\\";

		steady_clock_t _animation_time;
		bool _first_process = true;
		long _score = 0;
		int _hp = _HP;

	public:
		using game::Activity::Activity;
		screen_::Point face() noexcept;

		void hp(int value) noexcept;
		int hp() const noexcept;

		void score(long value) noexcept;
		long score() const noexcept;

		void process(game::Game* g, screen_::Screen* s, char key) override;
		std::string symbol() noexcept override;
};

}
