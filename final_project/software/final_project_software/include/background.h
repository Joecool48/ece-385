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
#include <map>
#include "../include/config.h"
#include "../include/player.h"
#include "../include/enemies.h"

using namespace std;

class Background_Object;
class Enemy;
class Player;
class Item;
class Fireball;


class Background : public Sprite {
	// Function to scroll background either right or left.
public:

	uint16_t x, y;
	void scrollBackgroundX (int moveAmount);
	void drawBackground();
	void drawWindow(); // Draws all the sprites to the screen after the background
	void updateBackground(); // Calls update on everything, and cleans up things out of bounds. Resolves collisions, draws background, and does physics
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
	void removeItemById(uint64_t id);
	void removeEnemyById(uint64_t id);
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
	void setPlayer (Player *curr_player);
	bool outOfBounds(Rect_Collider & other);
	void resolveCollisions(); // Function called after update to resolve collisions
	bool offScreen(Rect_Collider & other); // Returns true only if the rect collider is not visible within the current background bounds

};

class Background_Object {
public:
	Rect_Collider collider;
	Background_Object (Rect_Collider collider, bool contains_item);
	// TODO Implement collided_with for background objects
	void collided_with(Rect_Collider & other, Background * back); // TODO implement collider method to do stuff when it collides
	bool contains_item;
};

#endif /* INCLUDE_BACKGROUND_H_ */
