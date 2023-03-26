#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "sprite.h"
#include "player.h"
#include "enemy.h"


typedef struct {
	int posX;
	int posY;
	type_sprite_enum type;
	int freeze;
	union {
		player_t player;
		enemy_t enemy;
	};
} entity_t;

void initialise_entity(entity_t *entity, type_sprite_enum type, int posX, int posY);

#endif