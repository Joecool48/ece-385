/*
 * Sprite.cpp
 *
 *  Created on: Nov 27, 2018
 *      Author: joey
 */
#include "game_classes.h"
#include "config.h"


Background::Background(Player * p) {
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
	current_player = p; // Most likely Mario
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
	if (current_player) delete current_player;
}

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


/* TODO: Make function warn when it is drawing out of range
 * Draws a sprite at a specified location by placing it in memory
 */
void Sprite::drawSprite() {
	if (isVisible) {
		*SPRITE_X_PIO = x;
		*SPRITE_Y_PIO = y;
		*SPRITE_ADDRESS_PIO = start_address;
		*SPRITE_WIDTH_PIO = width;
		*SPRITE_HEIGHT_PIO = height;
		*SPRITE_ID_PIO = ++(*SPRITE_ID_PIO);
	}
}


/* TODO:
 * Draws all sprites in the layer in some rendering order.
 * Background
 * Items
 * Enemies
 * Player
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

void Sprite_Animator::setAnimType(Anim_State anim_state) {
	current_anim_state = anim_state;
}
void Sprite_Animator::advanceFrame() {
	current_frame += 1;
}
Sprite Sprite_Animator::getCurrentSprite() {

}


















