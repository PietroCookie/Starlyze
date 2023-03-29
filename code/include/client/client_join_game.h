/**
 * @file client_join_game.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manages when a customer joins an already created game
 * @version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __CLIENT_JOIN_GAME_H__
#define __CLIENT_JOIN_GAME_H__

#include "game.h"
/**
 * @brief Receive the list of games on hold from the server
 *
 * @param port
 * @param ip_server
 * @param sockfd
 * @return list_game_without_pointers_t
 */
list_game_without_pointers_t receive_list_games_on_hold(int port, char ip_server[15], int sockfd);

/**
 * @brief Sends the request to the server to join a game
 *
 * @param port
 * @param ip_server
 * @param choice_game
 * @param id_client
 */
void join_game(int port, char ip_server[15], int choice_game, int id_client);

#endif