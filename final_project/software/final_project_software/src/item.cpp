/*
 * item.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: joey
 */
#include "../include/item.h"

const float Fireball::FIREBALL_SPEED_BOUNCE = .5;
const float Mushroom::MUSHROOM_TRAVEL_SPEED = .2;
const float Item::ITEM_START_FRAME = 0;

Item::Item (uint16_t start_x, uint16_t start_y, uint16_t mode, uint16_t state, float start_frame, Rect_Collider rect) : Sprite_Animator (mode, state, start_frame){
	collider = rect;
	current_background = nullptr;
}
Fireflower::Fireflower (uint16_t start_x, uint16_t start_y) : Item (start_x, start_y, Item::ITEM_MODE, FIREFLOWER_EXIST, Item::ITEM_START_FRAME, Rect_Collider(Collider_Type::FIREFLOWER, start_x, start_y, FIREFLOWER_COLLIDER_WIDTH, FIREFLOWER_COLLIDER_HEIGHT)) {}
Mushroom::Mushroom (uint16_t start_x, uint16_t start_y) : Item (start_x, start_y, Item::ITEM_MODE, MUSHROOM_MOVE, Item::ITEM_START_FRAME, Rect_Collider(Collider_Type::MUSHROOM, start_x, start_y, MUSHROOM_COLLIDER_WIDTH, MUSHROOM_COLLIDER_HEIGHT)) {
	travelDir = rand() % 2;
}

Sprite_Animator::~Sprite_Animator() {

}

Fireball::Fireball (uint16_t start_x, uint16_t start_y, Background * b) : Sprite_Animator (Item::ITEM_MODE, STATE_BOUNCE, Item::ITEM_START_FRAME){
	if (b == nullptr) {
		std::cout << "Fireball wont be displayed. Null background!" << std::endl;
		return;
	}
	collider = Rect_Collider(Collider_Type::FIREBALL, start_x, start_y, FIREBALL_COLLIDER_WIDTH, FIREBALL_COLLIDER_HEIGHT);
	velX = 0;
	velY = 0;
	current_background = b;
}
//Coin::Coin (uint16_t start_x, uint16_t start_y) : Sprite_Animator (start_x, start_y, Item::ITEM_MODE, Item::ITEM_STATE, Item::ITEM_START_FRAME), Item::collider(Rect_Collider(Collider_Type::COIN, start_x, start_y, COIN_COLLIDER_WIDTH, COIN_COLLIDER_HEIGHT)) {
//}
void Item::setBackground(Background *b) {
	current_background = b;
}

void Fireball::setToExplode() {
	current_anim_state = STATE_EXPLODE;
}

/*
 *
 * Collision functions for special effects
 */
void Fireball::collided_with(Rect_Collider & other) {
	// Make sure the fireball either hits the side, or it hits an enemy before it is destroyed. Background will recycle outside objects
	if ((Collidable::cantGoThrough(other.collide_type) && !collider.collides_above(other)) || Collidable::isEnemy(other.collide_type)) {
		setToExplode();
	}
}
/*
 * Small state machine for fireball animation
 */
void Fireball::update() {
	current_anim_mode = Item::ITEM_MODE;
	if (wait_frames) {
		wait_frames--;
		return;
	}
	switch (current_anim_state) {
	case STATE_BOUNCE:
		// Does basically nothing. collided_with will set state to explode when a collision occurs
		break;
	case STATE_EXPLODE:
		wait_frames = EXPLODE_FRAMES;
		current_anim_state = STATE_DESTROY;
		break;
	case STATE_DESTROY:
		// Delete the object then remove it from the background. This will decrease map size too
		destroyInBackground();
		break;
	default:
		std::cout << "Unrecognized state in Fireball::update" << std::endl;
	}
}

void Fireball::destroyInBackground() {
	if (current_background == nullptr || current_background->fireballs.find(collider.collider_id) == current_background->fireballs.end()) {
		std::cout << "Problem finding the fireball to destroy" << std::endl;
		return;
	}
	delete current_background->fireballs[collider.collider_id];
	current_background->fireballs.erase(collider.collider_id);
}

void Item::destroyInBackground() {
	if (current_background == nullptr || current_background->items.find(collider.collider_id) == current_background->items.end()) {
		std::cout << "Problem finding the Item to destroy" << std::endl;
		return;
	}
	delete current_background->items[collider.collider_id];
	current_background->items.erase(collider.collider_id);
}

/*
 *
 * Add animator setup for frames
 */
