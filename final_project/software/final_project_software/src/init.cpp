/*
 * init.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: joey
 */
#include "init.h"
/*
 * TODO
 * Get all the background objects from the world1 like
 * Pipes, ground, coin clocks, and other things.
 * Some blocks should spawn coins, mushrooms, and or fireflowers
 */
void setBackgroundObjectWorld1(Background * b) {
	// Set the start address and width of background sprite
	if (b == nullptr || b->collidable_background_objects == nullptr) {
		std::cout << "You tried to init a nullptr" << std::endl;
	}
	b->x = 0;
	b->y = 0;
	b->width = 3391;
	b->height = 224;
	b->start_address = ADDRESS_OFFSET; // Background is at 0x0
	// Script generated init objects for the background
	Background_Object * Item_Box1 = new Background_Object (Rect_Collider (Collider_Type::ITEM_BLOCK, 256, 136, 15, 15), true);
	b->collidable_background_objects[Item_Box1->collider.collider_id] = Item_Box1;
	Background_Object * Normal_Box2 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 320, 136, 15, 15), false);
	b->collidable_background_objects[Normal_Box2->collider.collider_id] = Normal_Box2;
	Background_Object * Normal_Box3 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 336, 136, 15, 15), false);
	b->collidable_background_objects[Normal_Box3->collider.collider_id] = Normal_Box3;
	Background_Object * Normal_Box4 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 352, 136, 15, 15), false);
	b->collidable_background_objects[Normal_Box4->collider.collider_id] = Normal_Box4;
	Background_Object * Item_Box5 = new Background_Object (Rect_Collider (Collider_Type::ITEM_BLOCK, 368, 136, 15, 15), true);
	b->collidable_background_objects[Item_Box5->collider.collider_id] = Item_Box5;
	Background_Object * Normal_Box6 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 384, 136, 15, 15), false);
	b->collidable_background_objects[Normal_Box6->collider.collider_id] = Normal_Box6;
	Background_Object * Item_Box7 = new Background_Object (Rect_Collider (Collider_Type::ITEM_BLOCK, 352, 72, 15, 15), true);
	b->collidable_background_objects[Item_Box7->collider.collider_id] = Item_Box7;
	Background_Object * Normal_Box8 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 1232, 136, 15, 15), false);
	b->collidable_background_objects[Normal_Box8->collider.collider_id] = Normal_Box8;
	Background_Object * Item_Box9 = new Background_Object (Rect_Collider (Collider_Type::ITEM_BLOCK, 1248, 136, 15, 15), true);
	b->collidable_background_objects[Item_Box9->collider.collider_id] = Item_Box9;
	Background_Object * Normal_Box10 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 1264, 136, 15, 15), false);
	b->collidable_background_objects[Normal_Box10->collider.collider_id] = Normal_Box10;
	Background_Object * Normal_Box11 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 1280, 72, 128, 15), false);
	b->collidable_background_objects[Normal_Box11->collider.collider_id] = Normal_Box11;
	Background_Object * Normal_Box12 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 1456, 72, 47, 15), false);
	b->collidable_background_objects[Normal_Box12->collider.collider_id] = Normal_Box12;
	Background_Object * Item_Box13 = new Background_Object (Rect_Collider (Collider_Type::ITEM_BLOCK, 1504, 72, 15, 15), true);
	b->collidable_background_objects[Item_Box13->collider.collider_id] = Item_Box13;
	Background_Object * Normal_Box14 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 1504, 136, 15, 15), false);
	b->collidable_background_objects[Normal_Box14->collider.collider_id] = Normal_Box14;
	Background_Object * Normal_Box15 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 1600, 136, 31, 15), false);
	b->collidable_background_objects[Normal_Box15->collider.collider_id] = Normal_Box15;
	Background_Object * Item_Box16 = new Background_Object (Rect_Collider (Collider_Type::ITEM_BLOCK, 1696, 136, 15, 15), true);
	b->collidable_background_objects[Item_Box16->collider.collider_id] = Item_Box16;
	Background_Object * Item_Box17 = new Background_Object (Rect_Collider (Collider_Type::ITEM_BLOCK, 1744, 136, 15, 15), true);
	b->collidable_background_objects[Item_Box17->collider.collider_id] = Item_Box17;
	Background_Object * Item_Box18 = new Background_Object (Rect_Collider (Collider_Type::ITEM_BLOCK, 1792, 136, 15, 15), true);
	b->collidable_background_objects[Item_Box18->collider.collider_id] = Item_Box18;
	Background_Object * Item_Box19 = new Background_Object (Rect_Collider (Collider_Type::ITEM_BLOCK, 1744, 72, 15, 15), true);
	b->collidable_background_objects[Item_Box19->collider.collider_id] = Item_Box19;
	Background_Object * Normal_Box20 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 1888, 136, 15, 15), false);
	b->collidable_background_objects[Normal_Box20->collider.collider_id] = Normal_Box20;
	Background_Object * Normal_Box21 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 1936, 72, 47, 15), false);
	b->collidable_background_objects[Normal_Box21->collider.collider_id] = Normal_Box21;
	Background_Object * Normal_Box22 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2064, 136, 31, 15), false);
	b->collidable_background_objects[Normal_Box22->collider.collider_id] = Normal_Box22;
	Background_Object * Normal_Box23 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2048, 72, 15, 15), false);
	b->collidable_background_objects[Normal_Box23->collider.collider_id] = Normal_Box23;
	Background_Object * Normal_Box24 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2096, 72, 15, 15), false);
	b->collidable_background_objects[Normal_Box24->collider.collider_id] = Normal_Box24;
	Background_Object * Item_Box25 = new Background_Object (Rect_Collider (Collider_Type::ITEM_BLOCK, 2080, 72, 15, 15), true);
	b->collidable_background_objects[Item_Box25->collider.collider_id] = Item_Box25;
	Background_Object * Item_Box26 = new Background_Object (Rect_Collider (Collider_Type::ITEM_BLOCK, 2064, 72, 15, 15), true);
	b->collidable_background_objects[Item_Box26->collider.collider_id] = Item_Box26;
	Background_Object * Shiny_Box27 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2144, 184, 15, 15), false);
	b->collidable_background_objects[Shiny_Box27->collider.collider_id] = Shiny_Box27;
	Background_Object * Shiny_Box28 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2160, 168, 15, 31), false);
	b->collidable_background_objects[Shiny_Box28->collider.collider_id] = Shiny_Box28;
	Background_Object * Shiny_Box29 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2176, 152, 15, 47), false);
	b->collidable_background_objects[Shiny_Box29->collider.collider_id] = Shiny_Box29;
	Background_Object * Shiny_Box30 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2192, 136, 15, 63), false);
	b->collidable_background_objects[Shiny_Box30->collider.collider_id] = Shiny_Box30;
	Background_Object * Shiny_Box31 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2240, 136, 15, 63), false);
	b->collidable_background_objects[Shiny_Box31->collider.collider_id] = Shiny_Box31;
	Background_Object * Shiny_Box32 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2256, 152, 15, 47), false);
	b->collidable_background_objects[Shiny_Box32->collider.collider_id] = Shiny_Box32;
	Background_Object * Shiny_Box33 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2272, 168, 15, 31), false);
	b->collidable_background_objects[Shiny_Box33->collider.collider_id] = Shiny_Box33;
	Background_Object * Shiny_Box34 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2288, 184, 15, 15), false);
	b->collidable_background_objects[Shiny_Box34->collider.collider_id] = Shiny_Box34;
	Background_Object * Shiny_Box35 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2368, 184, 15, 15), false);
	b->collidable_background_objects[Shiny_Box35->collider.collider_id] = Shiny_Box35;
	Background_Object * Shiny_Box36 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2384, 168, 15, 31), false);
	b->collidable_background_objects[Shiny_Box36->collider.collider_id] = Shiny_Box36;
	Background_Object * Shiny_Box37 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2400, 152, 15, 47), false);
	b->collidable_background_objects[Shiny_Box37->collider.collider_id] = Shiny_Box37;
	Background_Object * Shiny_Box38 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2416, 136, 15, 63), false);
	b->collidable_background_objects[Shiny_Box38->collider.collider_id] = Shiny_Box38;
	Background_Object * Shiny_Box39 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2432, 136, 15, 63), false);
	b->collidable_background_objects[Shiny_Box39->collider.collider_id] = Shiny_Box39;
	Background_Object * Shiny_Box40 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2480, 136, 15, 63), false);
	b->collidable_background_objects[Shiny_Box40->collider.collider_id] = Shiny_Box40;
	Background_Object * Shiny_Box41 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2496, 152, 15, 47), false);
	b->collidable_background_objects[Shiny_Box41->collider.collider_id] = Shiny_Box41;
	Background_Object * Shiny_Box42 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2512, 168, 15, 31), false);
	b->collidable_background_objects[Shiny_Box42->collider.collider_id] = Shiny_Box42;
	Background_Object * Shiny_Box43 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2528, 184, 15, 15), false);
	b->collidable_background_objects[Shiny_Box43->collider.collider_id] = Shiny_Box43;
	Background_Object * Normal_Box44 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2688, 136, 31, 15), false);
	b->collidable_background_objects[Normal_Box44->collider.collider_id] = Normal_Box44;
	Background_Object * Normal_Box45 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2736, 136, 15, 15), false);
	b->collidable_background_objects[Normal_Box45->collider.collider_id] = Normal_Box45;
	Background_Object * Item_Box46 = new Background_Object (Rect_Collider (Collider_Type::ITEM_BLOCK, 2720, 136, 15, 15), true);
	b->collidable_background_objects[Item_Box46->collider.collider_id] = Item_Box46;
	Background_Object * Shiny_Box47 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2896, 184, 15, 15), false);
	b->collidable_background_objects[Shiny_Box47->collider.collider_id] = Shiny_Box47;
	Background_Object * Shiny_Box48 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2912, 168, 15, 31), false);
	b->collidable_background_objects[Shiny_Box48->collider.collider_id] = Shiny_Box48;
	Background_Object * Shiny_Box49 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2928, 152, 15, 47), false);
	b->collidable_background_objects[Shiny_Box49->collider.collider_id] = Shiny_Box49;
	Background_Object * Shiny_Box50 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2944, 136, 15, 63), false);
	b->collidable_background_objects[Shiny_Box50->collider.collider_id] = Shiny_Box50;
	Background_Object * Shiny_Box51 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2960, 120, 15, 79), false);
	b->collidable_background_objects[Shiny_Box51->collider.collider_id] = Shiny_Box51;
	Background_Object * Shiny_Box52 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2976, 104, 15, 97), false);
	b->collidable_background_objects[Shiny_Box52->collider.collider_id] = Shiny_Box52;
	Background_Object * Shiny_Box53 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2992, 88, 15, 113), false);
	b->collidable_background_objects[Shiny_Box53->collider.collider_id] = Shiny_Box53;
	Background_Object * Shiny_Box54 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 3008, 72, 15, 129), false);
	b->collidable_background_objects[Shiny_Box54->collider.collider_id] = Shiny_Box54;
	Background_Object * Shiny_Box55 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 3024, 72, 15, 149), false);
	b->collidable_background_objects[Shiny_Box55->collider.collider_id] = Shiny_Box55;
	Background_Object * Pipe56 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 448, 168, 32, 32), false);
	b->collidable_background_objects[Pipe56->collider.collider_id] = Pipe56;
	Background_Object * Pipe57 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 608, 151, 32, 48), false);
	b->collidable_background_objects[Pipe57->collider.collider_id] = Pipe57;
	Background_Object * Pipe58 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 736, 135, 32, 64), false);
	b->collidable_background_objects[Pipe58->collider.collider_id] = Pipe58;
	Background_Object * Pipe59 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 912, 135, 32, 64), false);
	b->collidable_background_objects[Pipe59->collider.collider_id] = Pipe59;
	Background_Object * Pipe60 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2608, 168, 32, 32), false);
	b->collidable_background_objects[Pipe60->collider.collider_id] = Pipe60;
	Background_Object * Pipe61 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2864, 168, 32, 32), false);
	b->collidable_background_objects[Pipe61->collider.collider_id] = Pipe61;
	Background_Object * Ground62 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 0, 200, 1103, 23), false);
	b->collidable_background_objects[Ground62->collider.collider_id] = Ground62;
	Background_Object * Ground63 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 1136, 200, 239, 23), false);
	b->collidable_background_objects[Ground63->collider.collider_id] = Ground63;
	Background_Object * Ground64 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 1424, 200, 1023, 23), false);
	b->collidable_background_objects[Ground64->collider.collider_id] = Ground64;
	Background_Object * Ground65 = new Background_Object (Rect_Collider (Collider_Type::PLATFORM_UNBREAKABLE, 2480, 200, 910, 23), false);
	b->collidable_background_objects[Ground65->collider.collider_id] = Ground65;




}



