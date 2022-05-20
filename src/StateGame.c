#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include <Print.h>


IMPORT_MAP(map);
IMPORT_TILES(font);

UINT8 collision_tiles[] = { 1, 0 };

void START() {
	//INIT_CONSOLE(font, 3, 2);
	
	scroll_target = SpriteManagerAdd(SpritePlayer, 50, 50);
	InitScroll(BANK(map), &map, collision_tiles, 0);
	SpriteManagerAdd(SpriteEnemy, 70, 40);
	SpriteManagerAdd(SpriteEnemy, 70, 80);
}

void UPDATE() {
}
