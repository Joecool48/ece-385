/*
 * enemies.cpp
 *
 *  Created on: Nov 29, 2018
 *      Author: joey
 */
#include "../include/enemies.h"
#include "../include/config.h"

Enemy::Enemy(Background * back) : Sprite_Animator (ENEMY_MODE, ENEMY_STATE, 0) {
	velX = 0;
	velY = 0;
	noCollide = false;
	current_background = back;
	brain = new Brain(current_background, this);
}

Enemy::~Enemy() {
	delete brain;
}

Turtle::Turtle(uint16_t x, uint16_t y, Background * b) : Enemy(b) {
	collider = Rect_Collider (Collider_Type::TURTLE, x, y, TURTLE_COLLIDER_WIDTH, TURTLE_COLLIDER_HEIGHT);
	animatorSetup();
	shell_timer = 0;
	shell_move_right = true;
	current_anim_mode = NORMAL_MODE;
	current_anim_state = WALKING;
}

Gumba::Gumba(uint16_t x, uint16_t y, Background * b) : Enemy(b) {
	collider = Rect_Collider(Collider_Type::GUMBA, x, y, GUMBA_COLLIDER_WIDTH, GUMBA_COLLIDER_HEIGHT);
	animatorSetup();
	current_anim_mode = NORMAL_MODE;
	current_anim_state = WALKING;
}

void Turtle::animatorSetup() {
	Sprite turtle_up(16, 32, ADDRESS_OFFSET + 759585);
	Sprite turtle_walk_1(16, 32, ADDRESS_OFFSET + 761637);
	Sprite turtle_walk_2(16, 32, ADDRESS_OFFSET + 760098);
	Sprite turtle_shell_frame_1(16, 32, ADDRESS_OFFSET + 760611);
	Sprite turtle_dying(16, 32, ADDRESS_OFFSET + 760611);
	state_mode_to_frames_map[WALKING][NORMAL_MODE].push_back(turtle_walk_1);
	state_mode_to_frames_map[WALKING][NORMAL_MODE].push_back(turtle_walk_2);
	state_mode_to_frames_map[SHELL][NORMAL_MODE].push_back(turtle_shell_frame_1);
	state_mode_to_frames_map[SHELL_MOVING][NORMAL_MODE].push_back(turtle_shell_frame_1);
	state_mode_to_frames_map[GET_UP][NORMAL_MODE].push_back(turtle_up);
	state_mode_to_frames_map[DYING_FIREBALL][NORMAL_MODE].push_back(turtle_dying);

}

void Gumba::animatorSetup() {
	Sprite walking_1(16, 32, 762663);
	Sprite walking_2(16, 32, 761124);
	Sprite goomba_die_frame_1 (16, 32, ADDRESS_OFFSET + 762150);
	Sprite goomba_dying (16, 32, ADDRESS_OFFSET + 762150);
	state_mode_to_frames_map[WALKING][NORMAL_MODE].push_back(walking_1);
	state_mode_to_frames_map[WALKING][NORMAL_MODE].push_back(walking_2);
	state_mode_to_frames_map[DYING][NORMAL_MODE].push_back(goomba_die_frame_1);
	state_mode_to_frames_map[DYING_FIREBALL][NORMAL_MODE].push_back(goomba_dying);
}

