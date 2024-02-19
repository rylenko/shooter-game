#pragma once

#include "screen.h"

namespace curses_screen {

class CursesScreen: public screen_::Screen {
	private:
		static const int _INPUT_DELAY = 50;

		int _height;
		int _width;

		int _curses_color(color::Color color) const;

	public:
		CursesScreen();
		~CursesScreen();

		int height() const noexcept override;
		int width() const noexcept override;

		void init_color(int id, color::Color fg, color::Color bg) override;
		void set_color(int id) override;
		void unset_color(int id) override;

		void set_underline() override;
		void unset_underline() override;

		void set_bold() override;
		void unset_bold() override;

		void clear() override;
		char read() override;
		void refresh() override;
		void out(screen_::Point point, const std::string& s) override;
};

}
