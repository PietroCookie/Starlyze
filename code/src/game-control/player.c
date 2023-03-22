#include "player.h"

#include <unistd.h>
#include <stdio.h>
<<<<<<< HEAD
=======
#include "pthread.h"
>>>>>>> main

void initialiser_player(player_t *player, int posX, int posY){
	player->life = MAX_LIFE_PLAYER;
	player->bomb = 0;
<<<<<<< HEAD
	// player->posX = posX;
	// player->posY = posY;
}

void *thread_player(void *arg) {
	printf("Thread player !\n");
=======
}

void *thread_player(void *arg) {

	while (1)
	{
		pthread_testcancel();
	}
>>>>>>> main

	return NULL;
}