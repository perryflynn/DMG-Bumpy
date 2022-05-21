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
	data->vy = -1;
	data->vx = 0;
	data->moving = 0;
}

void UPDATE() {
	UINT8 i;
	Sprite* spr;

	ENEMY_INFO* data = (ENEMY_INFO*)THIS->custom_data;
	if (data->moving && TranslateSprite(THIS, data->vx, data->vy)) {
		data->vy = -data->vy;
		data->vx = -data->vx;
	}
	
	SPRITEMANAGER_ITERATE(i, spr) {
		if (spr->type == SpritePlayer) {
			PLAYER_INFO* info = (PLAYER_INFO*)spr->custom_data;
			UINT8 tile = 0;

			// only when the player is not moves
			// see player sprite
			if (info->dead <= 0) {
				// use the player collition function to
				// bounce the player when the enemy runs into the player
				UBYTE dir = 0;
				dir = data->vx != 0 ? (data->vx > 0 ? dir | J_LEFT : dir | J_RIGHT) : dir;
				dir = data->vy != 0 ? (data->vy > 0 ? dir | J_UP : dir | J_DOWN) : dir;
				
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
