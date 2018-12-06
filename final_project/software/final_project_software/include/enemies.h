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
};
/*
 * TODO create Gumba
 * Possibly implement dying animation
 */
class Gumba : public Enemy {
	uint16_t NORMAL_MODE = 0;
	enum states {WALKING, DESTROY};
	void animatorSetup();
	void update();
};
/*
 * TODO create turtle which has a shell mode
 * Dying animation will not be implemented due to lack of time
 */
class Turtle : public Enemy {
	uint16_t NORMAL_MODE = 0;
	enum states {WALKING, SHELL, SHELL_MOVING, GET_UP, DESTROY};
	void animatorSetup();
	void update();
};

#endif /* INCLUDE_ENEMIES_H_ */
