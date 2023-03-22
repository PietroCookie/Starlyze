#include "player.h"

#include <unistd.h>
#include <stdio.h>
#include "pthread.h"

void initialiser_player(player_t *player, int posX, int posY){
	player->life = MAX_LIFE_PLAYER;
	player->bomb = 0;
}

void *thread_player(void *arg) {

	while (1)
	{
		pthread_testcancel();
	}

	return NULL;
}