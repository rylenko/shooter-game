#include "shooter_game.h"
#include "shooter_decor.h"
#include "shooter_enemies.h"
#include "shooter_enemy.h"
#include "shooter_menu.h"
#include "shooter_player.h"
#include "shooter_player_bullet.h"
#include "shooter_player_bullet_enemy.h"
#include "shooter_player_enemy.h"

namespace shooter_game {

void ShooterGame::restart() noexcept {
	// Play music
	this->_music.openFromFile(this->_MUSIC_PATH);
	this->_music.setVolume(this->_MUSIC_VOLUME);
	this->_music.setLoop(true);
	this->_music.play();

	// Refresh the game
	this->_is_over = false;
	this->_need_to_quit = false;
	this->_activities.clear();

	// Add activities
	this->add_activity(std::make_unique<shooter_player::ShooterPlayer>());
	this->add_activity(
		std::make_unique<shooter_player_bullet::ShooterPlayerBullet>()
	);
	this->add_activity(std::make_unique<shooter_enemies::ShooterEnemies>());
	this->add_activity(
		std::make_unique<shooter_player_bullet_enemy::ShooterPlayerBulletEnemy>()
	);
	this->add_activity(
		std::make_unique<shooter_player_enemy::ShooterPlayerEnemy>()
	);
	this->add_activity(std::make_unique<shooter_decor::ShooterDecor>());
}

}
