/**
 * @file server_udp.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manages the UDP server
 * @version 0.1
 * @date 2023-03-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __SERVER_UDP_H__
#define __SERVER_UDP_H__

#include "info_client.h"
#include "game.h"

// Constants
#define MAX_MSG 255

/**
 * @brief Function to save a new client
 * 
 * @param connected_clients 
 * @param pseudo 
 * @param client_adress 
 * @param nb_client 
 * @param port 
 */
void save_new_client(list_info_client_t* connected_clients, char pseudo[MAX_MSG], char* client_adress, int nb_client, int port); 

/**
 * @brief Function to add a client to a game specified by its id
 * 
 * @param list_game 
 * @param id_game 
 * @param client_to_join 
 * @param port 
 * @param sockfd 
 */
void add_client_at_game(list_game_t* list_game, int id_game, info_client_t* client_to_join, int port, int sockfd); 

/**
 * @brief Function to send a message with TCP Port to a client
 * 
 * @param port 
 * @param port_tcp 
 * @param game 
 * @param sockfd 
 */
void send_tcp_socket(int port, int port_tcp, game_t* game, int sockfd);

#endif