#include "shooter_bullet.h"
#include "shooter_enemy.h"
#include "shooter_player.h"
#include "shooter_player_bullet_enemy.h"

namespace shooter_player_bullet_enemy {

void ShooterPlayerBulletEnemy::process(
	game::Game* g, screen_::Screen* s, char key
) {
	if (g->is_over()) {
		this->_status = game::Status::Trash;
		return;
	}

	// Get player, bullets and enemies
	auto* player = g->get_activity<shooter_player::ShooterPlayer>();
	auto bullets = g->get_activities<shooter_bullet::ShooterBullet>();
	auto enemies = g->get_activities<shooter_enemy::ShooterEnemy>();

	for (auto* enemy : enemies) {
		// Check enemy collided with bullet
		for (auto& bullet : bullets) {
			bullet->point().y(bullet->point().y() - 1);
			bool collided_jump = enemy->collided_with(bullet);
			bullet->point().y(bullet->point().y() + 1);

			if (collided_jump || enemy->collided_with(bullet)) {
				this->_sound_player.play();
				enemy->status(game::Status::Trash);
				bullet->status(game::Status::Trash);
				player->score(player->score() + this->_SCORE);
			}
		}

		// Enemies shoot in the player
		if (enemy->point().x() == player->point().x() && rand() % 3 == 0) {
			g->add_activity(
				std::make_unique<shooter_bullet::ShooterBullet>(
					enemy->face(), shooter_bullet::Direction::Down
				)
			);
		}
	}
}

}
