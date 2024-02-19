#include "shooter_bullet.h"
#include "shooter_player.h"
#include "shooter_player_bullet.h"

namespace shooter_player_bullet {

void ShooterPlayerBullet::process(
	game::Game* g, screen_::Screen* s, char key
) {
	// Get player and bullets
	auto* player = g->get_activity<shooter_player::ShooterPlayer>();
	if (player->hp() <= 0) {
		this->_status = game::Status::Trash;
		return;
	}
	auto bullets = g->get_activities<shooter_bullet::ShooterBullet>();

	// Handle keys
	switch (key) {
	case ' ':
		g->add_activity(
			std::make_unique<shooter_bullet::ShooterBullet>(
				player->face(), shooter_bullet::Direction::Up
			)
		);
		break;
	}

	// Check bullets collided with player
	for (auto& bullet : bullets) {
		bullet->point().y(bullet->point().y() - 1);
		bool collided_jump = player->collided_with(bullet);
		bullet->point().y(bullet->point().y() + 1);

		if (collided_jump || player->collided_with(bullet)) {
			this->_sound_player.play();
			bullet->status(game::Status::Trash);
			player->hp(player->hp() - this->_DAMAGE);
		}
	}
}

}
