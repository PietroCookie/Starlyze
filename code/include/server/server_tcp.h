#ifndef __SERVER_TCP_H__
#define __SERVER_TCP_H__

#include "game.h"

void create_socket_tcp(int port, game_t* game, int sockfd); 

#endif