void Gumba::collided_with(Rect_Collider & other) {
	if (other.collide_type == Collider_Type::PLATFORM_UNBREAKABLE) {
		last_collided = other;
	}
	else if ((other.collide_type == Collider_Type::PLAYER && other.collides_above(collider)) || other.collide_type == Collider_Type::TURTLE_SHELL) {
		current_anim_state = DYING;
	}
	else if (other.collide_type == Collider_Type::FIREBALL) {
		current_anim_state = DYING_FIREBALL;
	}
}
void Turtle::collided_with(Rect_Collider & other) {
	if ((other.collide_type == Collider_Type::PLATFORM_UNBREAKABLE && !collider.collides_above(other) && getState() == SHELL_MOVING)) {
		shell_move_right = !shell_move_right;
		last_collided = other;
	}
	else if (other.collide_type == Collider_Type::PLATFORM_UNBREAKABLE) {
		last_collided = other;
	}
	else if ((other.collide_type == Collider_Type::PLAYER && other.collides_above(collider)) && getState() == WALKING) {
		// Set the timer for the turtle to get up
		shell_timer = REMAIN_IN_SHELL_FRAMES;
		current_anim_state = SHELL;
	}
	else if ((other.collide_type == Collider_Type::PLAYER && other.collides_above(collider)) && getState() == SHELL) {
		// If collides to the left, then the turtle should move right, else left
		shell_move_right = other.collides_left(collider);
		current_anim_state = SHELL_MOVING;
	}
	else if ((other.collide_type == Collider_Type::PLAYER && other.collides_above(collider)) && getState() == SHELL_MOVING) {
		current_anim_state = SHELL;
	}
	else if (other.collide_type == Collider_Type::FIREBALL) { // Can also die from falling off the cliff. Objects automatically cleared that fall out the map
		current_anim_state = DYING_FIREBALL;
	}
}

void Enemy::destroyInBackground() {
	if (current_background == nullptr || current_background->enemies.find(collider.collider_id) == current_background->enemies.end()) {
		std::cout << "Problem finding the Enemy to destroy" << std::endl;
		return;
	}
	delete current_background->enemies[collider.collider_id];
	current_background->enemies.erase(collider.collider_id);
}

/*
 * TODO
 * Implement Gumba state machine
 * Only one mode
 */
void Gumba::update() {
	current_anim_mode = NORMAL_MODE;
	if (wait_frames) {
		wait_frames--;
		return;
	}
	switch (current_anim_state) {
	case WALKING:
		brain->makeDecision();
		// TODO
		// AI Makes some decision
		break;
	case DYING:
		wait_frames = DIE_FRAMES;
		current_anim_state = DESTROY;
		break;
	case DYING_FIREBALL:
		// Impliment the death by fireball animation
		noCollide = true;
		flipped_mode = FLIP_VERTICAL;
		break;
	case DESTROY:
		destroyInBackground();
		break;
	}
}

/*
 * TODO
 * Implement Turtle state machine
 * Only one mode
 * WALKING, SHELL, SHELL_MOVING, GET_UP, DYING_FIREBALL, DESTROY
 */
void Turtle::update() {
	current_anim_mode = NORMAL_MODE;
	if (wait_frames) {
		wait_frames--;
		return;
	}
	switch (current_anim_state) {
	case WALKING:
		brain->makeDecision();
		// TODO
		// AI makes a decision
		break;
	case SHELL:
		velX = 0;
		if (shell_timer) {
			shell_timer--;
		}
		else {
			current_anim_state = GET_UP;
		}
		break;
	case GET_UP:
		velX = 0;
		wait_frames = 3;
		current_anim_state = WALKING;
		break;
	case SHELL_MOVING:
		velX = shell_move_right ? SHELL_MOVE_SPEED : -SHELL_MOVE_SPEED;
		break;
	case DYING_FIREBALL:
		// TODO
		// Get dying animation sorted out
		noCollide = true;
		flipped_mode = FLIP_VERTICAL;
		break;
	case DESTROY:
		destroyInBackground();
	}
}


void Enemy::gravity() {
	collider.collide_y += velY;
	collider.collide_x += velX;
	velY += GRAVITY_STRENGTH;
}

void Enemy::draw() {
	Sprite s = getCurrentSprite();
	// Update the rect collider!!!s
	collider.collide_width = s.width;
	collider.collide_height = s.height;
	s.drawSprite(collider.collide_x, collider.collide_y, flipped_mode ? FLIP_HORIZONTAL : NO_FLIP, isVisible); // Gets the current sprite and draws
}
