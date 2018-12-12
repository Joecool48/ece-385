/*
 * brain.h
 *
 *  Created on: Dec 3, 2018
 *      Author: joey
 */

#ifndef INCLUDE_BRAIN_H_
#define INCLUDE_BRAIN_H_
class Background;
class Enemy;
#include "background.h"
#include "enemies.h"
// Base class for enemy AI
class Brain {
public:
	const bool LEFT = 0;
	const bool RIGHT = 1;
	virtual ~Brain();
	Background * background;
	Enemy * enemy;
	void makeDecision();
	Brain(Background * back, Enemy * enemy);
	bool willFallOffCliff(uint16_t numFrames);
};


#endif /* INCLUDE_BRAIN_H_ */
