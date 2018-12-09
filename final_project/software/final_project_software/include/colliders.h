/*
 * colliders.h
 *
 *  Created on: Nov 29, 2018
 *      Author: joey
 */

#ifndef INCLUDE_COLLIDERS_H_
#define INCLUDE_COLLIDERS_H_

#include <vector>
#include <stdint.h>
#include "../include/config.h"

/*
 * TODO:
 * 	ADD MORE COLLIDERS AND FIX THE FACT THAT COLLIDERS OF DIFFERENT TYPES CANT BE CHECKED
 */
/*
 * TODO make sure to set isTrigger when putting item sprites on screen
 * Triggering means it doesnt move other objects
 */
enum class Collider_Type {DUMMY_COLLIDER_TYPE,
						GUMBA,
						FIREBALL,
						FIREFLOWER,
						MUSHROOM,
						TURTLE,
						TURTLE_SHELL,
						PLATFORM_UNBREAKABLE,
						ITEM_BLOCK,
						PLAYER
						}; // List all the possible objects on the screen. The background tells another object when it collides, and what it should do

bool cantGoThrough(Collider_Type type);
bool isEnemy(Collider_Type type);

// GUMBA, TURTLE, and TURTLE_SHELL are considered enemies

class Collidable {
public:
	static uint64_t current_id;
	uint64_t collider_id;
	Collider_Type collide_type;
	float collide_x;
	float collide_y;
	static bool cantGoThrough (Collider_Type type);
	static bool isEnemy (Collider_Type type);
	Collidable (Collider_Type collider_type, uint16_t collide_x, uint16_t collide_y);
	virtual ~Collidable();
};

class Rect_Collider : public Collidable {
public:
	uint16_t collide_width;
	uint16_t collide_height;
	Rect_Collider (Collider_Type collide_type, uint16_t collide_x, uint16_t collide_y, uint16_t collide_width, uint16_t collide_height);
	Rect_Collider();
	bool collides_with (Rect_Collider & other);
	bool collides_above (Rect_Collider & other);
	bool collides_below (Rect_Collider & other);
	bool collides_left (Rect_Collider & other);
	bool collides_right (Rect_Collider & other);
//	// Implement method to check for equality between rects
//	bool equals(Rect_Collider & other);
};

//class Complex_Collider : public Collidable {
//	// Multiple eRect colliders in vector
//public:
//	vector<Rect_Collider> colliders;
//	Complex_Collider::Complex_Collider(uint16_t collide_id, uint16_t collide_x, uint16_t collide_y, vector<Rect_Collider> colliders) {}
//	Rect_Collider collides_with (Rect_Collider & other);
//	Rect_Collider collides_above (Rect_Collider & other);
//	Rect_Collider collides_below (Rect_Collider & other);
//	Rect_Collider collides_left (Rect_Collider & other);
//	Rect_Collider collides_right (Rect_Collider & other);
//};



#endif /* INCLUDE_COLLIDERS_H_ */
