#ifndef __NETWORK_REQUEST_H__
#define __NETWORK_REQUEST_H__

#define MAX_MSG 255

#include "server_udp.h"
#include "create_game.h"

// Type of request for client
#define CLIENT_FIRST_CONNEXION_SEND_PSEUDO 1
#define CLIENT_NB_CLIENTS 2
#define CLIENT_DISCONNECTION 3
#define CLIENT_LIST_PLAYERS 4
#define CLIENT_RECOVERING_LIST_WORLDS 5

// Type of response for server
#define SERVER_SEND_ID_CLIENTS 1
#define SERVER_SEND_NB_CLIENTS 2

typedef union{
    char pseudo[MAX_MSG]; 
    int id_client; 
}content_request_client_udp_t; 

typedef struct{
    int type_request; 
    content_request_client_udp_t content; 
}request_client_udp_t; 

typedef union{
    int nb_clients; 
    int id_clients; 
    list_world_response_t list_world; 
}content_response_server_t;

typedef struct{
    int type_request;
    content_response_server_t content; 
}response_server_udp_t; 





#endif  