#include "player.h"

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#include "game_control.h"
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
	// game_control_t *game_control;

	// game_control = (game_control_t *)arg;

	while (1)
	{
		pthread_testcancel();
	}

	return NULL;
}