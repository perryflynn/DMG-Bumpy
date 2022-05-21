#include "Pery.h"
#include "SpritePlayer.h"
#include <Print.h>
#include <stdio.h>
#include <stdlib.h>


/*
* Handles collision caused by player and bounces
* the player back and returns the colliding map tile type
*/
UINT8 PERY_PLAYERCOLLISION(
	SPRITE_TYPE collisionType, 
	Sprite *player, UBYTE playerDirection, 
	Sprite *target
) {
	PLAYER_INFO* info = (PLAYER_INFO*)player->custom_data;

	// player is colliding with expected sprite type
	if (target->type == collisionType && CheckCollision(player, target)) {
		// measure bounce direction
		INT8 x = 0;
		INT8 y = 0;

		// player length + enemy length
		INT8 xavg = (16 + 12) / 2;
		INT8 yavg = (16 + 16) / 2;

		// be able to be negative <3
		INT16 px = (INT16)player->x;
		INT16 py = (INT16)player->y;
		INT16 tx = (INT16)target->x;
		INT16 ty = (INT16)target->y;

		// player is below the middle of the target
		if (py-ty > yavg/2) {
			y = BOUNCELENGTH;
		}

		// player is above the middle of the target
		if (ty-py > yavg/2) {
			y = -BOUNCELENGTH;
		}

		// player is right of the middle of the target
		if (px - tx > xavg / 2) {
			x = BOUNCELENGTH;
		}

		// player is left of the middle of the target
		if (tx - px > xavg / 2) {
			x = -BOUNCELENGTH;
		}
		
		// bounce and return the current map tile type
		return TranslateSprite(player, x, y);
	}

	return 0;
}
