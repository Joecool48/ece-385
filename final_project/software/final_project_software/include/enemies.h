/*
 * enemies.h
 *
 *  Created on: Dec 3, 2018
 *      Author: joey
 */

#ifndef INCLUDE_ENEMIES_H_
#define INCLUDE_ENEMIES_H_

#include "../include/config.h"
#include "../include/background.h"
#include "../include/brain.h"

class Background;
class Collidable;
class Rect_Collider;
class Brain;

class Enemy : public Sprite_Animator {
public:
	Rect_Collider collider;
	Background * current_background;
	float velX, velY;
	bool noCollide;
	uint16_t ENEMY_MODE = 213;
	uint16_t ENEMY_STATE = 23;
	Rect_Collider last_collided; // Collider to store the last collision. Used for fast implementation of enemy intelligence (simple)
	Enemy(Background * b);
	virtual ~Enemy();
	void draw();
	void gravity();
	void setBackground(Background *b);
	void destroyInBackground();
	virtual void collided_with(Rect_Collider & other) = 0;
	Brain *brain;
};
/*
 * TODO create Gumba
 * Possibly implement dying animation
 */
class Gumba : public Enemy {
public:
	uint16_t NORMAL_MODE = 0;
	enum states {WALKING, DYING, DYING_FIREBALL, DESTROY};
	void collided_with(Rect_Collider & other);
	const uint16_t DIE_FRAMES = 20;
	void animatorSetup();
	Gumba(uint16_t x, uint16_t y, Background * b);
	const static uint16_t GUMBA_COLLIDER_WIDTH = 16;
	const static uint16_t GUMBA_COLLIDER_HEIGHT = 32;
	void update();
};
/*
 * TODO create turtle which has a shell mode
 * Dying animation will not be implemented due to lack of time
 */
class Turtle : public Enemy {
public:
	uint16_t NORMAL_MODE = 0;
	const uint16_t REMAIN_IN_SHELL_FRAMES = 300;
	const float SHELL_MOVE_SPEED = .5;
	bool shell_move_right;
	enum states {WALKING, SHELL, SHELL_MOVING, GET_UP, DYING_FIREBALL, DESTROY};
	const static uint16_t TURTLE_COLLIDER_WIDTH = 16;
	const static uint16_t TURTLE_COLLIDER_HEIGHT = 32;
	void collided_with(Rect_Collider & other);
	void animatorSetup();
	Turtle(uint16_t x, uint16_t y, Background * b);
	void update();
private:
	uint16_t shell_timer;
};

#endif /* INCLUDE_ENEMIES_H_ */
