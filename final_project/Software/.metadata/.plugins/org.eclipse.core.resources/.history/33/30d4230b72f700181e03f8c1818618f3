/*
 * Sprite.h
 *
 *  Created on: Nov 27, 2018
 *      Author: joey
 */

#ifndef INCLUDE_GAME_CLASSES_H_
#define INCLUDE_GAME_CLASSES_H_

#include <vector>
#include <stdint.h>
#include <map>
#include <unordered_map>
using namespace std;


// Base class for enemy AI
class Brain {
	virtual ~Brain();
	Brain();
};

/*
 * TODO:
 * Create the fundamental AI for enemies
 */
class Enemy : public Sprite_Animator {
	Rect_Collider collider;
	Brain brain;
};

class Item : public Sprite_Animator {
	bool isCollectable;
	Rect_Collider collider;
	Item();
};

class Background_Object : public Background_Sprite {
	Collidable *collider;
};
#endif /* INCLUDE_GAME_CLASSES_H_ */
