#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include <Print.h>


IMPORT_MAP(map);
IMPORT_TILES(font);

UINT8 collision_tiles[] = { 1, 0 };

void START() {
	#ifdef CFG_ENABLE_LOGGING
	INIT_CONSOLE(font, 3, 2);
	#endif
	
	scroll_target = SpriteManagerAdd(SpritePlayer, 20, 50);
	InitScroll(BANK(map), &map, collision_tiles, 0);
	SpriteManagerAdd(SpriteEnemy, 70, 10);
	SpriteManagerAdd(SpriteEnemy, 70, 30);
	SpriteManagerAdd(SpriteEnemy, 70, 50);
	SpriteManagerAdd(SpriteEnemy, 70, 70);
	SpriteManagerAdd(SpriteEnemy, 70, 90);
	SpriteManagerAdd(SpriteEnemy, 90, 20);
	SpriteManagerAdd(SpriteEnemy, 90, 40);
	SpriteManagerAdd(SpriteEnemy, 90, 60);
	SpriteManagerAdd(SpriteEnemy, 90, 80);
	SpriteManagerAdd(SpriteEnemy, 90, 100);
}

void UPDATE() {
}
