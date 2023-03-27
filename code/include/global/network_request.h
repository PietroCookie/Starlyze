#ifndef __NETWORK_REQUEST_H__
#define __NETWORK_REQUEST_H__

#define MAX_MSG 255

#include "server_udp.h"
#include "create_game.h"
#include "game.h"

// Type of request for client
#define CLIENT_FIRST_CONNEXION_SEND_PSEUDO 1
#define CLIENT_NB_CLIENTS 2
#define CLIENT_DISCONNECTION 3
#define CLIENT_LIST_PLAYERS 4
#define CLIENT_RECOVERING_LIST_WORLDS 5
#define CLIENT_START_GAMES 6
#define CLIENT_SEND_LIST_GAME 7
#define CLIENT_JOIN_GAME 8

// Type of response for server
#define SERVER_SEND_ID_CLIENTS 1
#define SERVER_SEND_NB_CLIENTS 2
#define SERVER_SEND_LIST_GAMES 3
#define SERVER_SEND_NO_GAMES 4

typedef union{
    char pseudo[MAX_MSG]; 
    int id_client; 
    int settings_game[3]; // [0] : name_world | [1] : nb_players_game | [2] : id_client
    int choice_game[2]; // [0] : id_game | [1] : id_client
}content_request_client_udp_t; 

typedef struct{
    int type_request; 
    content_request_client_udp_t content; 
}request_client_udp_t; 

typedef union{
    int nb_clients; 
    int id_clients; 
    list_world_response_t list_world; 
    list_game_without_pointers_t list_game;
}content_response_server_t;

typedef struct{
    int type_request;
    content_response_server_t content; 
}response_server_udp_t; 


#endif  