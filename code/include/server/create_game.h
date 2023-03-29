/**
 * @file create_game.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manages the creation of a game for the server
 * @version 0.1
 * @date 2023-03-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __CREATE_GAME_H__
#define __CREATE_GAME_H__

#include <dirent.h>
#include "game.h"
#include "info_client.h"

// Constants
#define MAX_MSG 255

/**
 * @brief Structure that contains the list of worlds
 *
 */
typedef struct
{
    struct dirent **name_world;
    int nb_world;
} list_world_t;

/**
 * @brief Structure that contains the list of worlds without pointers
 *
 */
typedef struct
{
    char name_world[255][255];
    int nb_world;
} list_world_response_t;

/**
 * @brief Function to filter the names of .bin files
 *
 * @return int
 */
int filter_file();

/**
 * @brief Function to recover the list of worlds
 *
 * @return list_world_response_t
 */
list_world_response_t recovering_existing_worlds();

/**
 * @brief Function to create and save a new game
 *
 * @param list_game
 * @param nb_games
 * @param nb_participants_final
 * @param name_world
 * @param new_client
 */
void save_new_game(list_game_t *list_game, int nb_games, int nb_participants_final, char name_world[MAX_MSG],
                   info_client_t *new_client);

#endif