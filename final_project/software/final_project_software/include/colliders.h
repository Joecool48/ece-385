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

class Collidable {
public:
	uint16_t collide_id;
	uint16_t collide_x;
	uint16_t collide_y;
	Collidable (uint16_t collide_id, uint16_t collide_x, uint16_t collide_y);
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
};

class Complex_Collider : public Collidable {
	// Multiple eRect colliders in vector
	vector<Rect_Collider> colliders;
	Complex_Collider::Complex_Collider(uint16_t collide_id, uint16_t collide_x, uint16_t collide_y, vector<Rect_Collider> colliders) {}
	Rect_Collider collides_with (Rect_Collider & other);
	Rect_Collider collides_above (Rect_Collider & other);
	Rect_Collider collides_below (Rect_Collider & other);
	Rect_Collider collides_left (Rect_Collider & other);
	Rect_Collider collides_right (Rect_Collider & other);
};



#endif /* INCLUDE_COLLIDERS_H_ */
