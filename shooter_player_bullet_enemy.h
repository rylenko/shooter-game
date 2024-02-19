#pragma once

#include "game.h"
#include "sound_player.h"

namespace shooter_player_bullet_enemy {

class ShooterPlayerBulletEnemy: public game::Activity {
	private:
		static const long _SCORE = 10;
		static const int _DAMAGE = 15;

		sound_player::SoundPlayer _sound_player =
			sound_player::SoundPlayer("../resources/shooter_enemy_hurt.ogg");

	public:
		using game::Activity::Activity;
		void process(game::Game* g, screen_::Screen* s, char key) override;
};

}
