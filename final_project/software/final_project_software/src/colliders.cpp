/*
 * colliders.cpp
 *
 *  Created on: Nov 29, 2018
 *      Author: joey
 */
#include "colliders.h"

Collidable::Collidable(Collider_Type collide_type, uint16_t collide_x, uint16_t collide_y) : collider_type(collide_type), collide_x(collide_x), collide_y(collide_y) {
	current_id++;
	collider_id = current_id;
}

Rect_Collider::Rect_Collider (Collider_Type collide_type, uint16_t collide_x, uint16_t collide_y, uint16_t collide_width, uint16_t collide_height) : Collidable(collide_type, collide_x, collide_y), collide_width(collide_width), collide_height(collide_height) {}


// Used as a starter, or sentinel value for the Complex_Collider
Rect_Collider::Rect_Collider() : Collidable(Collider_Type::DUMMY_COLLIDER_TYPE, 0, 0), collide_width(0), collide_height(0) {}

//Complex_Collider::Complex_Collider(Collider_Type collide_type, uint16_t collide_x, uint16_t collide_y, vector<Rect_Collider> colliders) : collider_type(collide_type), collide_x(collide_x), collide_y(collide_y), colliders(colliders) {}

/*
 * Returns true if the two rect colliders collide, otherwise false
 */
bool Rect_Collider::collides_with(Rect_Collider & other) {
	return (collide_x + collide_width >= other.collide_x && collide_x <= other.collide_x + other.collide_width &&
			collide_y + collide_height >= other.collide_y && collide_y <= other.collide_y + other.collide_height);
}
/* TODO:
 * Determines whether the one collider is on top of the other.
 * For detecting whether Mario jumped on a enemy
 */
bool Rect_Collider::collides_above(Rect_Collider & other) {
	return (collides_with(other) && (collide_x + collide_width / 2 >= other.collide_x || collide_x >= other.collide_x + other.collide_width / 2)
			&& collide_y + collide_height < other.collide_y + other.collide_height / 2);
}

/* TODO:
 * Determines whether the one collider is on left of the other.
 * For detecting whether Mario jumped on a enemy
 */
bool Rect_Collider::collides_left(Rect_Collider & other) {
	return (collides_with(other) && collide_x + collide_width / 2 >= other.collide_x && collide_x + collide_width < other.collide_x + other.collide_width / 2);
}

/* TODO:
 * Determines whether the one collider is on right of the other.
 * For detecting whether Mario jumped on a enemy
 */
bool Rect_Collider::collides_right(Rect_Collider & other) {
	return other.collides_left(*this);
}

/* TODO:
 * Determines whether the one collider is on down of the other.
 * For detecting whether Mario jumped on a enemy
 */
bool Rect_Collider::collides_below(Rect_Collider & other) {
	return other.collides_above(*this);
}

///*
// * Determines if the complex collider collides with any other rect, and if so which one
// */
//Rect_Collider Complex_Collider::collides_with(Rect_Collider & other) {
//	for (unsigned i = 0; i < colliders.size(); i++) {
//		if (colliders[i].collides_with(other)) {
//			return colliders[i];
//		}
//	}
//	return Rect_Collider();
//}
//
///*
// * Determines if the other complex collider collides above the other collider
// */
//Rect_Collider Complex_Collider::collides_above(Rect_Collider & other) {
//	for (unsigned i = 0; i < colliders.size(); i++) {
//		if (colliders[i].collides_above(other)) {
//			return colliders[i];
//		}
//	}
//	return Rect_Collider();
//}
//
///*
// * Determines if the other complex collider collides left of the other collider
// */
//Rect_Collider Complex_Collider::collides_left(Rect_Collider & other) {
//	for (unsigned i = 0; i < colliders.size(); i++) {
//		if (colliders[i].collides_left(other)) {
//			return colliders[i];
//		}
//	}
//	return Rect_Collider();
//}
//
///*
// * Determines if the other complex collider collides right of the other collider
// */
//Rect_Collider Complex_Collider::collides_right(Rect_Collider & other) {
//	for (unsigned i = 0; i < colliders.size(); i++) {
//		if (colliders[i].collides_right(other)) {
//			return colliders[i];
//		}
//	}
//	return Rect_Collider();
//}
//
///*
// * Determines if the other complex collider collides below the other collider
// */
//Rect_Collider Complex_Collider::collides_below(Rect_Collider & other) {
//	for (unsigned i = 0; i < colliders.size(); i++) {
//		if (colliders[i].collides_below(other)) {
//			return colliders[i];
//		}
//	}
//	return Rect_Collider();
//}




















