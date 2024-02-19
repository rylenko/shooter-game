#include "shooter_enemy.h"
#include "shooter_player.h"
#include "shooter_player_enemy.h"

namespace shooter_player_enemy {

void ShooterPlayerEnemy::process(game::Game* g, screen_::Screen* s, char key) {
	// Get player, bullets and enemies
	auto* player = g->get_activity<shooter_player::ShooterPlayer>();
	auto enemies = g->get_activities<shooter_enemy::ShooterEnemy>();

	for (auto& enemy : enemies) {
		if (enemy->collided_with(player)) {
			// Enemy collided with player
			this->_sound_player.play();
			player->hp(player->hp() - this->_DAMAGE);
			player->score(player->score() + this->_SCORE);
			enemy->status(game::Status::Trash);
		} else if (
			enemy->point().y() + enemy->symbol_lines_count() >= s->height()
		) {
			// Enemy collided with barrier
			this->_sound_player.play();
			player->hp(player->hp() - this->_DAMAGE);
			player->score(player->score() - this->_SCORE);
		}
	}
}

}
