#include <ZGBMain.h>

#define BOUNCELENGTH 5
#define MAPTILE_NONE 0
#define MAPTILE_WALL 1

UINT8 PERY_PLAYERCOLLISION(SPRITE_TYPE collisionType, Sprite* player, UINT8 playerDirection, Sprite* target);

void PERY_LOGXY(UINT8 x, UINT8 y);
