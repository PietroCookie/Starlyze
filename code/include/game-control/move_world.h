#ifndef __MOVE_WORLD_H__
#define __MOVE_WORLD_H__

#include "level_info.h"
#include "entity.h"

typedef enum {
	LEFT = 1,
	RIGHT = 2,
	UP = 3,
	DOWN = 4
} direction_enum;

int move_level(level_info_t *level, entity_t *entity_move, direction_enum direction, int number_collision, entity_t *collision);

int take_item(level_info_t *level, player_t *player, int posX, int posY);

void drop_bomb(level_info_t *level, player_t *player, int posX, int posY);

void change_level(level_info_t *level_src, player_t *player, level_info_t *level_dest);

void enter_gate(level_info_t *level, player_t *player);

#endif