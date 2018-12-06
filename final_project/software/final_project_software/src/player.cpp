/*
 * player.cpp
 *
 *  Created on: Nov 30, 2018
 *      Author: joey
 */
#include "player.h"
#include <iostream>
#include "config.h"
#include "item.h"
#include "sprite.h"
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
 * Function to create a fireball and give it a initial velocity at that position. Only does so if mario is in fire mode,
 * and there are less than the max fireballs out. Adds the fireball to the background vector
 */
void Player::throwFireball() {
	if (current_background == nullptr) {
		std::cout << "throwFireball: Background is null" << std::endl;
		return;
	}
	if (current_anim_mode != modes::FIRE_MODE) {
		std::cout << "throwFireball: Mario is not in fire mode" << std::endl;
		return;
	}
	if (current_background->fireballs.size() >= MAX_FIREBALLS_IN_EXISTANCE) {
		std::cout << "throwFireball: no more fire balls allowed" << std::endl;
		return;
	}
	Fireball *fireball = nullptr;
	if (isFacingLeft) {
		fireball = new Fireball(x - FIREBALL_X_DIST_FROM_MARIO, y + FIREBALL_Y_DIST_FROM_MARIO, current_background);
	}
	else {
		// Otherwise is facing right direction
		fireball = new Fireball(x + player_collider.collide_width + FIREBALL_X_DIST_FROM_MARIO, y + FIREBALL_Y_DIST_FROM_MARIO, current_background);
	}
	// Add the fireball to the background
	current_background->fireballs[fireball->collider.collider_id] = fireball;
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
	Sprite sprite9 (0, 0, 16, 32, ADDRESS_OFFSET + 775801);
	Sprite sprite13 (0, 0, 16, 32, ADDRESS_OFFSET + 776314);
	Sprite sprite17 (0, 0, 16, 32, ADDRESS_OFFSET + 776827);
	Sprite sprite21 (0, 0, 16, 32, ADDRESS_OFFSET + 777340);
	Sprite sprite2 (0, 0, 16, 32, ADDRESS_OFFSET + 777853);
	Sprite sprite19 (0, 0, 16, 32, ADDRESS_OFFSET + 778366);
	Sprite sprite7 (0, 0, 16, 32, ADDRESS_OFFSET + 778879);
	Sprite sprite12 (0, 0, 16, 32, ADDRESS_OFFSET + 779392);
	Sprite sprite4 (0, 0, 16, 32, ADDRESS_OFFSET + 779905);
	Sprite sprite3 (0, 0, 16, 32, ADDRESS_OFFSET + 780418);
	Sprite sprite1 (0, 0, 16, 32, ADDRESS_OFFSET + 780931);
	Sprite sprite16 (0, 0, 16, 32, ADDRESS_OFFSET + 781444);
	Sprite sprite11 (0, 0, 16, 32, ADDRESS_OFFSET + 781957);
	Sprite sprite14 (0, 0, 16, 32, ADDRESS_OFFSET + 782470);
	Sprite sprite5 (0, 0, 16, 32, ADDRESS_OFFSET + 782983);
	Sprite sprite8 (0, 0, 16, 32, ADDRESS_OFFSET + 783496);
	Sprite sprite20 (0, 0, 16, 32, ADDRESS_OFFSET + 784009);
	Sprite sprite6 (0, 0, 16, 32, ADDRESS_OFFSET + 784522);
	Sprite sprite15 (0, 0, 16, 32, ADDRESS_OFFSET + 785035);
	Sprite sprite18 (0, 0, 16, 32, ADDRESS_OFFSET + 785548);
	Sprite sprite10 (0, 0, 16, 32, ADDRESS_OFFSET + 786061);
	Sprite fire_mario21 (0, 0, 16, 31, ADDRESS_OFFSET + 763176);
	Sprite fire_mario3 (0, 0, 16, 31, ADDRESS_OFFSET + 763673);
	Sprite fire_mario13 (0, 0, 16, 31, ADDRESS_OFFSET + 764170);
	Sprite fire_mario4 (0, 0, 16, 31, ADDRESS_OFFSET + 764667);
	Sprite fire_mario10 (0, 0, 16, 31, ADDRESS_OFFSET + 765164);
	Sprite fire_mario2 (0, 0, 16, 31, ADDRESS_OFFSET + 765661);
	Sprite fire_mario17 (0, 0, 16, 31, ADDRESS_OFFSET + 766158);
	Sprite fire_mario1 (0, 0, 16, 31, ADDRESS_OFFSET + 766655);
	Sprite fire_mario5 (0, 0, 16, 31, ADDRESS_OFFSET + 767152);
	Sprite fire_mario12 (0, 0, 16, 31, ADDRESS_OFFSET + 767649);
	Sprite fire_mario20 (0, 0, 16, 31, ADDRESS_OFFSET + 768146);
	Sprite fire_mario19 (0, 0, 16, 31, ADDRESS_OFFSET + 768643);
	Sprite fire_mario8 (0, 0, 16, 31, ADDRESS_OFFSET + 769140);
	Sprite fire_mario18 (0, 0, 16, 31, ADDRESS_OFFSET + 769637);
	Sprite fire_mario6 (0, 0, 16, 31, ADDRESS_OFFSET + 770134);
	Sprite fire_mario9 (0, 0, 16, 31, ADDRESS_OFFSET + 770631);
	Sprite fire_mario11 (0, 0, 16, 31, ADDRESS_OFFSET + 771128);
	Sprite fire_mario14 (0, 0, 16, 31, ADDRESS_OFFSET + 771625);
	Sprite fire_mario15 (0, 0, 16, 31, ADDRESS_OFFSET + 772122);
	Sprite fire_mario16 (0, 0, 16, 31, ADDRESS_OFFSET + 772619);
	Sprite fire_mario7 (0, 0, 16, 31, ADDRESS_OFFSET + 773116);
	Sprite mini_mario13 (0, 0, 16, 16, ADDRESS_OFFSET + 786574);
	Sprite mini_mario7 (0, 0, 16, 16, ADDRESS_OFFSET + 786831);
	Sprite mini_mario12 (0, 0, 16, 16, ADDRESS_OFFSET + 787088);
	Sprite mini_mario8 (0, 0, 16, 16, ADDRESS_OFFSET + 787345);
	Sprite mini_mario14 (0, 0, 16, 16, ADDRESS_OFFSET + 787602);
	Sprite mini_mario1 (0, 0, 16, 16, ADDRESS_OFFSET + 787859);
	Sprite mini_mario9 (0, 0, 16, 16, ADDRESS_OFFSET + 788116);
	Sprite mini_mario4 (0, 0, 16, 16, ADDRESS_OFFSET + 788373);
	Sprite mini_mario5 (0, 0, 16, 16, ADDRESS_OFFSET + 788630);
	Sprite mini_mario6 (0, 0, 16, 16, ADDRESS_OFFSET + 788887);
	Sprite mini_mario3 (0, 0, 16, 16, ADDRESS_OFFSET + 789144);
	Sprite mini_mario2 (0, 0, 16, 16, ADDRESS_OFFSET + 789401);
	Sprite mini_mario10 (0, 0, 16, 16, ADDRESS_OFFSET + 789658);
	Sprite mini_mario11 (0, 0, 16, 16, ADDRESS_OFFSET + 789915);
	// Init normal mario sprites
	state_mode_to_frames_map[IDLE][NORMAL_MODE].push_back(sprite1);
	state_mode_to_frames_map[WALKING][NORMAL_MODE].push_back(sprite2);
	state_mode_to_frames_map[WALKING][NORMAL_MODE].push_back(sprite3);
	state_mode_to_frames_map[WALKING][NORMAL_MODE].push_back(sprite4);
	state_mode_to_frames_map[FLIPPING][NORMAL_MODE].push_back(sprite5);
	state_mode_to_frames_map[JUMPING][NORMAL_MODE].push_back(sprite6);
	state_mode_to_frames_map[CROUCHING][NORMAL_MODE].push_back(sprite7);
	// Init mini-mario sprites
	state_mode_to_frames_map[IDLE][MINI_MODE].push_back(sprite1);
	state_mode_to_frames_map[WALKING][MINI_MODE].push_back(sprite2);
	state_mode_to_frames_map[WALKING][MINI_MODE].push_back(sprite3);
	state_mode_to_frames_map[WALKING][MINI_MODE].push_back(sprite4);
	state_mode_to_frames_map[FLIPPING][MINI_MODE].push_back(sprite5);
	state_mode_to_frames_map[JUMPING][MINI_MODE].push_back(sprite6);
	state_mode_to_frames_map[CROUCHING][MINI_MODE].push_back(sprite7);
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
		isVisible = ~isVisible; // Small animation to blink mario while invincible TODO may need fixing here
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
 *
 * Create function to draw the player
 */
void Player::draw() {
	getCurrentSprite().drawSprite(); // Gets the current player sprite and draws it
}
/*
 * TODO Might be BUGGED
 * Complete player jumping function. Background must handle physics
 */
bool Player::isInAir() {
	return velY != 0;
}

/*
 *
 * Returns true if an enemy hit mario and it wouldnt kill the enemy
 */
bool Player::hitByEnemy() {
	if (current_background == nullptr) {
		std::cout << "Background is null!" << std::endl;
		return false;
	}
	for (int i = 0; i < current_background->enemies.size(); i++) {
		if (current_background->enemies[i] != nullptr) {
			// Mario got hit by an enemy, and didnt land on top of it.
			// He takes damage when this happens
			if (current_background->enemies[i]->collider.collides_with(player_collider) && !player_collider.collides_above(current_background->enemies[i]->collider)) {
				return true;
			}
		}
	}
	return false;
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
	if (rect.collider_type == Collider_Type::MUSHROOM) {
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
	if (rect.collider_type == Collider_Type::FIREFLOWER){
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

/*
 * Mario drifts at certain times. This state is for while he is drifting
 */
void Player::slidingState() {
	return_state = SLIDING;
	if (velX < 0) {
		velX += SLIDING_SPEED_SLOW;
		if (velX > 0) velX = 0;
	}
	else if (velX > 0) {
		velX -= SLIDING_SPEED_SLOW;
		if (velX < 0) velX = 0;
	}
	if (velX == 0) {
		current_anim_state = IDLE;
	}
	else if (keyboard.key_left() || keyboard.key_right()) {
		current_anim_state = WALKING;
	}
}

/*
 * State to play the flipping animation, and change mario's direction
 */
void Player::flippingState() {
	return_state = FLIPPING;
	if (velX == 0) {
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
	std::cout << "You dead" << std::endl;
}

/*
 * Called when mario throws a fireball. Must be in fire mode obviously
 */
void Player::throwfireballState() {
	throwFireball(); // Should check all the conditions for us
	current_anim_state = return_state;
}

/* TODO
 * Called when mario slides down the flag poll
 */
void Player::flagdownState() {

}
