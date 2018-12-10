/*
 * player.h
 *
 *  Created on: Dec 1, 2018
 *      Author: joey
 */

#ifndef INCLUDE_PLAYER_H_
#define INCLUDE_PLAYER_H_


#include "../include/config.h"
#include <iostream>
#include "../include/item.h"
#include "../include/sprite.h"
#include "../include/sprite_animator.h"
#include "../include/keyboard.h"
using namespace std;

class Background;
class Sprite_Animator;

// Represents a playable character
class Player : public Sprite_Animator {
public:
	const float MAX_WALK_SPEED = 2; // Max amount that can be added per frame
	const float WALK_ACCEL = .1;
	const float JUMP_MOVE_ACCEL = .02;
	const float MAX_JUMP_MOVE_SPEED = 1;
	const float JUMP_VEL = 3;
	const float SLIDING_SPEED_SLOW = .05;
	const float ANIMATION_SPEED = .2; // Variable to vary the speed of anim based on velocity. Multiplied by speed of walking
	const uint16_t ENLARGING_NUM_FRAMES = 60;
	const uint16_t SHRINKING_NUM_FRAMES = 60;
	const uint16_t FIREFLOWER_NUM_FRAMES = 30; // Number of frames to pause when getting a fireflower when big
	const uint16_t INVINCIBILITY_NUM_FRAMES = 200;
	// Num fireballs in existance is current_background->fireballs.size(). Background should get rid of ones off screen
	const uint16_t MAX_FIREBALLS_IN_EXISTANCE = 2; // Max fireballs that can exist at a time
	const uint16_t FIREBALL_X_DIST_FROM_MARIO = 10;
	const uint16_t FIREBALL_Y_DIST_FROM_MARIO = 15;
	const float FIREBALL_X_VEL = .3;
	const float FIREBALL_Y_VEL = .2;
	const uint16_t PLAYER_JUMP_ON_ENEMY_BOOST = 3; // Speed jump boost when mario lands on a enemy
	Rect_Collider player_collider;
	enum modes {NORMAL_MODE = 0, MINI_MODE, FIRE_MODE, INVINCIBLE_MODE}; // Mario power up states
	enum states {IDLE = 0, WALKING, JUMPING, CROUCHING, SHRINKING, FLAGDOWN, ENLARGING, FLIPPING, DYING, THROWFIREBALL, SLIDING};
	float accelX, accelY;
	float velX, velY;
	bool enablePlayerControl;
	bool enemyCanKill;
	bool noCollide;
	bool inAir;
	uint16_t invincibility_frames;
	bool hasJumped; // bool to determine if he has jumped before. Set to false when he hits the ground
	uint16_t return_state; // Only used by enlarge and shrink states when mario gets hit. Returns to this state after the pause and animation
	Player(uint16_t x, uint16_t y);
	const static uint16_t PLAYER_COLLIDER_WIDTH = 16;
	const static uint16_t PLAYER_COLLIDER_HEIGHT = 32;
	void animatorSetup(); // Initialize all the animation states of the sprite
	void draw(); // function to draw player. Called AFTER update
	void update(); // player state machine
	bool isInAir(); // Function for if Mario is in  midair
	Background * current_background; // Init keyboard at beginning
	void collided_with(Rect_Collider & other);
	void setBackground(Background * b);
	void throwFireball();
	void idleState();
	void walkingState();
	void jumpingState();
	void shrinkingState();
	void crouchingState();
	void dyingState();
	void flippingState();
	void enlargingState();
	void flagdownState();
	void throwfireballState();
	void slidingState();
	bool hitByEnemy();
	bool getsMushroom();
	bool getsFireflower();
	void gravity(); // Does gravity ooo
	bool gotMushroom, gotFireflower, gotHitByEnemy;
};



#endif /* INCLUDE_PLAYER_H_ */
