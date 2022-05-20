#include "Banks/SetAutoBank.h"
#include <Keys.h>
#include <SpriteManager.h>
#include "ZGBMain.h"
#include "SpritePlayer.h"
#include <Print.h>

const UINT8 anim_idle[] = { 1, 0 }; //The first number indicates the number of frames
const UINT8 anim_walk[] = { 2, 1, 2 };

void START() {
	PLAYER_INFO* info = (PLAYER_INFO*)THIS->custom_data;
	info->moving = 0;
}

void UPDATE() {
	PLAYER_INFO* info = (PLAYER_INFO*)THIS->custom_data;

	UINT8 i;
	Sprite* spr;
	UINT8 tile;
	UINT8 lastDirection;

	info->moving = 1;

	if (KEY_PRESSED(J_UP)) {
		lastDirection = J_UP;
		tile = TranslateSprite(THIS, 0, -1);
		SetSpriteAnim(THIS, anim_walk, 15);
	}
	
	if (KEY_PRESSED(J_DOWN)) {
		lastDirection = J_DOWN;
		tile = TranslateSprite(THIS, 0, 1);
		SetSpriteAnim(THIS, anim_walk, 15);
	}
	
	if (KEY_PRESSED(J_LEFT)) {
		lastDirection = J_LEFT;
		tile = TranslateSprite(THIS, -1, 0);
		SetSpriteAnim(THIS, anim_walk, 15);
	}
	
	if (KEY_PRESSED(J_RIGHT)) {
		lastDirection = J_RIGHT;
		tile = TranslateSprite(THIS, 1, 0);
		SetSpriteAnim(THIS, anim_walk, 15);
	}
	
	if (keys == 0) {
		SetSpriteAnim(THIS, anim_idle, 15);
		info->moving = 0;
	}

	SPRITEMANAGER_ITERATE(i, spr) {
		if (info->moving) {
			if (spr->type == SpriteEnemy && CheckCollision(THIS, spr)) {

				UINT8 x = 0;
				UINT8 y = 0;

				if (lastDirection == J_UP) {
					y = 5;
				}
				if (lastDirection == J_DOWN) {
					y = -5;
				}
				if (lastDirection == J_LEFT) {
					x = 5;
				}
				if (lastDirection == J_RIGHT) {
					x = -5;
				}

				tile = TranslateSprite(THIS, x, y);
			}
			if (tile == 1) {
				SetState(StateGame);
			}
		}
	}
}

void DESTROY() {
}
