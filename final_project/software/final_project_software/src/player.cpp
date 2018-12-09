/*
 * player.cpp
 *
 *  Created on: Nov 30, 2018
 *      Author: joey
 */
#include "../include/player.h"
#include "../include/keyboard.h"
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
	std::cout << "Creating fireball" << std::endl;
	Fireball *fireball = nullptr;
	if (flipped_mode) { // If flipped horizontally, throw the fireball on his left side
		fireball = new Fireball(player_collider.collide_x - FIREBALL_X_DIST_FROM_MARIO, player_collider.collide_y + FIREBALL_Y_DIST_FROM_MARIO, current_background);
	}
	else {
		// Otherwise is facing right direction
		fireball = new Fireball(player_collider.collide_x + player_collider.collide_width + FIREBALL_X_DIST_FROM_MARIO, player_collider.collide_y + FIREBALL_Y_DIST_FROM_MARIO, current_background);
	}
	// Add the fireball to the background
	current_background->fireballs[fireball->collider.collider_id] = fireball;
}
/*
 * Constructs a new player object (Mario). This also calls animatorSetup to make sure all the sprites are filled. Always starts in normal mode and idle state
 * Also inits the rect collider, initial mode, and state.
 */
Player::Player(uint16_t x, uint16_t y) : Sprite_Animator (NORMAL_MODE, IDLE, 0) {
	enablePlayerControl = true;
	enemyCanKill = true;
	player_collider = Rect_Collider(Collider_Type::PLAYER, x, y, PLAYER_COLLIDER_WIDTH, PLAYER_COLLIDER_HEIGHT);
	accelX = 0, accelY = 0;
	velX = 0, velY = 0;
	invincibility_frames = 0;
	flipped_mode = NO_FLIP;
	hasJumped = false;
	return_state = IDLE;
	current_background = nullptr;
	gotMushroom = false;
	gotFireflower = false;
	gotHitByEnemy = false;
	noCollide = false;
	inAir = true;
	animatorSetup();
}
/*
 * Maps all the states and modes to their respective series of sprite frames
 */
