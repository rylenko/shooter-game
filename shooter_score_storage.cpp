#include <fstream>
#include "shooter_score_storage.h"
#include "shooter_player.h"

namespace shooter_score_storage {

void ShooterScoreStorage::clear() {
	this->_scores.clear();
	std::ofstream _scores(this->_PATH, std::ios::trunc);
}

const std::vector<std::string>& ShooterScoreStorage::load_all() {
	steady_clock_t now = steady_clock::now();
	if ((now - this->_last_load_time) / 1ms > this->_LOAD_DELAY) {
		this->_last_load_time = now;
		this->_scores.clear();
		std::ifstream scores(this->_PATH);
		std::string line;
		while (std::getline(scores, line)) {
			this->_scores.push_back(line);
		}
	}
	return this->_scores;
}

void ShooterScoreStorage::save(
	const game::Game* g,
	const std::string& username
) {
	std::ofstream stream(this->_PATH, std::ios::app);

	auto* player = g->get_activity<shooter_player::ShooterPlayer>();
	std::string score = username + ": " + std::to_string(player->score());
	this->_scores.push_back(score);
	stream << score << std::endl;
}

}
