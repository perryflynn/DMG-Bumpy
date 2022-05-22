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
	data->pauseCollision = 0;
}

void UPDATE() {
	UINT8 i;
	Sprite* spr;

	ENEMY_INFO* enemyInfo = (ENEMY_INFO*)THIS->custom_data;
	if (enemyInfo->moving && TranslateSprite(THIS, enemyInfo->vx, enemyInfo->vy)) {
		enemyInfo->vy = -enemyInfo->vy;
		enemyInfo->vx = -enemyInfo->vx;
	}
	
	SPRITEMANAGER_ITERATE(i, spr) {
		UINT8 isCollide = CheckCollision(THIS, spr);

		if (enemyInfo->pauseCollision > 0 && isCollide) {
			// Collision is paused by other enemy
			enemyInfo->pauseCollision--;

		} else {
			
			// Collision to other enemies
			if (enemyInfo->moving && spr != THIS &&
				spr->type == SpriteEnemy && isCollide
			) {
				ENEMY_INFO* otherEnemyInfo = (ENEMY_INFO*)spr->custom_data;

				// Collision, change direction and pause the
				// detection on the other enemy for one cycle
				enemyInfo->vy = -enemyInfo->vy;
				enemyInfo->vx = -enemyInfo->vx;
				otherEnemyInfo->pauseCollision = 2;

			// Bump the player on collision
			} else if (spr->type == SpritePlayer) {
				PLAYER_INFO* playerInfo = (PLAYER_INFO*)spr->custom_data;
				UINT8 tile = 0;

				if (playerInfo->dead && isCollide) {
					// change direction when player was killed
					enemyInfo->vy = -enemyInfo->vy;
					enemyInfo->vx = -enemyInfo->vx;
					enemyInfo->pauseCollision = 2;

				} else {
					// use the player collision function to
					// bounce the player when the enemy runs into the player
					UBYTE dir = 0;
					dir = enemyInfo->vx != 0 ? (enemyInfo->vx > 0 ? dir | J_LEFT : dir | J_RIGHT) : dir;
					dir = enemyInfo->vy != 0 ? (enemyInfo->vy > 0 ? dir | J_UP : dir | J_DOWN) : dir;
				
					tile = PERY_PLAYERCOLLISION(SpriteEnemy, spr, dir, THIS);
				}

				// Player touched wall
				if (tile == MAPTILE_WALL) {
					playerInfo->dead = 1;
				}
			}
		}
	}
}

void DESTROY() {
}
