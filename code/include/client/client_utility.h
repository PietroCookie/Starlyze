/**
 * @file client_utility.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief Various useful functions for the customer
 * @version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __CLIENT_UTILITY_H__
#define __CLIENT_UTILITY_H__

#include <dirent.h>
#include "create_game.h"
#include "info_client.h"

// Constants
#define MAX_MSG 255

/**
 * @brief Display the logo of the application Starlyze
 *
 */
void display_logo_app();

/**
 * @brief Entering the user's nickname
 *
 * @return char*
 */
char *pseudo_entry();

/**
 * @brief Display the menu for the client
 *
 * @param nb_players
 */
void display_menu(int nb_players);

/**
 * @brief Allows the management of the menu
 *
 * @param port
 * @param address_ip
 * @param info_client
 * @param sockfd
 */
void handler_menu(int port, char address_ip[15], info_client_t info_client, int sockfd);

#endif