#pragma once

#include "saver.h"
#include "time.h"

namespace shooter_saver {

class ShooterSaver: public saver::Saver {
	private:
		constexpr static const char* _DIR = "../resources/saves/";
		static const int _FILENAMES_LOAD_DELAY = 5500;
		constexpr static const char* _EXCLUDE_FILENAME = ".gitkeep";

		static const size_t _ENEMY_SLOTS_COUNT = 16;
		static const size_t _BULLET_SLOTS_COUNT = 256;
		static const int _INVALID_COORDINATE = -9999;

		std::vector<std::string> _filenames;
		steady_clock_t _filenames_last_load_time;

	public:
		ShooterSaver() = default;
		void clear() override;
		void load(game::Game* game, const std::string& filename) override;
		const std::vector<std::string>& load_filenames() override;
		void save(const game::Game* game, const std::string& filename) override;
};

}