void Player::animatorSetup() {
	Sprite sprite9 (16, 32, ADDRESS_OFFSET + 775801);
	Sprite sprite13 (16, 32, ADDRESS_OFFSET + 776314);
	Sprite sprite17 (16, 32, ADDRESS_OFFSET + 776827);
	Sprite sprite21 (16, 32, ADDRESS_OFFSET + 777340);
	Sprite sprite2 (16, 32, ADDRESS_OFFSET + 777853);
	Sprite sprite19 (16, 32, ADDRESS_OFFSET + 778366);
	Sprite sprite7 (16, 32, ADDRESS_OFFSET + 778879);
	Sprite sprite12 (16, 32, ADDRESS_OFFSET + 779392);
	Sprite sprite4 (16, 32, ADDRESS_OFFSET + 779905);
	Sprite sprite3 (16, 32, ADDRESS_OFFSET + 780418);
	Sprite sprite1 (16, 32, ADDRESS_OFFSET + 780931);
	Sprite sprite16 (16, 32, ADDRESS_OFFSET + 781444);
	Sprite sprite11 (16, 32, ADDRESS_OFFSET + 781957);
	Sprite sprite14 (16, 32, ADDRESS_OFFSET + 782470);
	Sprite sprite5 (16, 32, ADDRESS_OFFSET + 782983);
	Sprite sprite8 (16, 32, ADDRESS_OFFSET + 783496);
	Sprite sprite20 (16, 32, ADDRESS_OFFSET + 784009);
	Sprite sprite6 (16, 32, ADDRESS_OFFSET + 784522);
	Sprite sprite15 (16, 32, ADDRESS_OFFSET + 785035);
	Sprite sprite18 (16, 32, ADDRESS_OFFSET + 785548);
	Sprite sprite10 (16, 32, ADDRESS_OFFSET + 786061);
	Sprite fire_mario21 (16, 31, ADDRESS_OFFSET + 763176);
	Sprite fire_mario3 (16, 31, ADDRESS_OFFSET + 763673);
	Sprite fire_mario13 (16, 31, ADDRESS_OFFSET + 764170);
	Sprite fire_mario4 (16, 31, ADDRESS_OFFSET + 764667);
	Sprite fire_mario10 (16, 31, ADDRESS_OFFSET + 765164);
	Sprite fire_mario2 (16, 31, ADDRESS_OFFSET + 765661);
	Sprite fire_mario17 (16, 31, ADDRESS_OFFSET + 766158);
	Sprite fire_mario1 (16, 31, ADDRESS_OFFSET + 766655);
	Sprite fire_mario5 (16, 31, ADDRESS_OFFSET + 767152);
	Sprite fire_mario12 (16, 31, ADDRESS_OFFSET + 767649);
	Sprite fire_mario20 (16, 31, ADDRESS_OFFSET + 768146);
	Sprite fire_mario19 (16, 31, ADDRESS_OFFSET + 768643);
	Sprite fire_mario8 (16, 31, ADDRESS_OFFSET + 769140);
	Sprite fire_mario18 (16, 31, ADDRESS_OFFSET + 769637);
	Sprite fire_mario6 (16, 31, ADDRESS_OFFSET + 770134);
	Sprite fire_mario9 (16, 31, ADDRESS_OFFSET + 770631);
	Sprite fire_mario11 (16, 31, ADDRESS_OFFSET + 771128);
	Sprite fire_mario14 (16, 31, ADDRESS_OFFSET + 771625);
	Sprite fire_mario15 (16, 31, ADDRESS_OFFSET + 772122);
	Sprite fire_mario16 (16, 31, ADDRESS_OFFSET + 772619);
	Sprite fire_mario7 (16, 31, ADDRESS_OFFSET + 773116);
	Sprite mini_mario13 (16, 16, ADDRESS_OFFSET + 786574);
	Sprite mini_mario7 (16, 16, ADDRESS_OFFSET + 786831);
	Sprite mini_mario12 (16, 16, ADDRESS_OFFSET + 787088);
	Sprite mini_mario8 (16, 16, ADDRESS_OFFSET + 787345);
	Sprite mini_mario14 (16, 16, ADDRESS_OFFSET + 787602);
	Sprite mini_mario1 (16, 16, ADDRESS_OFFSET + 787859);
	Sprite mini_mario9 (16, 16, ADDRESS_OFFSET + 788116);
	Sprite mini_mario4 (16, 16, ADDRESS_OFFSET + 788373);
	Sprite mini_mario5 (16, 16, ADDRESS_OFFSET + 788630);
	Sprite mini_mario6 (16, 16, ADDRESS_OFFSET + 788887);
	Sprite mini_mario3 (16, 16, ADDRESS_OFFSET + 789144);
	Sprite mini_mario2 (16, 16, ADDRESS_OFFSET + 789401);
	Sprite mini_mario10 (16, 16, ADDRESS_OFFSET + 789658);
	Sprite mini_mario11 (16, 16, ADDRESS_OFFSET + 789915);
	// Init normal mario sprites
	state_mode_to_frames_map[IDLE][NORMAL_MODE].push_back(sprite1);
	state_mode_to_frames_map[WALKING][NORMAL_MODE].push_back(sprite2);
	state_mode_to_frames_map[WALKING][NORMAL_MODE].push_back(sprite3);
	state_mode_to_frames_map[WALKING][NORMAL_MODE].push_back(sprite4);
	state_mode_to_frames_map[FLIPPING][NORMAL_MODE].push_back(sprite5);
	state_mode_to_frames_map[JUMPING][NORMAL_MODE].push_back(sprite6);
	state_mode_to_frames_map[CROUCHING][NORMAL_MODE].push_back(sprite7);
	// Init mini-mario sprites
	state_mode_to_frames_map[IDLE][MINI_MODE].push_back(mini_mario1);
	state_mode_to_frames_map[WALKING][MINI_MODE].push_back(mini_mario2);
	state_mode_to_frames_map[WALKING][MINI_MODE].push_back(mini_mario3);
	state_mode_to_frames_map[WALKING][MINI_MODE].push_back(mini_mario4);
	state_mode_to_frames_map[FLIPPING][MINI_MODE].push_back(mini_mario5);
	state_mode_to_frames_map[JUMPING][MINI_MODE].push_back(mini_mario6);
	state_mode_to_frames_map[DYING][MINI_MODE].push_back(mini_mario7);
	// Init fire-mario sprites
	state_mode_to_frames_map[IDLE][FIRE_MODE].push_back(fire_mario1);
	state_mode_to_frames_map[WALKING][FIRE_MODE].push_back(mini_mario2);
	state_mode_to_frames_map[WALKING][FIRE_MODE].push_back(mini_mario3);
	state_mode_to_frames_map[WALKING][FIRE_MODE].push_back(mini_mario4);
	state_mode_to_frames_map[FLIPPING][FIRE_MODE].push_back(mini_mario5);
	state_mode_to_frames_map[JUMPING][FIRE_MODE].push_back(mini_mario6);
	state_mode_to_frames_map[CROUCHING][FIRE_MODE].push_back(mini_mario7);

}

