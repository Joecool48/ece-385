/*
 * player.cpp
 *
 *  Created on: Nov 30, 2018
 *      Author: joey
 */
#include "player.h"
#include <game_classes.h>
#include <iostream>
#include "config.h"
/*
 * TODO
 * Make sure to set background!!!
 */
void Player::setBackground(Background * b) {
	if (b == nullptr) {
		std::cout << "Player::setBackground: input is nullptr" << std::endl;
	}
	current_background = b;
}

/*
 * Constructs a new player object (Mario). This also calls animatorSetup to make sure all the sprites are filled.
 * Also inits the rect collider, initial mode, and state.
 */
Player::Player() {
	enablePlayerControl = true;
	enemyCanKill = true;
	accelX = 0, accelY = 0;
	velX = 0, velY = 0;
	invincibility_frames = 0;
	isFacingLeft = false;
	hasJumped = false;
	return_state = IDLE;
	current_background = nullptr;
}
/* TODO:
 * Maps all the states and modes to their respective series of sprite frames
 */
void Player::animatorSetup() {


}
/*
 * getKey returns NO_KEY if enablePlayerControl is off
 */
Key Player::getKey() {
	Key key = keyboard.getInputKey();
	if (key == Key::KEY_PAUSE || key == Key::NO_KEY) return key;
	if (!enablePlayerControl) {
		return Key::NO_KEY;
	}
	return key;
}
/*
 * TODO
 * Create player state machine
 */
void Player::update() {
	if (wait_frames) {
		wait_frames--;
		return;
	}
	// Invincibility code
	if (invincibility_frames == 1) {
		isVisible = false;
	}
	if (invincibility_frames > 0) {
		isVisible = ~isVisible; // Small animation to blink mario while invincible
		invincibility_frames--;
	}
	else {
		enemyCanKill = true;
	}
	/*
	 * TODO
	 * Set frames for the rest of the states. Make sure flag down gets it changed as well
	 */
	switch (current_anim_state) {
	case IDLE:
		idleState();
		break;
	case WALKING:
		advanceFrames(ANIMATION_SPEED * velX);
		walkingState();
		break;
	case JUMPING:
		setFrame(0);
		jumpingState();
		break;
	case SHRINKING: // Shrinking should set state to mini;
		setFrame(0);
		shrinkingState();
		break;
	case CROUCHING:
		crouchingState();
	case DYING:
		dyingState();
		break;
	case FLIPPING:
		flippingState();
		break;
	case ENLARGING: // Enlarging state to large mode
		enlargingState();
		break;
	case FLAGDOWN:
		flagdownState();
		break;
	case THROWFIREBALL:
		throwfireballState();
		break;
	case SLIDING:
		slidingState();
		break;
	default:
		std::cout << "Player state out of bounds" << std::endl;
	}
}

/*
 * TODO
 * Create function to draw the player
 */
void Player::draw() {
	getCurrentSprite().drawSprite(); // Gets the current player sprite and draws it
}
/*
 * TODO
 * Complete player jumping function. Background must handle physics
 */
bool Player::isInAir() {
	return velY != 0;
}
/*
 * TODO
 * Update if more things are added
 *
 */
bool Player::isEnemy(Collider_Id sprite_id) {
	return true;
}
/*
 * TODO
 * Returns true if an enemy hit mario and it wouldnt kill the enemy
 */
bool Player::hitByEnemy() {

}
/*
 *
 * Implement this method to return true if the player gets a mushroom. Mushroom should also disappear when returning true
 */
bool Player::getsMushroom() {
	if (current_background == nullptr) {
		std::cout << "Background is null!" << std::endl;
	}
	Rect_Collider & rect = current_background->itemCollidedWithPlayer();
	if (rect.collide_id == Collider_Id::MUSHROOM) {
		current_background->removeItemByCollider(rect);
		return true;
	}
	return false;
}
/*
 *
 * Implement this method to return true if the player gets a fireflower. Fireflower should disappear when returning true;
 */
bool Player::getsFireflower() {
	if (current_background == nullptr) {
		std::cout << "Background is null!" << std::endl;
	}
	Rect_Collider & rect = current_background->itemCollidedWithPlayer();
	if (rect.collide_id == Collider_Id::FIREFLOWER){
		current_background->removeItemByCollider(rect);
		return true;
	}
	return false;
}

