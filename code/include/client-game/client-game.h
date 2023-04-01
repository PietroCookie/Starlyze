/**
 * @file client-game.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manages the client in a game
 * @version 0.1
 * @date 2023-03-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __CLIENT_GAME_H__
#define __CLIENT_GAME_H__

#include <pthread.h>

#include "interface_game.h"

/**
 * @brief Structure that contains informations transmit at thread_display
 * 
 */
typedef struct 
{
	int freeze;
	int end_game;
	int *socket_client;
	interface_game_t *interface;
} client_game_infos_thread_t;

/**
 * @brief Creates a TCP socket for the connection to the game server and connects it
 * 
 * @param address The address of the game server
 * @param port  The port of the game server
 * @return int The file descriptor of the socket
 */
int connection_game(char* address, int port);

/**
 * @brief The thread that receive and displays the game
 * 
 * @param arg a pointer to a client_game_infos_thread_t structure
 * @return void* The result of this Thread - there is NULL
 */
void *thread_display(void *arg);

#endif