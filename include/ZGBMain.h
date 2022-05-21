#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateGame)\
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SpritePlayer, player)\
_SPRITE_DMG(SpriteEnemy, enemy)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

//#define CFG_ENABLE_LOGGING

void CreateEnemy(UINT16 x, UINT16 y, INT8 vx, INT8 vy);

#endif