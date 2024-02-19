#include "screen.h"

namespace screen_ {

Point::Point(int x, int y) noexcept: _x(x), _y(y) {}

int Point::x() const noexcept {
	return this->_x;
}

void Point::x(int value) noexcept {
	this->_x = value;
}

int Point::y() const noexcept {
	return this->_y;
}

void Point::y(int value) noexcept {
	this->_y = value;
}

}
