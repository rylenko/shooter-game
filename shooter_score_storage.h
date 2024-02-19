#pragma once

#include "score_storage.h"
#include "time.h"

namespace shooter_score_storage {

class ShooterScoreStorage: public score_storage::ScoreStorage {
	private:
		constexpr static const char* _PATH = "../resources/score";
		static const int _LOAD_DELAY = 5500;

		std::vector<std::string> _scores;
		steady_clock_t _last_load_time;

	public:
		ShooterScoreStorage() = default;
		void clear() override;
		const std::vector<std::string>& load_all() override;
		void save(const game::Game* game, const std::string& username) override;
};

}