/*
 *
 * Player state machine
 */
void Player::update() {
	std::cout << "Current player state is " << current_anim_state << std::endl;
	std::cout << "Player velx = " << velX << std::endl;
	std::cout << "Player vely = " << velY << std::endl;
	std::cout << "Keys pressed " << Keyboard::keys_pressed() << std::endl;
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
		setFrame(0);
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
		break;
	case DYING:
		dyingState();
		break;
	case FLIPPING:
		flippingState();
		break;
	case ENLARGING: // Enlarging state to large mode
		enlargingState();
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
	std::cout << "Start draw Player" << std::endl;
	// Choose whether to flip the sprite based on private variable
	Sprite s = getCurrentSprite();
	std::cout << "After get current" << std::endl;
	// Update the rect collider!!!
	//player_collider.collide_x = static_cast<int16_t>(x); // Convert the floats to ints
	//player_collider.collide_y = static_cast<int16_t> (y);

	player_collider.collide_width = s.width;
	player_collider.collide_height = s.height;
	std::cout << "Before static cast" << std::endl;
	std::cout << player_collider.collide_x << " " << player_collider.collide_y << std::endl;
	s.drawSprite(static_cast<int16_t>(player_collider.collide_x), static_cast<int16_t> (player_collider.collide_y), flipped_mode ? FLIP_HORIZONTAL : NO_FLIP, isVisible); // Gets the current player sprite and draws it
	std::cout << "After draw player" << std::endl;
}
/*
 * TODO Might be BUGGED
 * Complete player jumping function. Background must handle physics
 */
bool Player::isInAir() {
	// Allow for one frame of misalign
	if (inAir || (abs(velY) > GRAVITY_STRENGTH)) return true;
	else inAir = false;
	return false;
}

/*
 *
 * Returns true if an enemy hit mario and it wouldnt kill the enemy
 */
bool Player::hitByEnemy() {
	if (gotHitByEnemy) {
		gotHitByEnemy = false;
		return true;
	}
	return false;
}
/* TODO maybe implement
 * Called if something collides with the player
 *
 */
void Player::collided_with(Rect_Collider & other) {
	if (other.collide_type == Collider_Type::MUSHROOM) {
		gotMushroom = true;
	}
	else if (other.collide_type == Collider_Type::FIREFLOWER) {
		gotFireflower = true;
	}
	else if (Collidable::isEnemy(other.collide_type) && !player_collider.collides_above(other)) {
		gotHitByEnemy = true;
	}
	else if (Collidable::isEnemy(other.collide_type) && player_collider.collides_above(other)) {
		velY -= PLAYER_JUMP_ON_ENEMY_BOOST;
		current_anim_state = JUMPING; // They are technically in the air now
	}
	else if (other.collide_type == Collider_Type::PLATFORM_UNBREAKABLE) {
		inAir = false;
	}
}

