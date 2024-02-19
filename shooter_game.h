#pragma once

#include <SFML/Audio.hpp>
#include "game.h"

namespace shooter_game {

class ShooterGame: public game::Game {
	private:
		constexpr static const char* _MUSIC_PATH = "../resources/shooter_music.ogg";
		constexpr static const float _MUSIC_VOLUME = 50.0;

		sf::Music _music;

	public:
		ShooterGame() = default;
		void restart() noexcept override;
};

}
