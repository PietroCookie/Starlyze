/**
 * @file client_create_game.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief .h file of the client allowing the creation of a game
 * @version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __CLIENT_CREATE_GAME_H__
#define __CLEINT_CREATE_GAME_H__

#include "create_game.h"
/**
 * @brief Receive the list of the worlds from the server
 *
 * @param port
 * @param address_ip
 * @param sockfd
 * @return list_world_response_t
 */
list_world_response_t receive_list_world(int port, char address_ip[15], int sockfd);

/**
 * @brief Send the settings of the game to the server
 *
 * @param port
 * @param address_ip
 * @param choice_world
 * @param nb_players_game
 * @param id_client
 * @param sockfd
 */
void send_settings_game(int port, char address_ip[15], int choice_world, int nb_players_game, int id_client, int sockfd);

/**
 * @brief Menu managing the creation of a game
 *
 * @param list_world
 * @param port
 * @param address_ip
 * @param id_client
 * @param sockfd
 * @return int
 */
int handler_create_game(list_world_response_t list_world, int port, char address_ip[15], int id_client, int sockfd);

#endif