void Player::idleState () {
	return_state = IDLE;
	// Stop movement slowly if in idle state (Mario slides)
	if (velX != 0) {
		if (velX > 0) {
			x -= velX;
			velX -= WALK_ACCEL;
			if (velX < 0) {
				velX = 0;
			}
		}
		if (velX < 0) {
			x += velX;
			velX += WALK_ACCEL;
			if (velX > 0) {
				velX = 0;
			}
		}
	}
	else if (keyboard.key_jump() || isInAir()) {
		current_anim_state = JUMPING;
	}
	else if (keyboard.key_crouch() && current_anim_mode != MINI_MODE) {
		current_anim_state = CROUCHING;
	}
	else if (keyboard.key_right()) {
		if (isFacingLeft)
			current_anim_state = FLIPPING;
		else
			current_anim_state = WALKING;
	}
	else if (keyboard.key_left()) {
		// Must flip in order to go left because sprite faces right
		if (isFacingLeft)
			current_anim_state = WALKING;
		else
			current_anim_state = FLIPPING;
	}
	else if (keyboard.key_fireball() && current_anim_mode == FIRE_MODE) {
		current_anim_state = THROWFIREBALL;
	}
	else if (hitByEnemy() && enemyCanKill) {
		if (current_anim_mode == MINI_MODE) {
			current_anim_state == DYING;
		}
		else if (current_anim_mode == NORMAL_MODE) {
			current_anim_state = SHRINKING;
		}
		else if (current_anim_mode == FIRE_MODE) {
			current_anim_state = SHRINKING;
		}
	}
	else if (getsMushroom() && current_anim_mode == MINI_MODE) {
		current_anim_mode = ENLARGING;
	}
	else if (getsFireflower()) {
		if (current_anim_mode == MINI_MODE) {
			current_anim_state = ENLARGING;
		}
		else if (current_anim_mode == NORMAL_MODE) {
			current_anim_mode = FIRE_MODE;
			wait_frames = FIREFLOWER_NUM_FRAMES;
		}
	}
	else if (keyboard.multipleKeysPressed()) {
		current_anim_state = SLIDING;
	}
}
/*
 * Function for when the player is walking
 */
void Player::walkingState() {
	return_state = WALKING;
	if (keyboard.multipleKeysPressed()) {
		current_anim_state = SLIDING;
	}
	else if (isFacingLeft && keyboard.key_right()) {
		current_anim_state = FLIPPING;
	}
	else if (!isFacingLeft && keyboard.key_left()) {
		current_anim_state = FLIPPING;
	}
	else if (keyboard.key_jump() || isInAir()) {
		current_anim_state = JUMPING;
	}
	else if (keyboard.key_crouch() && current_anim_mode != MINI_MODE) {
		current_anim_state = CROUCHING;
	}
	else if (keyboard.key_crouch() && current_anim_mode == MINI_MODE) {
		current_anim_state = SLIDING;
	}
	else if (keyboard.key_fireball() && current_anim_mode == FIRE_MODE) {
		current_anim_state = THROWFIREBALL;
	}
	else if (hitByEnemy() && enemyCanKill) {
		if (current_anim_mode == MINI_MODE) {
			current_anim_state == DYING;
		}
		else if (current_anim_mode == NORMAL_MODE) {
			current_anim_state = SHRINKING;
		}
		else if (current_anim_mode == FIRE_MODE) {
			current_anim_state = SHRINKING;
		}
	}
	else if (getsMushroom() && current_anim_mode == MINI_MODE) {
		current_anim_mode = ENLARGING;
	}
	else if (getsFireflower()) {
		if (current_anim_mode == MINI_MODE) {
			current_anim_state = ENLARGING;
		}
		else if (current_anim_mode == NORMAL_MODE) {
			current_anim_mode = FIRE_MODE;
			wait_frames = FIREFLOWER_NUM_FRAMES;
		}
	}
	else if (!keyboard.key_left() && !keyboard.key_right()) {
		current_anim_state = IDLE;
	}
	else if (velX < 0 && keyboard.key_left()) {
		if (velX > -MAX_WALK_SPEED) {
			velX -= WALK_ACCEL;
			if (velX < -MAX_WALK_SPEED) {
				velX = -MAX_WALK_SPEED;
			}
		}
		x += velX;
	}
	else if (velX > 0 && keyboard.key_right()) {
		if (velX < MAX_WALK_SPEED) {
			velX += WALK_ACCEL;
			if (velX < MAX_WALK_SPEED) {
				if (velX > MAX_WALK_SPEED) {
					velX = MAX_WALK_SPEED;
				}
			}
		}
		x += velX;
	}
}

/*
 * Function for when the player is midair. Fist up while in this state. If he shrinks or enlarges during this time
 * then he moves to that state, and possibly back afterwards.
 */
