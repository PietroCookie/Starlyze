#include "player.h"

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#include "functions.h"

#include "game_control.h"
#include "move_world.h"
#include "move_world.h"

void initialise_player(player_t *player, int level, int id){
	int i;

	player->life = MAX_LIFE_PLAYER;
	player->bomb = 0;
	player->level = level;
	player->id = id;

	for (i = 0; i < NUMBER_KEY; i++)
		player->key[i] = 0;
}

void *thread_player(void *arg) {
	// int id_player = ((player_infos_thread_t *)arg)->id_player;
	// game_control_t *game_control = ((player_infos_thread_t *)arg)->game_control;
	// entity_t *player_entity = &game_control->players[id_player];
	
	free(arg);

	while (1)
	{
		// enter_gate(&game_control->world_info.levels[player_entity->player.level], player_entity);

		pthread_testcancel();
		sleep(2);
	}

	return NULL;
}