/*
 * enemies.cpp
 *
 *  Created on: Nov 29, 2018
 *      Author: joey
 */
#include "enemies.h"
#include "config.h"

Enemy::Enemy() {
	velX = 0;
	velY = 0;
	noCollide = false;
	current_background = nullptr;
}

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

void Gumba::collided_with(Rect_Collider & other) {
	if ((other.collider_type == Collider_Type::PLAYER && other.collides_above(collider)) || other.collider_type == Collider_Type::TURTLE_SHELL) {
		current_anim_state = DYING;
	}
	else if (other.collider_type == Collider_Type::FIREBALL) {
		current_anim_state = DYING_FIREBALL;
	}
}
void Turtle::collided_with(Rect_Collider & other) {
	if ((other.collider_type == Collider_Type::PLATFORM_UNBREAKABLE && collider.collides_above(other) && current_anim_state == SHELL_MOVING)) {
		shell_move_right = !shell_move_right;
	}
	else if ((other.collider_type == Collider_Type::PLAYER && other.collides_above(collider)) && current_anim_state == WALKING) {
		// Set the timer for the turtle to get up
		shell_timer = REMAIN_IN_SHELL_FRAMES;
		current_anim_state = SHELL;
	}
	else if ((other.collider_type == Collider_Type::PLAYER && other.collides_above(collider)) && current_anim_state == SHELL) {
		// If collides to the left, then the turtle should move right, else left
		shell_move_right = other.collides_left(collider);
		current_anim_state = SHELL_MOVING;
	}
	else if ((other.collider_type == Collider_Type::PLAYER && other.collides_above(collider)) && current_anim_state == SHELL_MOVING) {
		current_anim_state = SHELL;
	}
	else if (other.collider_type == Collider_Type::FIREBALL) {
		current_anim_state = DYING_FIREBALL;
	}
}

void Enemy::destroyInBackground() {
	if (current_background == nullptr || current_background->enemies.find(collider.collider_id) == current_background->enemies.end()) {
		std::cout << "Problem finding the Item to destroy" << std::endl;
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
		break;
	case DESTROY:
		destroyInBackground();
	}
}


void Enemy::gravity() {
	velY += GRAVITY_STRENGTH;
}


