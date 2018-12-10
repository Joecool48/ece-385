/*
 * background.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: joey
 */

#include "../include/background.h"

#include <cstdint>
#include <iostream>

/*
 * Returns true if the rect collider is outside the visible dimensions of the screen
 */
bool Background::offScreen(Rect_Collider & other) {
	return (other.collide_x > screenCenterX + window_width / 2 || other.collide_y > window_height);
}

Background_Object::Background_Object(Rect_Collider collider, bool contains_item) {
	this->collider = collider;
	this->contains_item = contains_item;
}
// Vel is for direction
float overlapX (Rect_Collider & rect1, Rect_Collider & rect2, float velX) {
	float dist1 = 0, dist2 = 0;
	dist1 = rect2.collide_x + rect2.collide_width - rect1.collide_x;
	if (dist1 > 0 && velX < 0) return dist1;
	dist2 = rect1.collide_x + rect1.collide_width - rect2.collide_x;
	if (dist2 > 0 && velX > 0) return -dist2;
	return 0;

}
// Returns how much to offset rect1 first param
float overlapY (Rect_Collider & rect1, Rect_Collider & rect2, float velY) {
	std::cout << "Vely in overlapy " << velY << std::endl;
	float dist1 = 0, dist2 = 0;
	dist1 = rect1.collide_y + rect1.collide_height - rect2.collide_y;
	// Allow for some tolerance with gravity
	if (dist1 > 0 && velY > GRAVITY_STRENGTH) return -dist1;
	dist2 = rect2.collide_y + rect2.collide_height - rect1.collide_y;
	if (dist2 < 0 && velY < GRAVITY_STRENGTH) return dist2;
	return 0;
}

/*
 *
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
	for (auto it = enemies.begin(); it != enemies.end(); it++) {
		if (it->second != nullptr)
			delete it->second;
	}
	// Draw all the items on the screen
	for (auto it = items.begin(); it != items.end(); it++) {
		if (it->second != nullptr)
			delete it->second;
	}
	// Draw all fireballs thrown by the player
	for (auto it = fireballs.begin(); it != fireballs.end(); it++) {
		if (it->second != nullptr)
			delete it->second;
	}
	// Just draw the player
	if (current_player != nullptr)
		delete current_player;
}
/*
 * TODO
 * MAKE SURE TO UPDATE THE BACKGROUND OBJECTS AS IT SCROLLS SO THAT THEY MOVE WITH IT
 */
void Background::scrollBackgroundX (int moveAmount) {
	int screenCenterXOriginal = screenCenterX;
	if (screenCenterX + moveAmount - (window_width / 2) < x) {
		screenCenterX = x + (window_width / 2);
	}
	else if (screenCenterX + moveAmount + (window_width / 2) > width + x) {
		screenCenterX = x + width - (window_width / 2);
	}
	else {
		screenCenterX += moveAmount;
	}
//	for (auto it = collidable_background_objects.begin(); it != collidable_background_objects.end(); it++) {
//		it->second->collider.collide_x -= (screenCenterX - screenCenterXOriginal);
//	}
}


void Background::drawBackground() {
	std::cout << "DrawBackground" << std::endl;
	*Sprite::SPRITE_X_PIO = static_cast<uint16_t>(x);
	*Sprite::SPRITE_Y_PIO = static_cast<uint16_t>(y);
	// Stored column major order in memory
	*Sprite::SPRITE_ADDRESS_PIO = start_address + height * (screenCenterX - (window_width / 2));
	*Sprite::SPRITE_HEIGHT_PIO = height;
	*Sprite::SPRITE_WIDTH_PIO = window_width;
	*Sprite::SPRITE_ID_PIO = ++(*Sprite::SPRITE_ID_PIO); // Make sure hardware sees change
	std::cout << "End draw Background" << std::endl;
}





/*:
 * Draws all sprites in the layer in some rendering order. Called every frame
 * Blindly updates. Doesnt check for anything
 *
 */
