/*
 * item.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: joey
 */
#include "item.h"
#include <stdlib.h>
#include "colliders.h"
#include "sprite_animator.h"
#include "config.h"
#include "background.h"
Item::Item (uint16_t start_x, uint16_t start_y, Rect_Collider rect) : Sprite_Animator (start_x, start_y, Item::ITEM_MODE, Item::ITEM_STATE, Item::ITEM_START_FRAME), Item::collider(Rect_Collider(rect)){
	current_background = nullptr;
}
Fireflower::Fireflower (uint16_t start_x, uint16_t start_y) : Sprite_Animator (start_x, start_y, Item::ITEM_MODE, Item::ITEM_STATE, Item::ITEM_START_FRAME), Item::collider(Rect_Collider(start_x, start_y, FIREFLOWER_COLLIDER_WIDTH, FIREFLOWER_COLLIDER_HEIGHT)) {
}
Mushroom::Mushroom (uint16_t start_x, uint16_t start_y) : Sprite_Animator (start_x, start_y, Item::ITEM_MODE, Item::ITEM_STATE, Item::ITEM_START_FRAME), Item::collider(Rect_Collider(start_x, start_y, MUSHROOM_COLLIDER_WIDTH, MUSHROOM_COLLIDER_HEIGHT)) {
	travelDir = rand() % 2;
}
Fireball::Fireball (uint16_t start_x, uint16_t start_y, Background * b) : Sprite_Animator (start_x, start_y, Item::ITEM_MODE, STATE_BOUNCE, Item::ITEM_START_FRAME), Item::collider(Rect_Collider(start_x, start_y, FIREBALL_COLLIDER_WIDTH, FIREBALL_COLLIDER_HEIGHT)){
	if (b == nullptr) {
		std::cout << "Fireball wont be displayed. Null background!" << std::endl;
		return;
	}
	current_background = b;
}
Coin::Coin (uint16_t start_x, uint16_t start_y) : Sprite_Animator (start_x, start_y, Item::ITEM_MODE, Item::ITEM_STATE, Item::ITEM_START_FRAME), Item::collider(Rect_Collider(start_x, start_y, COIN_COLLIDER_WIDTH, COIN_COLLIDER_HEIGHT)) {
}
void Item::setBackground(Background *b) {
	current_background = b;
}

void Fireball::setToExplode() {
	current_anim_state = STATE_EXPLODE;
}

/*
 *
 * Collision functions for special effects
 */
void Fireball::collided_with(Rect_Collider & other) {
	// Make sure the fireball either hits the side, or it hits an enemy before it is destroyed. Background will recycle outside objects
	if ((cantGoThrough(other.collider_type) && !collider.collides_above(other)) || isEnemy(other.collider_type)) {
		setToExplode();
	}
}
/*
 * Small state machine for fireball animation
 */
void Fireball::update() {
	current_anim_mode = Item::ITEM_MODE;
	if (wait_frames) {
		wait_frames--;
		return;
	}
	switch (current_anim_state) {
	case STATE_BOUNCE:
		// Does basically nothing. collided_with will set state to explode when a collision occurs
		break;
	case STATE_EXPLODE:
		wait_frames = EXPLODE_FRAMES;
		current_anim_state = STATE_DESTROY;
		break;
	}
	case STATE_DESTROY:
		// Delete the object then remove it from the background. This will decrease map size too
		delete current_background->fireballs[collider.collider_id];
		current_background->fireballs.erase(collider.collider_id);
		break;
	default:
		std::cout << "Unrecognized state in Fireball::update" << std::endl;
}
/*
 * TODO
 * Add animator setup for frames
 */
void Fireball::animatorSetup() {

}
/*
 * Defines how the Mushroom switches directions when hitting a object from the left or right. Only needs to know for player
 * collisions and platform collisions
 */
void Mushroom::collided_with(Rect_Collider & other) {
	if (cantGoThrough(other.collider_type) && !collider.collides_above(other)) {
		travelDir = !travelDir;
	}
	// Player checks if he got the sprite
}
/*
 * Simple update to determine which way it should go
 */
void Mushroom::update() {
	current_anim_state = ITEM_STATE;
	current_anim_mode = ITEM_MODE;
	if (travelDir == RIGHT) velX = MUSHROOM_TRAVEL_SPEED;
	else velX = -MUSHROOM_TRAVEL_SPEED;
}
/*
 * TODO
 * Add animator setup for Mushroom sprite
 */
void Mushroom::animatorSetup() {

}

/*
 *
 * Fireflower update function super simple.
 */
void Fireflower::update() {
	current_anim_state = ITEM_STATE;
	current_anim_mode = ITEM_MODE;
}

/*
 * TODO Initialize fireflower sprites in animSetup
 */
void Fireflower::animatorSetup() {

}
