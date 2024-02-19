#include <sstream>
#include "shooter_bullet.h"
#include "shooter_decor.h"
#include "shooter_enemy.h"
#include "shooter_player.h"

namespace shooter_decor {

void ShooterDecor::process(game::Game* g, screen_::Screen* s, char key) {
	std::stringstream buf;

	// Handle keys
	switch (key) {
	case 'q':
		g->need_to_quit(true);
		return;
	case 'r':
		g->restart();
		break;
	}

	// Debug statistics
	s->out(
		screen_::Point(1, 5),
		"_activities: " + std::to_string(g->activities().size())
	);

	// Title
	s->set_bold();
	s->set_underline();
	s->out(
		screen_::Point((s->width() - this->_TITLE.size()) / 2, 1),
		this->_TITLE
	);
	s->unset_underline();
	s->unset_bold();

	// Game over
	if (g->is_over()) {
		if (!this->_game_over_sound_played) {
			this->_game_over_sound_played = true;
			this->_game_over_sound_player.play();
		}
		s->set_underline();
		s->out(
			screen_::Point((s->width() - this->_GAME_OVER.size()) / 2, s->height() / 2),
			this->_GAME_OVER
		);
		s->unset_underline();
	}

	// Bullets on the screen
	buf = std::stringstream();
	buf << "Bullets: " << g->
		get_activities_count<shooter_bullet::ShooterBullet>();
	s->out(this->_BULLETS_STATS_POINT, buf.str());

	// Player statistics
	auto* player = g->get_activity<shooter_player::ShooterPlayer>();
	buf = std::stringstream();
	buf << "HP: " << player->hp() << "; Score: " << player->score();
	s->out(this->_PLAYER_STATS_POINT, buf.str());

	// Enemies on the screen
	buf = std::stringstream();
	buf << "Enemies: " << g->get_activities_count<shooter_enemy::ShooterEnemy>();
	s->out(this->_ENEMIES_STATS_POINT, buf.str());
}

}
