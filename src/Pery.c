#include "Pery.h"
#include "SpritePlayer.h"

/*
* Handles collition caused by player and bounces
* the player back and returns the colliding map tile type
*/
UINT8 PERY_PLAYERCOLLISION(
	SPRITE_TYPE collisionType, 
	Sprite *player, UINT8 playerDirection, 
	Sprite *target
) {
	PLAYER_INFO* info = (PLAYER_INFO*)player->custom_data;

	// player is colliding with expected sprite type
	if (target->type == collisionType && CheckCollision(player, target)) {
		// measure bounce direction
		UINT8 x = 0;
		UINT8 y = 0;

		if (playerDirection == J_UP) {
			y = BOUNCELENGTH;
		}
		if (playerDirection == J_DOWN) {
			y = -BOUNCELENGTH;
		}
		if (playerDirection == J_LEFT) {
			x = BOUNCELENGTH;
		}
		if (playerDirection == J_RIGHT) {
			x = -BOUNCELENGTH;
		}

		// bounce and return the current map tile type
		return TranslateSprite(player, x, y);
	}

	return 0;
}
