#ifndef __SERVER_UDP_H__
#define __SERVER_UDP_H__

#define MAX_MSG 255

#include "info_client.h"
#include "game.h"
#include "clients_connected.h"


void save_new_client(list_info_client_t* connected_clients, char pseudo[MAX_MSG], char* client_adress, int nb_client, int port); 

void add_client_at_game(list_game_t* list_game, int id_game, info_client_t* client_to_join, int port, int sockfd); 

void send_tcp_socket(int port, int port_tcp, game_t* game, int sockfd);

#endif