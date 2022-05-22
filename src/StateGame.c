#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include <Print.h>
#include "SpriteEnemy.h"


IMPORT_MAP(map);
IMPORT_TILES(font);

UINT8 collision_tiles[] = { 1, 0 };

void START() {
	#ifdef CFG_ENABLE_LOGGING
	INIT_CONSOLE(font, 3, 2);
	#endif
	
	scroll_target = SpriteManagerAdd(SpritePlayer, 20, 100);
	InitScroll(BANK(map), &map, collision_tiles, 0);
	CreateEnemy(50, 95, -1, 0);
	CreateEnemy(97, 75, 0, 1);
}

void UPDATE() {
}

void CreateEnemy(UINT16 x, UINT16 y, INT8 vx, INT8 vy) {
	Sprite *spr = SpriteManagerAdd(SpriteEnemy, x, y);
	ENEMY_INFO* data = (ENEMY_INFO*)spr->custom_data;
	data->vx = vx;
	data->vy = vy;
}