void Fireball::animatorSetup() {
	// Items dont have modes, or rather I'm not making them, so ITEM_MODE is default
	Sprite fireball_bounce(18, 17, ADDRESS_OFFSET + 774146);
	Sprite fireball_explode_1(18, 17, ADDRESS_OFFSET + 773840);
	Sprite fireball_explode_2(16, 17, ADDRESS_OFFSET + 775492);
	state_mode_to_frames_map[STATE_BOUNCE][Item::ITEM_MODE].push_back(fireball_bounce);
	state_mode_to_frames_map[STATE_EXPLODE][Item::ITEM_MODE].push_back(fireball_explode_1);
	state_mode_to_frames_map[STATE_EXPLODE][Item::ITEM_MODE].push_back(fireball_explode_2);

}
/*
 * Defines how the Mushroom switches directions when hitting a object from the left or right. Only needs to know for player
 * collisions and platform collisions
 */
void Mushroom::collided_with(Rect_Collider & other) {
	if (Collidable::cantGoThrough(other.collide_type) && !collider.collides_above(other)) {
		travelDir = !travelDir;
	}
	// Player checks if he got the sprite
}
/*
 * Simple update to determine which way it should go
 */
void Mushroom::update() {
	current_anim_mode = ITEM_MODE;
	if (wait_frames) {
		wait_frames--;
		return;
	}
	switch (current_anim_state) {
	case MUSHROOM_MOVE:
		if (travelDir == RIGHT) velX = MUSHROOM_TRAVEL_SPEED;
		else velX = -MUSHROOM_TRAVEL_SPEED;
		break;
	case MUSHROOM_DESTROY:
		destroyInBackground();
		break;
	}
}
/*
 *
 * Init animator setup for Mushroom sprite
 */
void Mushroom::animatorSetup() {
	Sprite mushroom_frame_1(16, 17, ADDRESS_OFFSET + 774964);
	state_mode_to_frames_map[MUSHROOM_MOVE][ITEM_MODE].push_back(mushroom_frame_1);
}

/*
 *
 * Fireflower update function super simple.
 */
void Fireflower::update() {
	if (wait_frames) {
		wait_frames--;
		return;
	}
	current_anim_mode = ITEM_MODE;
	switch (current_anim_state) {
	// Simply exist. That is all we can ask of you
	case FIREFLOWER_EXIST:
		break;
	case FIREFLOWER_DESTROY:
		destroyInBackground();
	}
}

/*
 * Initialize fireflower sprites in animSetup
 */
void Fireflower::animatorSetup() {
	Sprite fireflower_1 (16, 16, ADDRESS_OFFSET + 774452);
	Sprite fireflower_2(16, 16, ADDRESS_OFFSET + 774708);
	Sprite fireflower_3(16, 16, ADDRESS_OFFSET + 773584);
	Sprite fireflower_4(16, 16, ADDRESS_OFFSET + 774236);
	state_mode_to_frames_map[FIREFLOWER_EXIST][ITEM_MODE].push_back(fireflower_1);
	state_mode_to_frames_map[FIREFLOWER_EXIST][ITEM_MODE].push_back(fireflower_2);
	state_mode_to_frames_map[FIREFLOWER_EXIST][ITEM_MODE].push_back(fireflower_3);
	state_mode_to_frames_map[FIREFLOWER_EXIST][ITEM_MODE].push_back(fireflower_4);
}
// This method does nothing and is never called. Just there so the pure virtual is implemented
void Fireflower::collided_with(Rect_Collider &other) {

}

void Item::gravity() {
	velY += GRAVITY_STRENGTH;
	collider.collide_y += velY;
	collider.collide_x += velX;
}

void Fireball::gravity() {
	collider.collide_y += velY;
	collider.collide_x += velX;
	velY += GRAVITY_STRENGTH;
}

void Item::draw() {
	Sprite s = getCurrentSprite();
	// Update the rect collider!!!
	collider.collide_width = s.width;
	collider.collide_height = s.height;
	s.drawSprite(collider.collide_x, collider.collide_y, flipped_mode ? FLIP_HORIZONTAL : NO_FLIP, isVisible); // Gets the current player sprite and draws
}

void Fireball::draw() {
	Sprite s = getCurrentSprite();
	// Update the rect collider!!!
	collider.collide_width = s.width;
	collider.collide_height = s.height;
	s.drawSprite(collider.collide_x, collider.collide_y, flipped_mode ? FLIP_HORIZONTAL : NO_FLIP, isVisible); // Gets the current player sprite and draws
}

