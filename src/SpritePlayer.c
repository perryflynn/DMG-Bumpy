#include "Banks/SetAutoBank.h"
#include <Keys.h>
#include <SpriteManager.h>
#include "ZGBMain.h"
#include "SpritePlayer.h"
#include "Pery.h"
#include <Print.h>
#include "SpriteEnemy.h"


const UINT8 PLAYER_IDLE[] = { 1, 0 }; //The first number indicates the number of frames
const UINT8 PLAYER_WALK[] = { 2, 1, 2 };
const UINT8 PLAYER_DEAD[] = { 1, 3 };

void START() {
	PLAYER_INFO* info = (PLAYER_INFO*)THIS->custom_data;
	info->moving = 0;
	info->dead = 0;
}

void UPDATE() {
	PLAYER_INFO* info = (PLAYER_INFO*)THIS->custom_data;

	UINT8 i;
	Sprite* spr;
	UINT8 tile = 0;
	UINT8 lastDirection = 0;

	// Dead
	if (info->dead) {
		SetState(StateGame);
		SetSpriteAnim(THIS, PLAYER_DEAD, 15);
		info->dead = 0;
		return;
	}

	// Movement
	info->moving = 1;

	if (KEY_PRESSED(J_UP)) {
		lastDirection = J_UP;
		tile = TranslateSprite(THIS, 0, -1);
		SetSpriteAnim(THIS, PLAYER_WALK, 15);
	}
	
	if (KEY_PRESSED(J_DOWN)) {
		lastDirection = J_DOWN;
		tile = TranslateSprite(THIS, 0, 1);
		SetSpriteAnim(THIS, PLAYER_WALK, 15);
	}
	
	if (KEY_PRESSED(J_LEFT)) {
		lastDirection = J_LEFT;
		tile = TranslateSprite(THIS, -1, 0);
		SetSpriteAnim(THIS, PLAYER_WALK, 15);
	}
	
	if (KEY_PRESSED(J_RIGHT)) {
		lastDirection = J_RIGHT;
		tile = TranslateSprite(THIS, 1, 0);
		SetSpriteAnim(THIS, PLAYER_WALK, 15);
	}
	
	if (keys == 0) {
		SetSpriteAnim(THIS, PLAYER_IDLE, 15);
		info->moving = 0;
	}

	// Collisions
	SPRITEMANAGER_ITERATE(i, spr) {
		// only when the player moves
		// see the enemy sprite
		if (info->moving) {
			UINT8 coltile = PERY_PLAYERCOLLISION(SpriteEnemy, THIS, lastDirection, spr);

			PERY_LOGXY(coltile, 0);

			if (tile == MAPTILE_WALL || coltile == MAPTILE_WALL) {
				info->dead = 1;
			}
		}

		if (lastDirection && spr->type == SpriteEnemy) {
			ENEMY_INFO* einfo = (ENEMY_INFO*)spr->custom_data;
			einfo->moving = 1;
		}
	}
}

void DESTROY() {
}
