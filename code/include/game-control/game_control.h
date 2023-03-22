#ifndef __GAME_CONTROL_H__
#define __GAME_CONTROL_H__

#include "world_info.h"
#include "entity.h"


typedef struct {
	world_info_t world_info;
	int number_player;
<<<<<<< HEAD
=======
	int number_total_enemy;
>>>>>>> main

	entity_t *players;

	entity_t **enemy; // List of enemies according to their level
} game_control_t;

typedef struct {
	int level;
	int id_enemy;
	game_control_t *game_control;
<<<<<<< HEAD
} enemy_infos_thread_t;	

void game_control(int num_player);

int load_enemy_world(game_control_t *game_control_infos);
=======
} enemy_infos_thread_t;


void handler_exit(int signum);

void game_control(int num_player);

pthread_t *launch_enemy(game_control_t *game_control_infos);

void load_enemy_world(game_control_t *game_control_infos);

void *thread_trap_level(void *arg);
>>>>>>> main

#endif