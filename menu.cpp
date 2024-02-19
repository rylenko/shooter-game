#include "menu.h"

namespace menu {

bool Menu::need_to_start() const noexcept {
	return this->_need_to_start;
}

void Menu::need_to_start(bool value) noexcept {
	this->_need_to_start = value;
}

bool Menu::need_to_quit() const noexcept {
	return this->_need_to_quit;
}

}
