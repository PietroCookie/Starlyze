#ifndef __MOVE_WORLD_H__
#define __MOVE_WORLD_H__

#include "world_info.h"
#include "level_info.h"
#include "entity.h"
#include "sprite.h"

typedef enum {
	LEFT = 1,
	RIGHT = 2,
	UP = 3,
	DOWN = 4
} direction_enum;

int move_level(level_info_t *level, entity_t *entity_move, direction_enum direction, int number_collision, entity_t *collision);

int check_validation_move(level_info_t *level, int posX_dest, int posY_dest, type_sprite_enum type_sprite, direction_enum direction);

int take_item(level_info_t *level, player_t *player, int posX, int posY);

void drop_bomb(level_info_t *level, player_t *player, int posX, int posY);

void enter_door(world_info_t *world_info, entity_t *player);

void enter_gate(level_info_t *level, entity_t *player);

#endif