/*
 * sprite_animator.cpp
 *
 *  Created on: Dec 1, 2018
 *      Author: joey
 */
#include "sprite_animator.h"

void Sprite_Animator::setState(uint16_t anim_state) {
	current_anim_state = anim_state;
}
void Sprite_Animator::setMode(uint16_t mode) {
	current_anim_mode = mode;
}
void Sprite_Animator::Sprite_Animator (float frame) {
	current_frame_in_state = frame;
}
void Sprite_Animator::advanceFrames(float timeAmount) {
	current_frame_in_state += timeAmount;
}
Sprite Sprite_Animator::getCurrentSprite() {
	// Select the state based on current time and modulus the current size of the number of sprites
	return state_mode_to_frames_map[current_anim_state][current_anim_mode][((uint16_t)current_frame_in_state) % state_mode_to_frames_map[current_anim_state][current_anim_mode].size()];
}

Sprite_Animator::Sprite_Animator (uint16_t start_x, uint16_t start_y, uint16_t start_mode, uint16_t start_state, float start_frame) {
	x = start_x;
	y = start_y;
	current_anim_state = start_state;
	current_anim_mode = start_mode;
	current_frame_in_state = start_frame;
	wait_frames = 0;
	isVisible = true;
}

// Update function is implemented by every subclass. Essentially the animators state machine.
// animSetup function used for initializing the state mode frame map

