/*
 * item.h
 *
 *  Created on: Dec 3, 2018
 *      Author: joey
 */
#include "sprite_animator.h"
#include "colliders.h"

#ifndef INCLUDE_ITEM_H_
#define INCLUDE_ITEM_H_
/* TODO
 * Implement item setups
 */
class Item : public Sprite_Animator {
public:
	const float ITEM_START_FRAME = 0;
	const uint16_t ITEM_MODE = 0;
	const uint16_t ITEM_STATE = 0;
	Rect_Collider collider;
	float velX = 0, velY = 0;
	// Used to sent a signal telling the item it collided. No physics implemented, just special actions
	virtual void collided_with (Rect_Collider & other) = 0;
	Item(uint16_t start_x, uint16_t start_y, Rect_Collider rect);
};
/*
 * TODO
 * Add real values for the collider width and height
 */
class Fireflower : public Item {
public:
	Fireflower(uint16_t start_x, uint16_t start_y);
	const uint16_t FIREFLOWER_COLLIDER_WIDTH = 30;
	const uint16_t FIREFLOWER_COLLIDER_HEIGHT = 15;
	void update();
	void animatorSetup();
};
/*
 * TODO
 * Add real values for the collider width and height
 */
class Mushroom : public Item {
public:
	Mushroom(uint16_t start_x, uint16_t start_y);
	const bool LEFT = 0;
	const bool RIGHT = 1;
	const uint16_t MUSHROOM_COLLIDER_WIDTH = 30;
	const uint16_t MUSHROOM_COLLIDER_HEIGHT = 15;
	bool travelDir;
	void collided_with(Rect_Collider & other);
	void update();
	void animatorSetup();
};

class Coin : public Item {
public:
	Coin(uint16_t start_x, uint16_t start_y);
	void update();
	const uint16_t COIN_COLLIDER_WIDTH = 15;
	const uint16_t COIN_COLLIDER_HEIGHT = 15;
	void animatorSetup();
};
/*
 * TODO
 * Add real values for the collider width and height
 */
class Fireball : public Sprite_Animator {
public:
	Fireball(uint16_t start_x, uint16_t start_y);
	Rect_Collider collider;
	const float FIREBALL_SPEED_BOUNCE = .5;
	const uint16_t FIREBALL_COLLIDER_WIDTH = 10;
	const uint16_t FIREBALL_COLLIDER_HEIGHT = 10;
	void collided_with(Rect_Collider & other);
	void update();
	void animatorSetup();
};

#endif /* INCLUDE_ITEM_H_ */
