/*
 * Sprite.h
 *
 *  Created on: Nov 27, 2018
 *      Author: joey
 */

#ifndef INCLUDE_GAME_CLASSES_H_
#define INCLUDE_GAME_CLASSES_H_

#include <vector>
#include <stdint.h>
#include <map>
#include "anim_num.h"
using namespace std;
// Class to store information about a image. Will be copied from this to create other sprites.
class Image {
public:
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t height;
	uint32_t start_address;
	virtual ~Image () = 0;
};

// Class for each spriteframe
class Sprite : public Image {
public:
	bool isVisible;
	void drawSprite();
};
// Sprite with no image. Just to keep track of its collisions and movement
class Background_Sprite {
public:
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t height;
};

// Animator which is the base class for anything that moves
class Sprite_Animator {
protected:
	uint16_t x;
	uint16_t y;
	uint16_t wait_frames; // When set the state machine will continue in its current state until wait_frames is 0
	virtual ~Sprite_Animator();
	bool pause_animation; // Set to true if animations are paused
	uint16_t current_frame_in_state;
	uint16_t current_anim_state;
	uint16_t current_anim_mode;
	Sprite_Animator ();
	virtual void animatorSetup() = 0;
	// State first, then mode map to sprites
	map <uint16_t, map<uint16_t, vector<Sprite>>> state_mode_to_frames_map; // Different subclasses must define own states
	// Change the animation type
	void setState(uint16_t state);
	void setMode(uint16_t mode);
	void advanceFrame();
	Sprite getCurrentSprite();

};

// Represents a playable character
class Player : Sprite_Animator {
	Rect_Collider player_collider;
	enum modes {NORMAL_MODE = 0, MINI_MODE}; // Mario power up states
	enum states {IDLE = 0, WALKING, JUMPING, LANDING, RUNNING, HIT_BLOCK};

	Player();
	void animatorSetup(); // Initialize all the animation states of the sprite
	void drawPlayer();
	void player_update();
};

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
	Background(Player * p); // Init background with a player
	~Background();
private:
	vector<Background_Object*> collidable_background_objects; // Objects that aren't seperate sprites, but are still collidable on the map; These update every frame with the background
	Player * current_player;
	vector<Enemy*> enemies;
	vector<Item*> items;
};

// Base class for enemy AI
class Brain {
	virtual ~Brain();
	Brain();
};

/*
 * TODO:
 * Create the fundamental AI for enemies
 */
class Enemy : public Sprite_Animator {
	Rect_Collider collider;
	Brain brain;
};

class Item : public Sprite_Animator {
	bool isCollectable;
	Item();
};

class Background_Object : public Background_Sprite {
	Collidable *collider;
};
#endif /* INCLUDE_GAME_CLASSES_H_ */
