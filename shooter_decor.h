#pragma once

#include "game.h"
#include "sound_player.h"

namespace shooter_decor {

class ShooterDecor: public game::Activity {
	private:
		inline static const std::string _TITLE = "--- Shooter game ---";
		inline static const std::string _GAME_OVER = "--- Game over ---";

		inline static const screen_::Point _PLAYER_STATS_POINT =
			screen_::Point(1, 1);
		inline static const screen_::Point _BULLETS_STATS_POINT =
			screen_::Point(1, 2);
		inline static const screen_::Point _ENEMIES_STATS_POINT =
			screen_::Point(1, 3);

		sound_player::SoundPlayer _game_over_sound_player =
			sound_player::SoundPlayer("../resources/shooter_game_over.ogg");
		bool _game_over_sound_played = false;

	public:
		using game::Activity::Activity;
		void process(game::Game* g, screen_::Screen* s, char key) override;
};

}
