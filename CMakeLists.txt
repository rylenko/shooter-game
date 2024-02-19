cmake_minimum_required(VERSION 3.16)

project(game CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

add_executable(
	${PROJECT_NAME}
	curses_screen.cpp
	game.cpp
	main.cpp
	menu.cpp
	screen.cpp
	shooter_bullet.cpp
	shooter_decor.cpp
	shooter_enemies.cpp
	shooter_enemy.cpp
	shooter_game.cpp
	shooter_saver.cpp
	shooter_score_storage.cpp
	shooter_menu.cpp
	shooter_player.cpp
	shooter_player_bullet.cpp
	shooter_player_bullet_enemy.cpp
	shooter_player_enemy.cpp
	sound_player.cpp
	utils.cpp
)

# Curses
target_link_libraries(${PROJECT_NAME} curses)

# SFML
target_link_libraries(${PROJECT_NAME} sfml-audio sfml-system)
