#pragma once

#include "game.h"

namespace score_storage {

class ScoreStorage {
	public:
		virtual ~ScoreStorage() = default;
		virtual void clear() = 0;
		virtual const std::vector<std::string>& load_all() = 0;
		virtual void save(const game::Game* game, const std::string& username) = 0;
};

}
