#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "sprite.h"
#include "player.h"
#include "enemy.h"


typedef enum {
	PLAYER = 1,
	ENEMY = 2
} type_entity_enum;

typedef struct {
	int posX;
	int posY;
	type_entity_enum type;
	int freeze;
	union {
		player_t player;
		enemy_t enemy;
	};
} entity_t;

void initialise_entity(entity_t *entity, type_entity_enum type, int posX, int posY);

int posX_width_entity(entity_t entity);

int posY_height_entity(entity_t entity);

#endif