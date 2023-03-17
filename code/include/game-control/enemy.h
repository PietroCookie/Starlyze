#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "sprite.h"

typedef enum {
	ROBOT = SPRITE_ROBOT,
	PROBE = SPRITE_PROBE
} type_enemy_enum;

typedef struct
{
	type_enemy_enum type;
} enemy_t;

void initialiser_enemy(enemy_t *enemy, type_enemy_enum type);

#endif