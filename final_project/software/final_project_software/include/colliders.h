/*
 * colliders.h
 *
 *  Created on: Nov 29, 2018
 *      Author: joey
 */

#ifndef INCLUDE_COLLIDERS_H_
#define INCLUDE_COLLIDERS_H_

#include <vector>
using namespace std;
/*
 * TODO:
 * 	ADD MORE COLLIDERS AND FIX THE FACT THAT COLLIDERS OF DIFFERENT TYPES CANT BE CHECKED
 */
/*
 * TODO make sure to set isTrigger when putting item sprites on screen
 * Triggering means it doesnt move other objects
 */
class Collidable {
public:
	Collider_Id collide_id;
	uint16_t collide_x;
	uint16_t collide_y;
	bool isTrigger;
	Collidable (uint16_t collide_id, uint16_t collide_x, uint16_t collide_y, bool isTrig);
	virtual ~Collidable();
};

class Rect_Collider : public Collidable {
public:
	uint16_t collide_width;
	uint16_t collide_height;
	Rect_Collider (uint16_t collide_id, uint16_t collide_x, uint16_t collide_y, uint16_t collide_width, uint16_t collide_height);
	Rect_Collider();
	bool collides_with (Rect_Collider & other);
	bool collides_above (Rect_Collider & other);
	bool collides_below (Rect_Collider & other);
	bool collides_left (Rect_Collider & other);
	bool collides_right (Rect_Collider & other);
	// Implement method to check for equality between rects
	bool equals(Rect_Collider & other);
};

class Complex_Collider : public Collidable {
	// Multiple eRect colliders in vector
public:
	vector<Rect_Collider> colliders;
	Complex_Collider::Complex_Collider(uint16_t collide_id, uint16_t collide_x, uint16_t collide_y, vector<Rect_Collider> colliders) {}
	Rect_Collider collides_with (Rect_Collider & other);
	Rect_Collider collides_above (Rect_Collider & other);
	Rect_Collider collides_below (Rect_Collider & other);
	Rect_Collider collides_left (Rect_Collider & other);
	Rect_Collider collides_right (Rect_Collider & other);
};



#endif /* INCLUDE_COLLIDERS_H_ */
