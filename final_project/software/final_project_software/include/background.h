/*
 * background.h
 *
 *  Created on: Dec 3, 2018
 *      Author: joey
 */

#ifndef INCLUDE_BACKGROUND_H_
#define INCLUDE_BACKGROUND_H_
#include <vector>
#include "colliders.h"
#include "item.h"
using namespace std;

class Background : public Sprite {
	// Function to scroll background either right or left.
public:
	void scrollBackgroundX (int moveAmount);
	void drawBackground();
	void drawWindow(); // Draws all the sprites to the screen after the background
	void updateBackground();
	void initBackground(); // Initializes everything on the background
	uint16_t deadZoneLeft; // The left and right of the dead zone.
	uint16_t deadZoneRight;
	uint16_t maxScrollSpeed;
	// Center of the window in reference from (0,0) NOT X
	uint16_t screenCenterX;
	uint16_t window_width; // Max width in both dimensions
	uint16_t window_height;
	// Returns a rect_collider if an item collides with the player
	Rect_Collider itemCollidedWithPlayer();
	// Returns a rect_collider if an enemy collides with the player
	Rect_Collider enemyCollidedWithPlayer();
	// Remove said item from rendering
	void removeItemByCollider(Rect_Collider & collider);
	void removeEnemyByCollider(Rect_Collider & collider);
	Rect_Collider collidedWithEnemy();
	// No need to notify for platforms. Background will handle those physics
	Background(); // Init background with a player
	~Background();
	// On any movement of the background these must be updated too
	map<uint64_t, Background_Object*> collidable_background_objects; // Objects that aren't seperate sprites, but are still collidable on the map; These update every frame with the background
	Player * current_player;
	map<uint64_t, Enemy*> enemies;
	map<uint64_t, Item*> items;
	map<uint64_t, Fireball*> fireballs;
};

class Background_Object : public Background_Sprite {
	Rect_Collider collider;
	bool contains_coins;
	uint16_t coin_amount;
	bool contains_item;
};


#endif /* INCLUDE_BACKGROUND_H_ */
