#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "sprite.h"

typedef enum {
	ROBOT = 1,
	PROBE = 2
} type_enemy_enum;

typedef struct
{
	type_enemy_enum type;
} enemy_t;


void initialise_enemy(enemy_t *enemy, type_enemy_enum type);

void *thread_enemy(void *arg);

int direction_alea(type_enemy_enum type_enemy);

#endif