#include <chrono>
#include <fstream>
#include <iomanip>
#include "shooter_menu.h"

namespace shooter_menu {

std::string _generate_filename();

void ShooterMenu::process(
	game::Game* g,
	saver::Saver* saver,
	score_storage::ScoreStorage* score_storage,
	screen_::Screen* s,
	char key
) {
	this->_need_to_start = false;

	this->_handle_key(g, saver, score_storage, key);
	this->_draw_buttons(s);
	this->_draw_scores(score_storage, s);
	this->_draw_save_filenames(saver, s);
	this->_draw_title_and_help(s);
}

void ShooterMenu::_draw_buttons(screen_::Screen* s) const noexcept {
	int y = (s->height() - this->_BUTTONS.size()) / 2;

	// Username input
	std::string username_button = this->_BUTTONS[0] + this->_username_input;
	if (this->_active_button == 0) {
		s->set_underline();
		s->set_bold();
		username_button = "* " + username_button;
	}
	if (this->_username_input_is_active) {
		username_button += '|';
	}
	s->out(
		screen_::Point(
			(s->width() - this->_BUTTONS[0].size() - this->_username_input.size())
				/ 2,
			y
		),
		username_button
	);
	if (this->_active_button == 0) {
		s->unset_underline();
		s->unset_bold();
	}

	// Static buttons
	for (size_t i = 1; i < this->_BUTTONS.size(); ++i) {
		if (this->_active_button == i) {
			s->set_underline();
			s->set_bold();
		}
		s->out(
			screen_::Point((s->width() - this->_BUTTONS[i].size()) / 2, y + i),
			this->_active_button == i ? "* " + this->_BUTTONS[i] : this->_BUTTONS[i]
		);
		if (this->_active_button == i) {
			s->unset_underline();
			s->unset_bold();
		}
	}
}

void ShooterMenu::_draw_save_filenames(
	saver::Saver* saver,
	screen_::Screen* s
) const noexcept {
	const std::vector<std::string>& filenames = saver->load_filenames();
	for (size_t i = 0; i < filenames.size(); ++i) {
		bool active = this->_active_button == this->_BUTTONS.size() + i;
		if (active) {
			s->set_underline();
			s->set_bold();
		}
		s->out(
			screen_::Point(s->width() * 2 / 3, s->height() / 3 + i),
			active ? "* " + filenames[i] : filenames[i]
		);
		if (active) {
			s->unset_underline();
			s->unset_bold();
		}
	}
}

void ShooterMenu::_draw_scores(
	score_storage::ScoreStorage* score_storage,
	screen_::Screen* s
) const noexcept {
	s->out(this->_SCORES_POINT, this->_SCORES);
	const std::vector<std::string>& scores = score_storage->load_all();
	for (size_t i = 0; i < scores.size(); ++i) {
		s->out(
			screen_::Point(this->_SCORES_POINT.x(), this->_SCORES_POINT.y() + 1 + i),
			scores[i]
		);
	}
}

void ShooterMenu::_draw_title_and_help(screen_::Screen* s) const noexcept {
	s->set_underline();
	s->set_bold();
	s->out(
		screen_::Point((s->width() - this->_TITLE.size()) / 2, this->_TITLE_Y),
		this->_TITLE
	);
	s->out(
		screen_::Point((s->width() - this->_HELP.size()) / 2, this->_HELP_Y),
		this->_HELP
	);
	s->unset_underline();
	s->unset_bold();
}

void ShooterMenu::_handle_key(
	game::Game* g,
	saver::Saver* saver,
	score_storage::ScoreStorage* score_storage,
	char key
) noexcept {
	const std::vector<std::string>& save_filenames = saver->load_filenames();
	if (this->_username_input_is_active && key != ' ') {
		this->_input_username(key);
	} else {
		switch (key) {
		case 'j':
			++this->_active_button;
			if (
				this->_active_button >= this->_BUTTONS.size() + save_filenames.size()
			) {
				this->_active_button = 0;
			}
			break;
		case 'k':
			this->_active_button--;
			if (this->_active_button < 0) {
				this->_active_button = this->_BUTTONS.size() + save_filenames.size() - 1;
			}
			break;
		case ' ':
			this->_click_sound_player.play();
			switch (this->_active_button) {
			case 0:
				this->_username_input_is_active = !this->_username_input_is_active;
				break;
			case 1:
				this->_need_to_start = true;
				g->restart();
				break;
			case 2:
				if (g->need_to_quit() && !g->is_over()) {
					saver->save(g, this->_username_input + "-" + _generate_filename());
				}
				break;
			case 3:
				if (g->need_to_quit() && g->is_over()) {
					score_storage->save(g, this->_username_input);
				}
				break;
			case 4:
				score_storage->clear();
				break;
			case 5:
				saver->clear();
				break;
			case 6:
				if (this->_username_input.empty()) {
					this->_username_input = this->_DEFAULT_USERNAME;
				}
				this->_need_to_quit = true;
				break;
			}

			// Select a save
			if (this->_active_button >= this->_BUTTONS.size()) {
				g->restart();
				const std::string filename =
					save_filenames[this->_active_button - this->_BUTTONS.size()];
				saver->load(g, filename);
				this->_need_to_start = true;
			}
			break;
		}
	}
}

void ShooterMenu::_input_username(char key) noexcept {
	if (key == '\b' && this->_username_input.size() > 0) {
		this->_username_input.pop_back();
	} else if (('a' <= key && key <= 'z') || ('A' <= key && key <= 'Z'))  {
		this->_username_input += key;
	}
}

std::string _generate_filename() {
	auto now = std::chrono::system_clock::now();
	auto local_time = std::chrono::system_clock::to_time_t(now);
	std::stringstream stream;
	stream << std::put_time(std::localtime(&local_time), "%F_%H-%M-%S");
	return stream.str();
}

}
