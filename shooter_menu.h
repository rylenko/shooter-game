#pragma once

#include <vector>
#include "menu.h"
#include "sound_player.h"
#include "time.h"

namespace shooter_menu {

class ShooterMenu: public menu::Menu {
	private:
		// Scores
		inline static const std::string _SCORES = "SCORES:";
		inline static const screen_::Point _SCORES_POINT = screen_::Point(1, 1);

		// Title
		static const int _TITLE_Y = 1;
		inline static const std::string _TITLE = "--- Shooter Game ---";

		// Help
		static const int _HELP_Y = 2;
		inline static const std::string _HELP =
			"Space to submit or shoot, h/j/k/l or arrows for movement.";

		// Default values
		inline static const std::string _DEFAULT_USERNAME = "Unknown";

		// Buttons
		inline static const std::vector<std::string> _BUTTONS = {
			"USERNAME: ",
			"START",
			"SAVE (Press it game is still ongoing)",
			"SAVE SCORE (Press it after game over)",
			"CLEAR SCORES",
			"CLEAR SAVES",
			"QUIT"
		};

		// Username
		bool _username_input_is_active = true;
		std::string _username_input = _DEFAULT_USERNAME;

		// Sounds
		sound_player::SoundPlayer _click_sound_player =
			sound_player::SoundPlayer("../resources/shooter_click.ogg");

		char _active_button = 0;

		void _draw_buttons(screen_::Screen* s) const noexcept;
		void _draw_save_filenames(
			saver::Saver* saver,
			screen_::Screen* s
		) const noexcept;
		void _draw_scores(
			score_storage::ScoreStorage* score_storage,
			screen_::Screen* s
		) const noexcept;
		void _draw_title_and_help(screen_::Screen* s) const noexcept;
		void _handle_key(
			game::Game* g,
			saver::Saver* saver,
			score_storage::ScoreStorage* score_storage,
			char key
		) noexcept;
		void _input_username(char key) noexcept;
		void _read_scores_filenames();

	public:
		ShooterMenu() = default;
		void process(
			game::Game* g,
			saver::Saver* saver,
			score_storage::ScoreStorage* score_storage,
			screen_::Screen* screen,
			char key
		) override;
};

}
