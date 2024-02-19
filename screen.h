#pragma once

#include <string>
#include "color.h"

namespace screen_ {

class Point {
	private:
		int _x;
		int _y;

	public:
		Point(int x, int y) noexcept;

		int x() const noexcept;
		void x(int value) noexcept;

		int y() const noexcept;
		void y(int value) noexcept;
};

class Screen {
	public:
		virtual ~Screen() = default;

		virtual int height() const noexcept = 0;
		virtual int width() const noexcept = 0;

		virtual void init_color(int id, color::Color fg, color::Color bg) = 0;
		virtual void set_color(int id) = 0;
		virtual void unset_color(int id) = 0;

		virtual void set_underline() = 0;
		virtual void unset_underline() = 0;

		virtual void set_bold() = 0;
		virtual void unset_bold() = 0;

		virtual void clear() = 0;
		virtual char read() = 0;
		virtual void refresh() = 0;
		virtual void out(Point point, const std::string& s) = 0;
};

}
