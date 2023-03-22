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

void *thread_enemy(void *arg);

<<<<<<< HEAD
int direction_alea();
=======
int direction_alea(type_enemy_enum type_enemy);
>>>>>>> main

#endif