#ifndef __CLIENT_GAME_H__
#define __CLIENT_GAME_H__

#include <pthread.h>

#include "interface_game.h"

typedef struct
{
	int *socket_client;
	interface_game_t *interface;
} client_game_infos_thread_t;


int connection_game(char* address, int port);

void *thread_display(void *arg);

#endif