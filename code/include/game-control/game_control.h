#ifndef __GAME_CONTROL_H__
#define __GAME_CONTROL_H__

#include "world_info.h"
#include "entity.h"


typedef struct {
	world_info_t world_info;
	int number_player;

	entity_t *players;

	entity_t **enemy; // List of enemies according to their level
} game_control_t;

typedef struct {
	int level;
	int id_enemy;
	game_control_t *game_control;
} enemy_infos_thread_t;	

void game_control(int num_player);

int load_enemy_world(game_control_t *game_control_infos);

#endif