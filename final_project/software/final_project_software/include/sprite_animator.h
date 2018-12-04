/*
 * sprite_animator.h
 *
 *  Created on: Dec 1, 2018
 *      Author: joey
 */

#ifndef INCLUDE_SPRITE_ANIMATOR_H_
#define INCLUDE_SPRITE_ANIMATOR_H_
#include <map>
#include <vector>
using namespace std;
// Animator which is the base class for anything that moves
class Sprite_Animator {
protected:
	uint16_t x;
	uint16_t y;
	uint16_t wait_frames; // When set the state machine will continue in its current state until wait_frames is 0
	virtual ~Sprite_Animator();
	float current_frame_in_state; // Keeps track of the place in the sprites array
	uint16_t current_anim_state;
	uint16_t current_anim_mode;
	bool isVisible;
	// Constructor to init animator
	Sprite_Animator (uint16_t start_x, uint16_t start_y, uint16_t start_mode, uint16_t start_state, float start_frame);
	virtual void animatorSetup() = 0;
	// Draw method to be implimented by all animations to draw the current state
	virtual void draw() = 0;
	// State first, then mode map to sprites
	map <uint16_t, map<uint16_t, vector<Sprite>>> state_mode_to_frames_map; // Different subclasses must define own states
	// Change the animation type
	void setState(uint16_t state);
	void setMode(uint16_t mode);
	void setFrame(float frame);
	void advanceFrames(float timeAmount);

	Sprite getCurrentSprite();
	virtual void update() = 0;
};

#endif /* INCLUDE_SPRITE_ANIMATOR_H_ */
