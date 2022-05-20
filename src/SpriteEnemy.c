#include "Banks/SetAutoBank.h"
#include <Keys.h>
#include <SpriteManager.h>
#include "ZGBMain.h"
#include "SpritePlayer.h"
#include <Print.h>
#include "SpriteEnemy.h"


void START() {
	ENEMY_INFO* data = (ENEMY_INFO*)THIS->custom_data;
	data->vy = 1;
}

void UPDATE() {
	UINT8 i;
	Sprite* spr;
	UINT8 lastDirection;
	UINT8 tile;

	ENEMY_INFO* data = (ENEMY_INFO*)THIS->custom_data;
	if (TranslateSprite(THIS, 0, data->vy)) {
		data->vy = -data->vy;
	}
	
	/*
	DPRINT_POS(0, 0);
	DPrintf("x:%d y:%d  ", data->vy, 0);
	*/

	SPRITEMANAGER_ITERATE(i, spr) {
		if (spr->type == SpritePlayer && CheckCollision(THIS, spr)) {
			PLAYER_INFO* info = (PLAYER_INFO*)spr->custom_data;

			if (!info->moving) {
				UINT8 y = 0;

				if (data->vy > 0) {
					y = 5;
				}
				else {
					y = -5;
				}

				tile = TranslateSprite(spr, 0, y);
			}
		}
		if (tile == 1) {
			SetState(StateGame);
		}
	}
}

void DESTROY() {
}