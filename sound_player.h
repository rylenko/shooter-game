#pragma once

#include <SFML/Audio.hpp>
#include <utility>
#include "time.h"

namespace sound_player {

class SoundPlayer {
	private:
		sf::SoundBuffer _buffer;
		std::vector<sf::Sound> _sounds;
		steady_clock_t _last_sound_time;

	public:
		SoundPlayer(const std::string& path);
		void play();
};

}
