/*
 * enemies.cpp
 *
 *  Created on: Nov 29, 2018
 *      Author: joey
 */
#include "enemies.h"


void Turtle::animatorSetup() {
	Sprite turtle_up(x, y, 16, 32, ADDRESS_OFFSET + 759585);
	Sprite turtle_walk_1(x, y, 16, 32, ADDRESS_OFFSET + 761637);
	Sprite turtle_walk_2(x, y, 16, 32, ADDRESS_OFFSET + 760098);
	Sprite turtle_shell_frame_1(x, y, 16, 32, ADDRESS_OFFSET + 760611);
	state_mode_to_frames_map[WALKING][NORMAL_MODE].push_back(turtle_walk_1);
	state_mode_to_frames_map[WALKING][NORMAL_MODE].push_back(turtle_walk_2);
	state_mode_to_frames_map[SHELL][NORMAL_MODE].push_back(turtle_shell_frame_1);
	state_mode_to_frames_map[SHELL_MOVING][NORMAL_MODE].push_back(turtle_shell_frame_1);
	state_mode_to_frames_map[GET_UP][NORMAL_MODE].push_back(turtle_up);
	state_mode_to_frames_map[DYING_FIREBALL][NORMAL_MODE].push_back(turtle_shell_frame_1);

}

void Gumba::animatorSetup() {
	Sprite walking_1(x, y, 16, 32, 762663);
	Sprite walking_2(x, y, 16, 32, 761124);
	Sprite goomba_die_frame_1 (0, 0, 16, 32, ADDRESS_OFFSET + 762150);
	state_mode_to_frames_map[WALKING][NORMAL_MODE].push_back(walking_1);
	state_mode_to_frames_map[WALKING][NORMAL_MODE].push_back(walking_2);
	state_mode_to_frames_map[DYING][NORMAL_MODE].push_back(goomba_die_frame_1);
	state_mode_to_frames_map[DYING_FIREBALL][NORMAL_MODE].push_back(walking_1);

}
/*
 * TODO
 * Implement Gumba state machine
 */
void Gumba::update() {

}

/*
 * TODO
 * Implement Turtle state machine
 */
void Turtle::update() {

}
