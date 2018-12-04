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
Item::Item (uint16_t start_x, uint16_t start_y, Rect_Collider rect) : Sprite_Animator (start_x, start_y, Item::ITEM_MODE, Item::ITEM_STATE, Item::ITEM_START_FRAME), Item::collider(Rect_Collider(rect)){
}
Fireflower::Fireflower (uint16_t start_x, uint16_t start_y) : Sprite_Animator (start_x, start_y, Item::ITEM_MODE, Item::ITEM_STATE, Item::ITEM_START_FRAME), Item::collider(Rect_Collider(start_x, start_y, FIREFLOWER_COLLIDER_WIDTH, FIREFLOWER_COLLIDER_HEIGHT)) {
}
Mushroom::Mushroom (uint16_t start_x, uint16_t start_y) : Sprite_Animator (start_x, start_y, Item::ITEM_MODE, Item::ITEM_STATE, Item::ITEM_START_FRAME), Item::collider(Rect_Collider(start_x, start_y, MUSHROOM_COLLIDER_WIDTH, MUSHROOM_COLLIDER_HEIGHT)) {
	travelDir = rand() % 2;
}
Fireball::Fireball (uint16_t start_x, uint16_t start_y) : Sprite_Animator (start_x, start_y, Item::ITEM_MODE, Item::ITEM_STATE, Item::ITEM_START_FRAME), Item::collider(Rect_Collider(start_x, start_y, FIREBALL_COLLIDER_WIDTH, FIREBALL_COLLIDER_HEIGHT)){
}
Coin::Coin (uint16_t start_x, uint16_t start_y) : Sprite_Animator (start_x, start_y, Item::ITEM_MODE, Item::ITEM_STATE, Item::ITEM_START_FRAME), Item::collider(Rect_Collider(start_x, start_y, COIN_COLLIDER_WIDTH, COIN_COLLIDER_HEIGHT)) {
}
/*
 * TODO
 * Collision functions for special effects
 */
void Fireball::collided_with(Rect_Collider & other) {
	if (cantGoThrough(other.collide_id)) {

	}
}