void Player::jumpingState() {
	return_state = JUMPING;

	// If you were moving when jumping and hit the ground
	if (!hasJumped) {
		velY = JUMP_VEL;
		hasJumped = true;
	}
	// Determines how mario lands whether he slides or flips first
	else if (!isInAir() && velX != 0) {
		hasJumped = false;
		velY = 0;
		if (velX > 0 && isFacingLeft) current_anim_state = FLIPPING;
		else if (velX > 0 && isFacingLeft) current_anim_state = SLIDING;
		else if (velX < 0 && !isFacingLeft) current_anim_state = FLIPPING;
		else current_anim_state = SLIDING;
	}
	// Allow for slight changes of movement while in midair
	else if (isInAir() && !keyboard.multipleKeysPressed()) {
		if (keyboard.key_left()) {
			velX -= JUMP_MOVE_ACCEL;
			if (velX < -MAX_JUMP_MOVE_SPEED) {
				velX = -MAX_JUMP_MOVE_SPEED;
			}
			x += velX;
		}
		else if (keyboard.key_right()) {
			velX += JUMP_MOVE_ACCEL;
			if (velX > MAX_JUMP_MOVE_SPEED) {
				velX = MAX_JUMP_MOVE_SPEED;
			}
			x += velX;
		}
	}
	else if (keyboard.key_fireball() && current_anim_mode == FIRE_MODE) {
		current_anim_state = THROWFIREBALL;
	}
	else if (hitByEnemy() && enemyCanKill) {
		if (current_anim_mode == MINI_MODE) {
			current_anim_state == DYING;
		}
		else if (current_anim_mode == NORMAL_MODE) {
			current_anim_state = SHRINKING;
		}
		else if (current_anim_mode == FIRE_MODE) {
			current_anim_state = SHRINKING;
		}
	}
	else if (getsMushroom() && current_anim_mode == MINI_MODE) {
		current_anim_mode = ENLARGING;
	}
	else if (getsFireflower()) {
		if (current_anim_mode == MINI_MODE) {
			current_anim_state = ENLARGING;
		}
		else if (current_anim_mode == NORMAL_MODE) {
			current_anim_mode = FIRE_MODE;
			wait_frames = FIREFLOWER_NUM_FRAMES;
		}
	}
}

/*
 * State for when mario is about to shrink. Uses return_state to return to the state it came from when it's done animating
 * Should set invincibility timer
 */
void Player::shrinkingState() {
	current_anim_mode = MINI_MODE;
	current_anim_state = return_state;
	wait_frames = SHRINKING_NUM_FRAMES;
	enemyCanKill = false; // Make mario temporarily invincible for num_frames
	invincibility_frames = INVINCIBILITY_NUM_FRAMES;
}

/*
 * State for when mario is enlarging. Uses return_state to return to the state it came from.
 */
void Player::enlargingState() {
	current_anim_mode = NORMAL_MODE;
	current_anim_state = return_state;
	wait_frames = ENLARGING_NUM_FRAMES;
}

/*
 * State for when the player crouches. Can be only when he is on the ground and not in mini mode
 */
void Player::crouchingState() {
	return_state = CROUCHING;
	velX = 0;
	velY = 0;
	if (!keyboard.key_crouch() || current_anim_state == MINI_MODE) {
		current_anim_mode = IDLE;
	}
	else if (getsMushroom()) {
		// Do nothing, but need to call the method to get rid of the mushroom. Can't become big while crouching cause he already is
	}
	else if (getsFireflower()) {
		current_anim_mode = FIRE_MODE;
		wait_frames = FIREFLOWER_NUM_FRAMES;
	}
	else if (hitByEnemy() && enemyCanKill) {
		if (current_anim_mode == NORMAL_MODE) {
			current_anim_state = SHRINKING;
		}
		else if (current_anim_mode == FIRE_MODE) {
			current_anim_state = SHRINKING;
		}
	}
}

/* TODO
 * Mario drifts at certain times. This state is for while he is drifting
 */
void Player::slidingState() {

}

/*
 * State to play the flipping animation, and change mario's direction
 */
void Player::flippingState() {
	if (velX != 0) {
		current_anim_state = IDLE;
	}
	else if (keyboard.key_left() || keyboard.key_right()) {
		current_anim_state = WALKING;
	}
	else {
		current_anim_state = SLIDING;
	}
	isFacingLeft = !isFacingLeft;
}

/* TODO
 * Called when mario dies by being killed by an enemy
 */
void Player::dyingState() {

}

/* TODO
 * Called when mario throws a fireball. Must be in fire mode obviously
 */
void Player::throwfireballState() {

}

/* TODO
 * Called when mario slides down the flag poll
 */
void Player::flagdownState() {

}
