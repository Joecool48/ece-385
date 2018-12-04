/*
 * enemies.h
 *
 *  Created on: Dec 3, 2018
 *      Author: joey
 */

#ifndef INCLUDE_ENEMIES_H_
#define INCLUDE_ENEMIES_H_


/*
 * TODO:
 * Create the fundamental AI for enemies
 */
class Enemy : public Sprite_Animator {
public:
	Rect_Collider collider;
	Brain brain;
	void animatorSetup();
	void update();
};


#endif /* INCLUDE_ENEMIES_H_ */
