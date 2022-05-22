#include "Banks/SetAutoBank.h"
#include <Keys.h>
#include <SpriteManager.h>
#include "ZGBMain.h"
#include "SpritePlayer.h"
#include "Pery.h"
#include <Print.h>
#include "SpriteEnemy.h"
#include <stdio.h>
#include <stdlib.h>


const UINT8 PLAYER_IDLE[] = { 1, 0 }; //The first number indicates the number of frames
const UINT8 PLAYER_WALK[] = { 2, 1, 2 };
const UINT8 PLAYER_DEAD[] = { 2, 3, 3 };

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

	// Death
	if (info->dead == 1) {
		// init death
		SetSpriteAnim(THIS, PLAYER_DEAD, 1);
		info->dead = 2;
		return;
	} else if(info->dead == 2 && THIS->anim_frame > 0) {
		// game over after animation
		SetState(StateGame);
		info->dead = 0;
		return;
	} else if (info->dead > 0) {
		// no interaction as long as death is in progress
		return;
	}

	// Movement
	info->moving = 1;

	if (KEY_PRESSED(J_UP)) {
		tile = TranslateSprite(THIS, 0, -1);
		SetSpriteAnim(THIS, PLAYER_WALK, 15);
	}
	
	if (KEY_PRESSED(J_DOWN)) {
		tile = TranslateSprite(THIS, 0, 1);
		SetSpriteAnim(THIS, PLAYER_WALK, 15);
	}
	
	if (KEY_PRESSED(J_LEFT)) {
		tile = TranslateSprite(THIS, -1, 0);
		SetSpriteAnim(THIS, PLAYER_WALK, 15);
	}
	
	if (KEY_PRESSED(J_RIGHT)) {
		tile = TranslateSprite(THIS, 1, 0);
		SetSpriteAnim(THIS, PLAYER_WALK, 15);
	}
	
	if (keys == 0) {
		SetSpriteAnim(THIS, PLAYER_IDLE, 15);
		info->moving = 0;
	}

	if (tile == MAPTILE_WALL) {
		info->dead = 1;
	}

	// Collisions
	INT16 px = (INT16)THIS->x;
	INT16 py = (INT16)THIS->y;

	SPRITEMANAGER_ITERATE(i, spr) {
		INT16 tx = (INT16)spr->x;
		INT16 ty = (INT16)spr->y;

		#ifdef CFG_ENABLE_LOGGING
		if (spr->type == SpriteEnemy) {
			DPRINT_POS(0, 0);
			DPrintf("%d %d %d %d ", px - tx, py - ty, 0, 0);
		}
		#endif

		// trigger enemy when player is nearby
		if (spr->type == SpriteEnemy &&
			(abs(px-tx) < 30 && abs(py-ty) < 30)
		) {
			ENEMY_INFO* einfo = (ENEMY_INFO*)spr->custom_data;
			einfo->moving = 1;
		}
	}
}

void DESTROY() {
}
