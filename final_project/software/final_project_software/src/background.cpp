/*
 * background.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: joey
 */
#include "background.h"
#include "config.h"

Background_Object::Background_Object(Rect_Collider collider, bool contains_item) {
	this->collider = collider;
	this->contains_item = contains_item;
}

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
		if (it->second != nullptr)
			it->second->getCurrentSprite().drawSprite();
	}
	// Draw all the items on the screen
	for (auto it = items.begin(); it != items.end(); it++) {
		if (it->second != nullptr)
			it->second->getCurrentSprite().drawSprite();
	}
	// Draw all fireballs thrown by the player
	for (auto it = fireballs.begin(); it != fireballs.end(); it++) {
		if (it->second != nullptr)
			it->second->getCurrentSprite().drawSprite();
	}
	// Just draw the player
	if (current_player != nullptr)
		current_player->getCurrentSprite().drawSprite();
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
	for (auto it = enemies.begin(); it != enemies.end();) {
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
	for (auto it = items.begin(); it != items.end(); it++) {
		if (it->second == nullptr || outOfBounds(it->second->collider)) {
			it = items.erase(it);
		}
		else {
			it->second->gravity();
			it->second->update();
			it++;
		}
	}
	for (auto it = enemies.begin(); it != enemies.end();) {
		if (it->second == nullptr || outOfBounds(it->second->collider)) {
			it = enemies.erase(it);
		}
		else {
			it->second->gravity();
			it->second->update();
			it++;
		}
	}
	for (auto it = fireballs.begin(); it != fireballs.end(); it++) {
		if (it->second == nullptr || outOfBounds(it->second->collider)) {
			it = fireballs.erase(it);
		}
		else {
			it->second->gravity();
			it->second->update();
			it++;
		}
	}
	current_player->gravity();
	current_player->update();
	resolveCollisions();
	drawWindow();
}



// Checks and update all the collisions
void Background::resolveCollisions() {
//	map<uint64_t, Background_Object*> collidable_background_objects; // Objects that aren't seperate sprites, but are still collidable on the map; These update every frame with the background
//	Player * current_player;
//	map<uint64_t, Enemy*> enemies;
//	map<uint64_t, Item*> items;
//	map<uint64_t, Fireball*> fireballs;
	int16_t shiftX = 0;
	int16_t shiftY = 0;
	for (auto backgroundIt = collidable_background_objects.begin(); backgroundIt != collidable_background_objects.end(); backgroundIt++) {
		if (backgroundIt->second == nullptr) continue;
		for (auto enemiesIt = enemies.begin(); enemiesIt != enemies.end(); enemiesIt++) {
			if (!enemiesIt->second->noCollide && enemiesIt->second->collider.collides_with(backgroundIt->second->collider)) {
				shiftX = overlapX(enemiesIt->second->collider, backgroundIt->second->collider);
				shiftY = overlapY(enemiesIt->second->collider, backgroundIt->second->collider);
				if (shiftX != 0) {
					enemiesIt->second->collider.collide_x += shiftX;
					enemiesIt->second->velX = 0;
				}
				if (shiftY != 0) {
					enemiesIt->second->collider.collide_y += shiftY;
					enemiesIt->second->velY = 0;
				}
			}
		}
		if (current_player != nullptr && current_player->player_collider.collides_with(backgroundIt->second->collider) && !current_player->noCollide) {
			shiftX = overlapX(current_player->player_collider, backgroundIt->second->collider);
			shiftY = overlapY(current_player->player_collider, backgroundIt->second->collider);
			if (shiftX != 0) {
				current_player->player_collider.collide_x += shiftX;
				current_player->velX = 0;
			}
			if (shiftY != 0) {
				current_player->player_collider.collide_y += shiftY;
				current_player->velY = 0;
			}
			// Pass in background too
			backgroundIt->second->collided_with(current_player->player_collider, this);
		}
		for (auto itemsIt = items.begin(); itemsIt != items.end(); itemsIt++) {
			if (itemsIt->second->collider.collides_with(backgroundIt->second->collider)) {
				shiftX = overlapX(itemsIt->second->collider, backgroundIt->second->collider);
				shiftY = overlapY(itemsIt->second->collider, backgroundIt->second->collider);
				if (shiftX != 0) {
					itemsIt->second->collider.collide_x += shiftX;
					itemsIt->second->velX = 0;
				}
				if (shiftY != 0) {
					itemsIt->second->collider.collide_y += shiftY;
					itemsIt->second->velY = 0;
				}
			}
		}
		for (auto fireballsIt = fireballs.begin(); fireballsIt != fireballs.end(); fireballsIt++) {
			if (fireballsIt->second->collider.collides_with(backgroundIt->second->collider)) {
				shiftX = overlapX(fireballsIt->second->collider, backgroundIt->second->collider);
				shiftY = overlapY(fireballsIt->second->collider, backgroundIt->second->collider);
				if (shiftX != 0) {
					fireballsIt->second->collider.collide_x += shiftX;
					fireballsIt->second->velX = 0;
				}
				if (shiftY != 0) {
					fireballsIt->second->collider.collide_y += shiftY;
					fireballsIt->second->velY = 0;
				}
				fireballsIt->second->collided_with(backgroundIt->second->collider); // Let fireball know that it collided with the platform
				// Platform doesnt need to know
			}
		}
	}
	for (auto itemsIt = items.begin(); itemsIt != items.end(); itemsIt++) {
		if (itemsIt->second->collider.collides_with(current_player->player_collider)) {
			itemsIt->second->collided_with(current_player->player_collider);
			current_player->player_collider(itemsIt->second->collider);
		}
	}
	for (auto enemiesIt = enemies.begin(); enemiesIt != enemies.end(); enemiesIt++) {
		if (enemiesIt->second->collider.collides_with(current_player->player_collider)) {
			enemiesIt->second->collided_with(current_player->player_collider);
			current_player->collided_with(enemiesIt->second->collider);
		}
		for (auto fireballsIt = fireballs.begin(); fireballsIt != fireballs.end(); fireballsIt) {
			if (enemiesIt->second->collider.collides_with(fireballsIt->second->collider)) {
				enemiesIt->second->collided_with(fireballsIt->second->collider);
				fireballsIt->second->collided_with(enemiesIt->second->collider);
			}
		}
	}
}

void Background_Object::collided_with(Rect_Collider & other, Background * back) {
	if (other.collider_type == Collider_Type::PLAYER && other.collides_below(this->collider)) {
		if (this->collider.collider_type == Collider_Type::ITEM_BLOCK && contains_item) {
			contains_item = false;
			// Dispense item based on player mode
			if (back->current_player->current_anim_mode == Player::MINI_MODE) {
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


