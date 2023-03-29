#ifndef __MOVE_WORLD_H__
#define __MOVE_WORLD_H__

#include "game_control.h"
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

typedef struct
{
	int infos[3];
	level_info_t *level;
} infos_wait_item_t;

typedef struct 
{
	int position[2];
	int number_players;
	int number_enemy;
	int delay_explosion;
	int id_level;
	world_info_t *world_info;
	entity_t *enemy_level;
	entity_t *players;
	type_sprite_enum last_sprite;
} infos_bomb_explose_t;

void *thread_wait_item(void *arg);

void *thread_explose_bomb(void *arg);

int move_level(game_control_t *game_control_info, int id_level, entity_t *entity_move, direction_enum direction);

void reset_player(world_info_t world_info, entity_t *player);

int check_validation_move(level_info_t *level, int posX_dest, int posY_dest, int posX_width, int posY_height, entity_t *entity_move);

int check_validation_move_enemy(level_info_t *level, int posX_dest, int posY_dest, int posX_width, int posY_height, entity_t *entity_move);

int check_validation_move_player(level_info_t *level, int posX_dest, int posY_dest, int posX_width, int posY_height, entity_t *entity_move);

entity_t* check_collision(entity_t *collision, entity_t *collider, int number_collider, int level);

void take_item(level_info_t *level, player_t *player, int posX_dest, int posY_dest, int posX_width, int posY_height);

void enter_door(world_info_t *world_info, entity_t *player);

void drop_bomb(game_control_t *game_control, entity_t *player);

#endif