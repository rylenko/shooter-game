#pragma once

#include "game.h"
#include "sound_player.h"

namespace shooter_player_bullet {

class ShooterPlayerBullet: public game::Activity {
	private:
		static const int _DAMAGE = 10;

		sound_player::SoundPlayer _sound_player =
			sound_player::SoundPlayer("../resources/shooter_player_hurt.ogg");

	public:
		using game::Activity::Activity;
		void process(game::Game* g, screen_::Screen* s, char key) override;
};

}