/*
 *
 * Implement this method to return true if the player gets a mushroom. Mushroom should also disappear when returning true
 */
bool Player::getsMushroom() {
	if (gotMushroom) {
		gotMushroom = false;
		return true;
	}
	return false;
}
/*
 *
 * Implement this method to return true if the player gets a fireflower. Fireflower should disappear when returning true;
 */
bool Player::getsFireflower() {
	if (gotFireflower) {
		gotFireflower = false;
		return true;
	}
	return false;
}

void Player::idleState () {
	return_state = IDLE;
	// Stop movement slowly if in idle state (Mario slides)
	if (velX != 0) {
		if (velX > 0) {
			player_collider.collide_x -= velX;
			velX -= WALK_ACCEL;
			if (velX < 0) {
				velX = 0;
			}
		}
		if (velX < 0) {
			player_collider.collide_x += velX;
			velX += WALK_ACCEL;
			if (velX > 0) {
				velX = 0;
			}
		}
	}
	else if (Keyboard::key_jump(enablePlayerControl)) {
		current_anim_state = JUMPING;
	}
	else if (Keyboard::key_crouch(enablePlayerControl) && current_anim_mode != MINI_MODE && !isInAir()) {
		current_anim_state = CROUCHING;
	}
	else if (Keyboard::key_right(enablePlayerControl)) {
		if (flipped_mode)
			current_anim_state = FLIPPING;
		else
			current_anim_state = WALKING;
	}
	else if (Keyboard::key_left(enablePlayerControl)) {
		// Must flip in order to go left because sprite faces right
		if (flipped_mode)
			current_anim_state = WALKING;
		else
			current_anim_state = FLIPPING;
	}
	else if (Keyboard::key_fireball(enablePlayerControl) && current_anim_mode == FIRE_MODE) {
		std::cout << "Throwing fire" << std::endl;
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
	else if (Keyboard::multipleKeysPressed()) {
		current_anim_state = SLIDING;
	}
}
/*
 * Function for when the player is walking
 */
void Player::walkingState() {
	return_state = WALKING;

	if (Keyboard::multipleKeysPressed()) {
		current_anim_state = SLIDING;
	}
	else if (flipped_mode && Keyboard::key_right(enablePlayerControl)) {
		current_anim_state = FLIPPING;
	}
	else if (!flipped_mode && Keyboard::key_left(enablePlayerControl)) {
		current_anim_state = FLIPPING;
	}
	else if (Keyboard::key_jump(enablePlayerControl)) {
		current_anim_state = JUMPING;
	}
	else if (Keyboard::key_crouch(enablePlayerControl) && current_anim_mode != MINI_MODE) {
		current_anim_state = CROUCHING;
	}
	else if (Keyboard::key_crouch(enablePlayerControl) && current_anim_mode == MINI_MODE) {
		current_anim_state = SLIDING;
	}
	else if (Keyboard::key_fireball(enablePlayerControl) && current_anim_mode == FIRE_MODE) {
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
	else if (!Keyboard::key_left(enablePlayerControl) && !Keyboard::key_right(enablePlayerControl)) {
		current_anim_state = IDLE;
	}
	else if (velX == 0) {
		if (Keyboard::key_left(enablePlayerControl)) {
			if (velX > -MAX_WALK_SPEED) {
				velX -= WALK_ACCEL;
				if (velX < -MAX_WALK_SPEED) {
					velX = -MAX_WALK_SPEED;
				}
			}
			player_collider.collide_x += velX;
		}
		else if (Keyboard::key_right(enablePlayerControl)) {
			if (velX < MAX_WALK_SPEED) {
				velX += WALK_ACCEL;
				if (velX < MAX_WALK_SPEED) {
					if (velX > MAX_WALK_SPEED) {
						velX = MAX_WALK_SPEED;
					}
				}
			}
			player_collider.collide_x += velX;
		}
	}
	else if (velX < 0 && Keyboard::key_left(enablePlayerControl)) {
		if (velX > -MAX_WALK_SPEED) {
			velX -= WALK_ACCEL;
			if (velX < -MAX_WALK_SPEED) {
				velX = -MAX_WALK_SPEED;
			}
		}
		player_collider.collide_x += velX;
	}
	else if (velX > 0 && Keyboard::key_right(enablePlayerControl)) {
		if (velX < MAX_WALK_SPEED) {
			velX += WALK_ACCEL;
			if (velX < MAX_WALK_SPEED) {
				if (velX > MAX_WALK_SPEED) {
					velX = MAX_WALK_SPEED;
				}
			}
		}
		player_collider.collide_x += velX;
	}
}

/*
 * Function for when the player is midair. Fist up while in this state. If he shrinks or enlarges during this time
 * then he moves to that state, and possibly back afterwards.
 */
void Player::jumpingState() {
	return_state = JUMPING;
	std::cout << "In jumping state and vely = " << velY << std::endl;
	// If you were moving when jumping and hit the ground
	std::cout << "IsInAir = " << isInAir() << std::endl;
	if (!hasJumped && !isInAir() && Keyboard::key_jump(enablePlayerControl)) {
		velY = -JUMP_VEL;
		hasJumped = true;
	}
	// Determines how mario lands whether he slides or flips first
	else if (!isInAir() && velX != 0) {
		hasJumped = false;
		velY = 0;
		if (velX > 0 && flipped_mode) current_anim_state = FLIPPING;
		else if (velX > 0 && flipped_mode) current_anim_state = SLIDING;
		else if (velX < 0 && !flipped_mode) current_anim_state = FLIPPING;
		else current_anim_state = SLIDING;
	}
	else if (!isInAir()) {
		hasJumped = false;
		current_anim_state = IDLE;
	}
	// Allow for slight changes of movement while in midair
	else if (isInAir() && !Keyboard::multipleKeysPressed()) {
		if (Keyboard::key_left(enablePlayerControl)) {
			velX -= JUMP_MOVE_ACCEL;
			if (velX < -MAX_JUMP_MOVE_SPEED) {
				velX = -MAX_JUMP_MOVE_SPEED;
			}
			player_collider.collide_x += velX;
		}
		else if (Keyboard::key_right(enablePlayerControl)) {
			velX += JUMP_MOVE_ACCEL;
			if (velX > MAX_JUMP_MOVE_SPEED) {
				velX = MAX_JUMP_MOVE_SPEED;
			}
			player_collider.collide_x += velX;
		}
	}
	else if (Keyboard::key_fireball(enablePlayerControl) && current_anim_mode == FIRE_MODE) {
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
	std::cout << "In crouching" << std::endl;
	return_state = CROUCHING;
	velX = 0;
	velY = 0;
	if (!Keyboard::key_crouch(enablePlayerControl) || current_anim_mode == MINI_MODE) {
		current_anim_state = IDLE;
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
	else if (Keyboard::key_left(enablePlayerControl) || Keyboard::key_right(enablePlayerControl)) {
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
	else if (Keyboard::key_left(enablePlayerControl) || Keyboard::key_right(enablePlayerControl)) {
		current_anim_state = WALKING;
	}
	else {
		current_anim_state = SLIDING;
	}
	flipped_mode = flipped_mode ? NO_FLIP : FLIP_HORIZONTAL;
}

/* TODO
 * Called when mario dies by being killed by an enemy
 */
void Player::dyingState() {
	noCollide = true; // Make him fall through the world and display his dying frame when he is small
	enablePlayerControl = false;
	std::cout << "Game over" << std::endl;
}

/*
 * Called when mario throws a fireball. Must be in fire mode obviously
 */
void Player::throwfireballState() {
	throwFireball(); // Should check all the conditions for us
	current_anim_state = return_state;
}

///*
// * Called when mario slides down the flag poll
// */
//void Player::flagdownState() {
//
//}

void Player::gravity() {
	player_collider.collide_x += velX;
	player_collider.collide_y += velY;
	velY += GRAVITY_STRENGTH;
}


