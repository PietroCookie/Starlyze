/**
 * @file network_request.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manages the requests and responses of the network between the client and the server
 * @version 0.1
 * @date 2023-03-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __NETWORK_REQUEST_H__
#define __NETWORK_REQUEST_H__

#include "server_udp.h"
#include "create_game.h"
#include "game.h"

// Constants
#define MAX_MSG 255

// Type of request for client
#define CLIENT_FIRST_CONNEXION_SEND_PSEUDO 1
#define CLIENT_NB_CLIENTS 2
#define CLIENT_DISCONNECTION 3
#define CLIENT_LIST_PLAYERS 4
#define CLIENT_RECOVERING_LIST_WORLDS 5
#define CLIENT_START_GAMES 6
#define CLIENT_SEND_LIST_GAME 7
#define CLIENT_JOIN_GAME 8
#define CLIENT_WAITING_FOR_GAME_START 9

// Type of response for server
#define SERVER_SEND_ID_CLIENTS 1
#define SERVER_SEND_NB_CLIENTS 2
#define SERVER_SEND_LIST_GAMES 3
#define SERVER_SEND_NO_GAMES 4

/**
 * @brief Structure that contains the content of the request of the client
 *
 */
typedef union
{
    char pseudo[MAX_MSG];
    int id_client;
    int settings_game[3]; // [0] : name_world | [1] : nb_players_game | [2] : id_client
    int choice_game[2];   // [0] : id_game | [1] : id_client
} content_request_client_udp_t;

/**
 * @brief Structure that contains the request of the client
 *
 */
typedef struct
{
    int type_request;
    content_request_client_udp_t content;
} request_client_udp_t;

/**
 * @brief Structure that contains the content of the response of the server
 *
 */
typedef union
{
    int nb_clients;
    int id_clients;
    int port_tcp;
    list_world_response_t list_world;
    list_game_without_pointers_t list_game;
} content_response_server_t;

/**
 * @brief Structure that contains the response of the server
 *
 */
typedef struct
{
    int type_request;
    content_response_server_t content;
} response_server_udp_t;

#endif