void Background::drawWindow() {
	drawBackground();
	// Don't need to draw background objects
	// Draw all the enemies at the current frame
	for (auto it = enemies.begin(); it != enemies.end(); it++) {
		if (it->second != nullptr && !offScreen(it->second->collider))
			it->second->draw();
	}
	// Draw all the items on the screen
	for (auto it = items.begin(); it != items.end(); it++) {
		if (it->second != nullptr && !offScreen(it->second->collider))
			it->second->draw();
	}
	// Draw all fireballs thrown by the player
	for (auto it = fireballs.begin(); it != fireballs.end(); it++) {
		if (it->second != nullptr && !offScreen(it->second->collider))
			it->second->draw();
	}
	// Just draw the player
	if (current_player != nullptr) // Player should always be drawn and onscreen
		current_player->draw();
	else
		std::cout << "Player is null when trying to draw him :(" << std::endl;
}

/*
 * Returns a rect_collider if an item is a item and is touching mario. Otherwise it returns the rect default constructor
 * as a sentinel value
 */
Rect_Collider Background::itemCollidedWithPlayer() {
	// Return sentinel value if the current_player is null
	if (current_player == nullptr) return Rect_Collider();
	for (auto it = items.begin(); it != items.end();) {
		// Delete the element if it is null. Clears up some space
		if (it->second == nullptr) {
			it = items.erase(it);
		}
		else {
			if (it->second->collider.collides_with(current_player->player_collider)) return it->second->collider;
			it++;
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
	auto it = enemies.begin();
	while(it != enemies.end()) {
		// Delete the element if it is null. Clears up some space
		if (it->second == nullptr) {
			it = enemies.erase(it);
		}
		else {
			if (it->second->collider.collides_with(current_player->player_collider)) return it->second->collider;
			it++;
		}
	}
	return Rect_Collider();
}
/*
 * Sets player in background
 */
void Background::setPlayer(Player *curr_player) {
	if (curr_player == nullptr) {
		std::cout << "Setting current_player to null in setPlayer" << std::endl;
		return;
	}
	current_player = curr_player;
}

/*
 * These two methods remove stuff in the background vector by rect_collider id.
 *
 */
void Background::removeItemById(uint64_t id) {
	if (items.find(id) != items.end()) {
		if (items[id] != nullptr) {
			delete items[id];
		}
		items.erase(id);
	}
}
void Background::removeEnemyById(uint64_t id) {
	if (enemies.find(id) != enemies.end()) {
		if (enemies[id] != nullptr) {
			delete enemies[id];
		}
		enemies.erase(id);
	}
}

bool Background::outOfBounds(Rect_Collider & other) {
	return (other.collide_x + other.collide_width < 0 || other.collide_x >= width || other.collide_y >= height || other.collide_y + other.collide_y < 0);
}

void Background::updateBackground() {
	// Move the background based on player pos
	std::cout << "Player mode " << unsigned(current_player->getMode()) << std::endl;
	std::cout << "Player frame " << unsigned(current_player->current_frame_in_state) << std::endl;
	std::cout << "Begin background player y " << current_player->player_collider.collide_y << std::endl;
	// TODO turn on scrolling again sometime
	if (current_player != nullptr)
		scrollBackgroundX(current_player->velX);
	for (auto it = items.begin(); it != items.end();) {
		if (it->second == nullptr || outOfBounds(it->second->collider)) {
			it = items.erase(it);
		}
		else {
			it->second->update();
			it->second->gravity();
			it++;
		}
	}
	for (auto it = enemies.begin(); it != enemies.end();) {
		if (it->second == nullptr || outOfBounds(it->second->collider)) {
			it = enemies.erase(it);
		}
		else {
			it->second->update();
			it->second->gravity();
			it++;
		}
	}
	for (auto it = fireballs.begin(); it != fireballs.end();) {
		if (it->second == nullptr || outOfBounds(it->second->collider)) {
			it = fireballs.erase(it);
		}
		else {
			it->second->update();
			it->second->gravity();
			it++;
		}
	}
	std::cout << "Before player y update " << current_player->player_collider.collide_y << std::endl;
	current_player->update();
	std::cout << "After update player y " << current_player->player_collider.collide_y << std::endl;
	current_player->gravity();
	resolveCollisions();
	drawWindow();
}



// Checks and update all the collisions
void Background::resolveCollisions() {
	std::cout << "Started resolveCollisions" << std::endl;
//	map<uint64_t, Background_Object*> collidable_background_objects; // Objects that aren't seperate sprites, but are still collidable on the map; These update every frame with the background
//	Player * current_player;
//	map<uint64_t, Enemy*> enemies;
//	map<uint64_t, Item*> items;
//	map<uint64_t, Fireball*> fireballs;
	float shiftX = 0;
	float shiftY = 0;
	for (auto backgroundIt = collidable_background_objects.begin(); backgroundIt != collidable_background_objects.end(); backgroundIt++) {
		if (backgroundIt->second == nullptr) continue;
		for (auto enemiesIt = enemies.begin(); enemiesIt != enemies.end(); enemiesIt++) {
			Rect_Collider update_collider = enemiesIt->second->collider;
			update_collider.collide_x += enemiesIt->second->velX;
			update_collider.collide_y += enemiesIt->second->velY;
			if (!enemiesIt->second->noCollide && update_collider.collides_with(backgroundIt->second->collider)) {
				// Remove updated y to see if x collides
				update_collider.collide_y -= enemiesIt->second->velY;
				if (update_collider.collides_with(backgroundIt->second->collider) && (update_collider.collides_left(backgroundIt->second->collider) || update_collider.collides_right(backgroundIt->second->collider))) {
					shiftX = overlapX(update_collider, backgroundIt->second->collider, enemiesIt->second->velX);
					if (shiftX != 0) {
						enemiesIt->second->collider.collide_x += shiftX + enemiesIt->second->velX;
						enemiesIt->second->velX = 0;
					}
				}
				update_collider.collide_x -= enemiesIt->second->velX; // Remove velX update and add velY
				update_collider.collide_y += enemiesIt->second->velY;
				if (update_collider.collides_with(backgroundIt->second->collider) && (update_collider.collides_left(backgroundIt->second->collider) || update_collider.collides_right(backgroundIt->second->collider))) {
					shiftY = overlapY(update_collider, backgroundIt->second->collider, enemiesIt->second->velY);
					if (shiftY != 0) {
						enemiesIt->second->collider.collide_y += shiftY + enemiesIt->second->velY;
						enemiesIt->second->velY = 0;
					}
				}
			}
		}
		Rect_Collider update_collider = current_player->player_collider;
		update_collider.collide_x += current_player->velX;
		update_collider.collide_y += current_player->velY;
		if (current_player != nullptr && update_collider.collides_with(backgroundIt->second->collider) && !current_player->noCollide) {
			std::cout << "Player collided with background object at " << backgroundIt->second->collider.collide_x << " " << backgroundIt->second->collider.collide_y << std::endl;
			update_collider.collide_x -= current_player->velX; // Check vely first
			if (update_collider.collides_with(backgroundIt->second->collider) && (update_collider.collides_above(backgroundIt->second->collider) || update_collider.collides_below(backgroundIt->second->collider))) {
				shiftY = overlapY(update_collider, backgroundIt->second->collider, current_player->velY);
				std::cout << "Shifty is " << shiftY << std::endl;
				if (shiftY != 0) {
					current_player->player_collider.collide_y += shiftY + current_player->velY;
					current_player->velY = 0;
				}
			}
			update_collider.collide_y -= current_player->velY;
			update_collider.collide_x += current_player->velX;
			if (update_collider.collides_with(backgroundIt->second->collider) && (update_collider.collides_left(backgroundIt->second->collider) || update_collider.collides_right(backgroundIt->second->collider))) {
				shiftX = overlapX(update_collider, backgroundIt->second->collider, current_player->velX);
				if (shiftX != 0) {
					current_player->player_collider.collide_x += shiftX + current_player->velX;
					current_player->velX = 0;
				}
			}
			// Pass in background too
			backgroundIt->second->collided_with(current_player->player_collider, this);
			current_player->collided_with(backgroundIt->second->collider);
		}
		for (auto itemsIt = items.begin(); itemsIt != items.end(); itemsIt++) {
			Rect_Collider update_collider = itemsIt->second->collider;
			update_collider.collide_x += itemsIt->second->velX;
			update_collider.collide_y += itemsIt->second->velY;
			if (update_collider.collides_with(backgroundIt->second->collider)) {
				// Remove updated y to see if x collides
				update_collider.collide_y -= itemsIt->second->velY;
				if (update_collider.collides_with(backgroundIt->second->collider) && (update_collider.collides_left(backgroundIt->second->collider) || update_collider.collides_right(backgroundIt->second->collider))) {
					shiftX = overlapX(update_collider, backgroundIt->second->collider, itemsIt->second->velX);
					if (shiftX != 0) {
						itemsIt->second->collider.collide_x += shiftX + itemsIt->second->velX;
						itemsIt->second->velX = 0;
					}
				}
				update_collider.collide_x -= itemsIt->second->velX; // Remove velX update and add velY
				update_collider.collide_y += itemsIt->second->velY;
				if (update_collider.collides_with(backgroundIt->second->collider) && (update_collider.collides_left(backgroundIt->second->collider) || update_collider.collides_right(backgroundIt->second->collider))) {
					shiftY = overlapY(update_collider, backgroundIt->second->collider, itemsIt->second->velY);
					if (shiftY != 0) {
						itemsIt->second->collider.collide_y += shiftY + itemsIt->second->velY;
						itemsIt->second->velY = 0;
					}
				}
			}
		}
		for (auto fireballsIt = fireballs.begin(); fireballsIt != fireballs.end(); fireballsIt++) {
			Rect_Collider update_collider = fireballsIt->second->collider;
			update_collider.collide_x += fireballsIt->second->velX;
			update_collider.collide_y += fireballsIt->second->velY;
			if (update_collider.collides_with(backgroundIt->second->collider)) {
				// Remove updated y to see if x collides
				update_collider.collide_y -= fireballsIt->second->velY;
				if (update_collider.collides_with(backgroundIt->second->collider) && (update_collider.collides_left(backgroundIt->second->collider) || update_collider.collides_right(backgroundIt->second->collider))) {
					shiftX = overlapX(update_collider, backgroundIt->second->collider, fireballsIt->second->velX);
					if (shiftX != 0) {
						fireballsIt->second->collider.collide_x += shiftX + fireballsIt->second->velX;
						fireballsIt->second->velX = 0;
					}
				}
				update_collider.collide_x -= fireballsIt->second->velX; // Remove velX update and add velY
				update_collider.collide_y += fireballsIt->second->velY;
				if (update_collider.collides_with(backgroundIt->second->collider) && (update_collider.collides_left(backgroundIt->second->collider) || update_collider.collides_right(backgroundIt->second->collider))) {
					shiftY = overlapY(update_collider, backgroundIt->second->collider, fireballsIt->second->velY);
					if (shiftY != 0) {
						fireballsIt->second->collider.collide_y += shiftY + fireballsIt->second->velY;
						fireballsIt->second->velY = 0;
					}
				}
				fireballsIt->second->collided_with(backgroundIt->second->collider); // Let fireball know that it collided with the platform
				// Platform doesnt need to know
			}
		}
	}
	for (auto itemsIt = items.begin(); itemsIt != items.end(); itemsIt++) {
		if (itemsIt->second->collider.collides_with(current_player->player_collider)) {
			itemsIt->second->collided_with(current_player->player_collider);
			current_player->collided_with(itemsIt->second->collider);
		}
	}
	for (auto enemiesIt = enemies.begin(); enemiesIt != enemies.end(); enemiesIt++) {
		if (enemiesIt->second->collider.collides_with(current_player->player_collider)) {
			enemiesIt->second->collided_with(current_player->player_collider);
			current_player->collided_with(enemiesIt->second->collider);
		}
		for (auto fireballsIt = fireballs.begin(); fireballsIt != fireballs.end(); fireballsIt++) {
			if (enemiesIt->second->collider.collides_with(fireballsIt->second->collider)) {
				enemiesIt->second->collided_with(fireballsIt->second->collider);
				fireballsIt->second->collided_with(enemiesIt->second->collider);
			}
		}
	}
}

void Background_Object::collided_with(Rect_Collider & other, Background * back) {
	if (other.collide_type == Collider_Type::PLAYER && other.collides_below(this->collider)) {
		if (this->collider.collide_type == Collider_Type::ITEM_BLOCK && contains_item) {
			contains_item = false;
			// Dispense item based on player mode
			if (back->current_player->getMode() == Player::MINI_MODE) {
				Mushroom *mush = new Mushroom(this->collider.collide_x, this->collider.collide_y - Mushroom::MUSHROOM_COLLIDER_HEIGHT);
				back->items[mush->collider.collider_id] = mush;
			}
			else {
				Fireflower *fire = new Fireflower (this->collider.collide_x, this->collider.collide_y - Fireflower::FIREFLOWER_COLLIDER_HEIGHT);
				back->items[fire->collider.collider_id] = fire;
			}
		}
	}
}


