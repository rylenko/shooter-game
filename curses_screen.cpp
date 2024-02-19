#include <sstream>
#include <stdexcept>
#include <curses.h>
#include "curses_screen.h"

namespace curses_screen {

CursesScreen::CursesScreen() {
	setlocale(LC_ALL, ""); // Unicode
	initscr(); // Initialize curses
	cbreak(); // Disable buffering
	noecho(); // Disable input character
	curs_set(FALSE); // Disable cursor
	keypad(stdscr, TRUE); // Enable function keys: arrows, etc.
	timeout(this->_INPUT_DELAY);
	if (has_colors() == FALSE) {
		throw std::runtime_error("Curses screen doesn't support colors.");
	}
	start_color();
	getmaxyx(stdscr, this->_height, this->_width);
}

CursesScreen::~CursesScreen() {
	endwin();
}

void CursesScreen::clear() {
	::clear();
}

int CursesScreen::height() const noexcept {
	return this->_height;
}

int CursesScreen::width() const noexcept {
	return this->_width;
}

void CursesScreen::init_color(int id, color::Color fg, color::Color bg) {
	init_pair(id, this->_curses_color(fg), this->_curses_color(bg));
}

void CursesScreen::out(screen_::Point point, const std::string& s) {
	int y = point.y();
	std::istringstream stream(s);
	std::string line;
	while (std::getline(stream, line)) {
		wmove(stdscr, y++, point.x());
		wprintw(stdscr, line.c_str());
	}
}

char CursesScreen::read() {
	int ch = getch();
	switch (ch) {
	case KEY_UP:
		return 'k';
	case KEY_DOWN:
		return 'j';
	case KEY_LEFT:
		return 'h';
	case KEY_RIGHT:
		return 'l';
	case KEY_BACKSPACE:
		return '\b';
	default:
		return ch;
	}
}

void CursesScreen::refresh() {
	::refresh();
}

void CursesScreen::set_color(int id) {
	attron(COLOR_PAIR(id));
}

void CursesScreen::set_bold() {
	attron(A_BOLD);
}

void CursesScreen::set_underline() {
	attron(A_UNDERLINE);
}

void CursesScreen::unset_color(int id) {
	attroff(COLOR_PAIR(id));
}

void CursesScreen::unset_bold() {
	attroff(A_BOLD);
}

void CursesScreen::unset_underline() {
	attroff(A_UNDERLINE);
}

int CursesScreen::_curses_color(color::Color color) const {
	switch (color) {
	case color::Color::Black:
		return COLOR_BLACK;
	case color::Color::Green:
		return COLOR_GREEN;
	case color::Color::Magenta:
		return COLOR_MAGENTA;
	case color::Color::Red:
		return COLOR_RED;
	case color::Color::White:
		return COLOR_WHITE;
	default:
		throw std::invalid_argument("Unknown color.");
	}
}

}
