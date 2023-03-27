#ifndef __CLIENT_JOIN_GAME_H__
#define __CLIENT_JOIN_GAME_H__

#include "game.h"

list_game_without_pointers_t receive_list_games_on_hold(int port, char ip_server[15]);
void join_game(int port, char ip_server[15], int choice_game, int id_client); 


#endif