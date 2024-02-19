#pragma once

#include "game.h"

namespace saver {

class Saver {
	public:
		virtual void clear() = 0;
		virtual void load(game::Game* g, const std::string& filename) = 0;
		virtual const std::vector<std::string>& load_filenames() = 0;
		virtual void save(const game::Game* g, const std::string& filename) = 0;
};

}
