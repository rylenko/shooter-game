#include <filesystem>
#include <fstream>
#include <stdexcept>
#include "shooter_saver.h"
#include "shooter_bullet.h"
#include "shooter_enemy.h"
#include "shooter_player.h"

namespace shooter_saver {

void ShooterSaver::clear() {
	for (const auto& filename : this->_filenames) {
		std::remove((this->_DIR + filename).c_str());
	}
	this->_filenames.clear();
}

void ShooterSaver::load(game::Game* g, const std::string& filename) {
	int x;
	int y;
	int hp;
	long score;
	int direction_number;

	std::ifstream stream(this->_DIR + filename);

	// Player
	auto* player = g->get_activity<shooter_player::ShooterPlayer>();
	stream >> x >> y >> hp >> score;
	player->point().x(x);
	player->point().y(y);
	player->hp(hp);
	player->score(score);

	// Enemies
	for (size_t i = 0; i < this->_ENEMY_SLOTS_COUNT; ++i) {
		stream >> x >> y;
		if (x != this->_INVALID_COORDINATE && y != this->_INVALID_COORDINATE) {
			g->add_activity(
				std::make_unique<shooter_enemy::ShooterEnemy>(screen_::Point(x, y))
			);
		}
	}

	// Bullets
	for (size_t i = 0; i < this->_BULLET_SLOTS_COUNT; ++i) {
		stream >> x >> y >> direction_number;
		if (x != this->_INVALID_COORDINATE && y != this->_INVALID_COORDINATE) {
			g->add_activity(
				std::make_unique<shooter_bullet::ShooterBullet>(
					screen_::Point(x, y),
					static_cast<shooter_bullet::Direction>(direction_number)
				)
			);
		}
	}
}

const std::vector<std::string>& ShooterSaver::load_filenames() {
	steady_clock_t now = steady_clock::now();
	if (
		(now - this->_filenames_last_load_time) / 1ms > this->_FILENAMES_LOAD_DELAY
	) {
		this->_filenames_last_load_time = now;
		this->_filenames.clear();

		for (const auto& entry : std::filesystem::directory_iterator(this->_DIR)) {
			std::string path = entry.path();
			std::string filename = path.substr(path.rfind("/") + 1);
			if (filename != this->_EXCLUDE_FILENAME) {
				this->_filenames.insert(this->_filenames.begin(), filename);
			}
		}
	}
	return this->_filenames;
}

void ShooterSaver::save(const game::Game* g, const std::string& filename) {
	std::ofstream stream(this->_DIR + filename);

	// Player
	auto* player = g->get_activity<shooter_player::ShooterPlayer>();
	stream << player->point().x() << std::endl
		<< player->point().y() << std::endl
		<< player->hp() << std::endl
		<< player->score() << std::endl;

	// Enemies
	auto enemies = g->get_activities<shooter_enemy::ShooterEnemy>();
	if (enemies.size() > this->_ENEMY_SLOTS_COUNT) {
		throw std::runtime_error("save: Enemies count greater than slots count.");
	}
	for (size_t i = 0; i < this->_ENEMY_SLOTS_COUNT; ++i) {
		if (i >= enemies.size()) {
			stream << this->_INVALID_COORDINATE << std::endl
				<< this->_INVALID_COORDINATE << std::endl;
		} else {
			stream << enemies[i]->point().x() << std::endl
				<< enemies[i]->point().y() << std::endl;
		}
	}

	// Bullets
	auto bullets = g->get_activities<shooter_bullet::ShooterBullet>();
	if (bullets.size() > this->_BULLET_SLOTS_COUNT) {
		throw std::runtime_error("save: Enemies count greater than slots count.");
	}
	for (size_t i = 0; i < this->_BULLET_SLOTS_COUNT; ++i) {
		if (i >= bullets.size()) {
			stream << this->_INVALID_COORDINATE << std::endl
				<< this->_INVALID_COORDINATE << std::endl;
		} else {
			stream << bullets[i]->point().x() << std::endl
				<< bullets[i]->point().y() << std::endl
				<< static_cast<int>(bullets[i]->direction()) << std::endl;
		}
	}
}

}
