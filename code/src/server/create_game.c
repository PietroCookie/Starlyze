/**
 * @file create_game.c
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manages the creation of a game for the server
 * @version 0.1
 * @date 2023-03-29
 *
 * @copyright Copyright (c) 2023
 *
 */

// INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "create_game.h"

/**
 * @brief Function to filter the names of .bin files
 *
 * @param entry
 * @return int
 */
int filter_file_bin(const struct dirent *entry)
{
    if (entry->d_type == DT_REG)
    {
        if (strstr(entry->d_name, ".bin") != NULL)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Function to recover the list of worlds
 *
 * @return list_world_response_t
 */
list_world_response_t recovering_existing_worlds()
{
    list_world_t list_world;
    list_world_response_t response_list_world;
    char *name, *last_dot;
    // Scans the directory with the custom filter function and retrieve the number of files
    list_world.nb_world = scandir(".", &list_world.name_world, filter_file_bin, alphasort);

    if (list_world.name_world < 0)
    {
        perror("[ERROR] - Error when browsing the directory");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < list_world.nb_world; i++)
    {
        name = list_world.name_world[i]->d_name;
        // Find the last dot in the file name
        last_dot = strrchr(name, '.');
        // Removes the file name extension
        if (last_dot != NULL)
        {
            *last_dot = '\0';
        }
        free(list_world.name_world[i]);
    }

    response_list_world.nb_world = list_world.nb_world;
    // response_list_world.name_world = malloc(sizeof(char*) * list_world.nb_world);

    for (int i = 0; i < list_world.nb_world; i++)
    {
        // response_list_world.name_world[i] = malloc(sizeof(char) * strlen(list_world.name_world[i]->d_name));
        strcpy(response_list_world.name_world[i], list_world.name_world[i]->d_name);
    }

    return response_list_world;
}

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
                   info_client_t *new_client)
{
    game_t *new_game = init_game(nb_games, nb_participants_final, 1, name_world, new_client);
    add_game(list_game, new_game);
    list_game->nb_games++;
}