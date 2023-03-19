#include "player.h"

#include <unistd.h>
#include <stdio.h>

void initialiser_player(player_t *player, int posX, int posY){
	player->life = MAX_LIFE_PLAYER;
	player->bomb = 0;
	// player->posX = posX;
	// player->posY = posY;
}

void *thread_player(void *arg) {
	printf("Thread player !\n");

	return NULL;
}