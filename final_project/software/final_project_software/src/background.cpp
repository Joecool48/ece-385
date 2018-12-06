/*
 * background.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: joey
 */
#include "background.h"
#include "config.h"


/*
 * TODO update current_player in constructor
 */
Background::Background() {
	// Make sure width can fit on screen on that location
	x = 0;
	y = 0;
	window_width = SCREEN_WIDTH - x;
	window_height = SCREEN_HEIGHT - y;
	deadZoneLeft = 30;
	deadZoneRight = 30;
	maxScrollSpeed = 30;
	/* TODO
	 * Initialize width and height of background.
	 * Initialize all the colliders, players, enemies, and item meta data
	 */
	screenCenterX = x + (window_width / 2); // Center starts at middle of displayable screen
	current_player = nullptr; // Most likely Mario TODO make sure this is updated with a player
}

Background::~Background() {
	// Clean up all the memory used for keeping track of screen data
	for (unsigned i = 0; i < collidable_background_objects.size(); i++) {
		if (collidable_background_objects[i]) delete collidable_background_objects[i];
	}
	for (unsigned i = 0; i < enemies.size(); i++) {
		if (enemies[i]) delete enemies[i];
	}
	for (unsigned i = 0; i < items.size(); i++) {
		if (items[i]) delete items[i];
	}
	for (unsigned i = 0; i < fireballs.size(); i++) {
		if (fireballs[i]) delete fireballs[i];
	}
	if (current_player) delete current_player;
}
/*
 * TODO
 * MAKE SURE TO UPDATE THE BACKGROUND OBJECTS AS IT SCROLLS SO THAT THEY MOVE WITH IT
 */
void Background::scrollBackgroundX (int moveAmount) {
	if (screenCenterX + moveAmount - (window_width / 2) < x) {
		screenCenterX = x + (window_width / 2);
	}
	else if (screenCenterX + moveAmount + (window_width / 2) > width + x) {
		screenCenterX = x + width - (window_width / 2);
	}
	else {
		screenCenterX += moveAmount;
	}
}


void Background::drawBackground() {
	*SPRITE_X_PIO = x;
	*SPRITE_Y_PIO = y;
	// Stored column major order in memory
	*SPRITE_ADDRESS_PIO = start_address + height * (screenCenterX - (window_width / 2));
	*SPRITE_HEIGHT_PIO = height;
	*SPRITE_WIDTH_PIO = window_width;
	*SPRITE_ID_PIO = ++(*SPRITE_ID_PIO); // Make sure hardware sees change
}





/* TODO:
 * Draws all sprites in the layer in some rendering order. Called every frame
 * MAKE SURE TO UPDATE THE BACKGROUND EVERY TIME IT SCROLLS
 */
void Background::drawWindow() {
	drawBackground();
	// Don't need to draw background objects
	// Draw all the enemies at the current frame
	for (unsigned i = 0; i < enemies.size(); i++) {
		enemies[i]->getCurrentSprite().drawSprite();
	}
	// Draw all the items on the screen
	for (unsigned i = 0; i < items.size(); i++) {
		items[i]->getCurrentSprite().drawSprite();
	}

	// Just draw the player
	current_player->getCurrentSprite().drawSprite();
}

/*
 * Returns a rect_collider if an item is a item and is touching mario. Otherwise it returns the rect default constructor
 * as a sentinel value
 */
Rect_Collider Background::itemCollidedWithPlayer() {
	// Return sentinel value if the current_player is null
	if (current_player == nullptr) return Rect_Collider();
	unsigned i = 0;
	while (i < items.size()) {
		// Delete the element if it is null. Clears up some space
		if (items[i] == nullptr) {
			items.erase(items.begin() + i);
		}
		else {
			if (items[i]->collider.collides_with(current_player->player_collider)) return items[i]->collider;
			i++;
		}
	}
	return Rect_Collider();
}

/*
 * Returns the rect_collider of the enemy that collided with the player. This logic will only determine if they hit.
 * In the player class it will determine if the player takes damage, or the enemy is killed
 */
Rect_Collider Background::enemyCollidedWithPlayer() {
	// Return sentinel value if the current_player is null
	if (current_player == nullptr) return Rect_Collider();
	unsigned i = 0;
	while (i < enemies.size()) {
		// Delete the element if it is null. Clears up some space
		if (enemies[i] == nullptr) {
			enemies.erase(enemies.begin() + i);
		}
		else {
			if (enemies[i]->collider.collides_with(current_player->player_collider)) return enemies[i]->collider;
			i++;
		}
	}
	return Rect_Collider();
}


/*
 * These two methods remove stuff in the background vector by rect_collider reference.
 * Uses rect_collider equals method
 */
void Background::removeItemByCollider(Rect_Collider & collider) {
	for (unsigned i = 0; i < items.size(); i++) {
		if (items[i] != nullptr && items[i]->collider.equals(collider)) {
			items.erase(items.begin() + i);
			return;
		}
	}
}
void Background::removeEnemyByCollider(Rect_Collider & collider) {
	for (unsigned i = 0; i < enemies.size(); i++) {
		if (enemies[i] != nullptr && enemies[i]->collider.equals(collider)) {
			enemies.erase(enemies.begin() + i);
			return;
		}
	}
}







