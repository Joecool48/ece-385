/*
 * enemies.h
 *
 *  Created on: Dec 3, 2018
 *      Author: joey
 */

#ifndef INCLUDE_ENEMIES_H_
#define INCLUDE_ENEMIES_H_

#include "config.h"
#include "background.h"

/*
 * TODO:
 * Create the fundamental AI for enemies
 */
class Enemy : public Sprite_Animator {
public:
	Rect_Collider collider;
	Background * current_background;
	float velX, velY;
	bool noCollide;
	Enemy();
	void gravity();
	void setBackground(Background *b);
	void destroyInBackground();
	virtual void collided_with(Rect_Collider & other);
	Brain brain;
};
/*
 * TODO create Gumba
 * Possibly implement dying animation
 */
class Gumba : public Enemy {
	uint16_t NORMAL_MODE = 0;
	enum states {WALKING, DYING, DYING_FIREBALL, DESTROY};
	void collided_with(Rect_Collider & other);
	const uint16_t DIE_FRAMES = 20;
	void animatorSetup();
	void update();
};
/*
 * TODO create turtle which has a shell mode
 * Dying animation will not be implemented due to lack of time
 */
class Turtle : public Enemy {
	uint16_t NORMAL_MODE = 0;
	const uint16_t REMAIN_IN_SHELL_FRAMES = 300;
	const uint16_t SHELL_MOVE_SPEED = .5;
	bool shell_move_right;
	enum states {WALKING, SHELL, SHELL_MOVING, GET_UP, DYING_FIREBALL, DESTROY};
	void collided_with(Rect_Collider & other);
	void animatorSetup();
	void update();
private:
	uint16_t shell_timer;
};

#endif /* INCLUDE_ENEMIES_H_ */
