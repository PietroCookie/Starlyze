/**
 * @file server_tcp.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manages the TCP server
 * @version 0.1
 * @date 2023-03-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __SERVER_TCP_H__
#define __SERVER_TCP_H__

#include "game.h"

/**
 * @brief Create a socket tcp
 *
 * @param port
 * @param game
 * @param sockfd
 */
void create_socket_tcp(int port, game_t *game, int sockfd);

#endif