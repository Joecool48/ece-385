/*
 * brain.cpp
 *
 *  Created on: Nov 29, 2018
 *      Author: joey
 */
#include "../include/brain.h"

// Caller destroyed variables
Brain::Brain(Background *back, Enemy * enemy) {
	this->background = back;
	this->enemy = enemy;
}
// Do nothing. All pointers are caller destroyed
Brain::~Brain() {}

// Simple function to make a decision where to move in which direction
void Brain::makeDecision() {
	if (willFallOffCliff(5) && enemy->velX != 0) {
		enemy->velX *= -1;
		return;
	}
	else if (willFallOffCliff(3)) {
		enemy->velX = (rand() % 2) ? -enemy->velX : enemy->velX;
	}
	else {
		enemy->velX = 0;
	}
}
/*
 * Detects if the enemy will fall off the cliff in this many steps based on its current velocity
 */
bool Brain::willFallOffCliff(uint16_t numFrames) {
	Rect_Collider update_collider = enemy->collider;

	update_collider += enemy->velX * numFrames;
	if(update_collider.collides_with(enemy->last_collided) && !background->outOfBounds(update_collider)) {
		return false;
	}
	return true;
}
