#include "Banks/SetAutoBank.h"
#include <Keys.h>
#include <SpriteManager.h>
#include "ZGBMain.h"
#include "SpritePlayer.h"
#include <Print.h>
#include "SpriteEnemy.h"
#include "Pery.h"


void START() {
	ENEMY_INFO* data = (ENEMY_INFO*)THIS->custom_data;
	data->vy = 1;
}

void UPDATE() {
	UINT8 i;
	Sprite* spr;
	UINT8 tile = 0;

	ENEMY_INFO* data = (ENEMY_INFO*)THIS->custom_data;
	if (TranslateSprite(THIS, 0, data->vy)) {
		data->vy = -data->vy;
	}
	
	SPRITEMANAGER_ITERATE(i, spr) {
		if (spr->type == SpritePlayer) {
			PLAYER_INFO* info = (PLAYER_INFO*)spr->custom_data;
			 
			// only when the player is not moves
			// see player sprite
			if (!info->moving) {
				// use the player collition function to
				// bounce the player when the enemy runs into the player
				UINT8 dir = data->vy > 0 ? J_UP : J_DOWN;
				tile = PERY_PLAYERCOLLISION(SpriteEnemy, spr, dir, THIS);
			}

			if (tile == MAPTILE_WALL) {
				info->dead = 1;
			}
		}
	}
}

void DESTROY() {
}