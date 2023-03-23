#ifndef __CLIENT_CREATE_GAME_H__
#define __CLEINT_CREATE_GAME_H__

#include "create_game.h"

list_world_response_t receive_list_world(int port, char address_ip[15]); 
void send_settings_game(int port, char address_ip[15], int choice_world,int nb_players_game, int id_client); 
int handler_create_game(list_world_response_t list_world, int port, char address_ip[15], int); 

#endif