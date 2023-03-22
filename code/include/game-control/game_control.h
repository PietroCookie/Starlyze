#ifndef __GAME_CONTROL_H__
#define __GAME_CONTROL_H__

#include "world_info.h"
#include "entity.h"


typedef struct {
	world_info_t world_info;
	int number_player;
	int number_total_enemy;

	entity_t *players;

	entity_t **enemy; // List of enemies according to their level
} game_control_t;

typedef struct {
	int level;
	int id_enemy;
	game_control_t *game_control;
} enemy_infos_thread_t;


void handler_exit(int signum);

void game_control(int num_player);

pthread_t *launch_enemy(game_control_t *game_control_infos);

void load_enemy_world(game_control_t *game_control_infos);

void *thread_trap_level(void *arg);

#endif