#include "sound_player.h"

namespace sound_player {

SoundPlayer::SoundPlayer(const std::string& path) {
	this->_buffer.loadFromFile(path);
}

void SoundPlayer::play() {
	steady_clock_t now = steady_clock::now();

	// Clear old sounds
	if (
		(now - this->_last_sound_time) / 1ms
		> this->_buffer.getDuration().asMilliseconds()
	) {
		this->_sounds.clear();
	}

	// Play new sound
	this->_sounds.emplace_back();
	this->_sounds.back().setBuffer(this->_buffer);
	this->_sounds.back().play();
	this->_last_sound_time = now;
}

}
