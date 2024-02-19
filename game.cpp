#include <algorithm>
#include <sstream>
#include "game.h"

namespace game {

Activity::Activity(screen_::Point point) noexcept: _point(point) {}

bool Activity::collided_with(Activity* a) noexcept {
	std::vector<std::string> this_lines = this->symbol_lines();
	std::vector<std::string> a_lines = a->symbol_lines();

	for (size_t i1 = 0; i1 < this_lines.size(); ++i1) {
		for (size_t i2 = 0; i2 < a_lines.size(); ++i2) {
			if (this->_point.y() + i1 != a->_point.y() + i2) {
				continue;
			}
			for (size_t j1 = 0; j1 < this_lines[i1].size(); ++j1) {
				for (size_t j2 = 0; j2 < a_lines[i2].size(); ++j2) {
					if (this->_point.x() + j1 != a->_point.x() + j2) {
						continue;
					} else if (this_lines[i1][j1] != ' ' && a_lines[i2][j2] != ' ') {
						return true;
					}
				}
			}
		}
	}
	return false;
}

screen_::Point& Activity::point() noexcept {
	return this->_point;
}

std::string Activity::symbol() noexcept {
	return this->_EMPTY_SYMBOL;
}

Status Activity::status() const noexcept {
	return this->_status;
}

void Activity::status(Status value) noexcept {
	this->_status = value;
}

std::vector<std::string> Activity::symbol_lines() noexcept {
	std::vector<std::string> lines;
	std::string line;
	std::istringstream s(this->symbol());
	while (std::getline(s, line)) {
		lines.push_back(line);
	}
	return lines;
}

size_t Activity::symbol_lines_count() noexcept {
	size_t rv = 0;
	for (const char& ch : this->symbol()) {
		if (ch == '\n') {
			++rv;
		}
	}
	return rv;
}

std::vector<std::unique_ptr<Activity>>& Game::activities()
noexcept {
	return this->_activities;
}

void Game::add_activity(std::unique_ptr<Activity> a) noexcept {
	this->_activities.push_back(std::move(a));
}

bool Game::is_over() const noexcept {
	return this->_is_over;
}

bool Game::need_to_quit() const noexcept {
	return this->_need_to_quit;
}

void Game::need_to_quit(bool value) noexcept {
	this->_need_to_quit = value;
}

void Game::over() noexcept {
	this->_is_over = true;
}

void Game::process(screen_::Screen* s, char key) {
	// Process activities
	for (size_t i = this->_activities.size() - 1;; i--) {
		std::unique_ptr<Activity>& a = this->_activities[i];
		if (a->status() == Status::Ok) {
			a->process(this, s, key);
		}
		if (i == 0) {
			break;
		}
	}

	// Remove trash
	this->_activities.erase(
		std::remove_if(
			this->_activities.begin(),
			this->_activities.end(),
			[&](std::unique_ptr<Activity>& a) { return a->status() == Status::Trash; }
		),
		this->_activities.end()
	);
}

}
