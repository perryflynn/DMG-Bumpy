#include "Pery.h"
#include "SpritePlayer.h"
#include <Print.h>

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

		if (/*(playerDirection & J_UP) > 0 &&*/ player->y > target->y) {
			y = BOUNCELENGTH;
		}
		if (/*(playerDirection & J_DOWN) > 0 &&*/ target->y > player->y) {
			y = -BOUNCELENGTH;
		}
		if (/*(playerDirection & J_LEFT) > 0 &&*/ player->x > target->x) {
			x = BOUNCELENGTH;
		}
		if (/*(playerDirection & J_RIGHT) > 0 &&*/ target->x > player->x) {
			x = -BOUNCELENGTH;
		}

		// bounce and return the current map tile type
		return TranslateSprite(player, x, y);
	}

	return 0;
}

void PERY_LOGXY(UINT8 x, UINT8 y) {
#ifdef CFG_ENABLE_LOGGING
	DPRINT_POS(0, 0);
	DPrintf("x:%d y:%d  ", x, y);
#endif
}
