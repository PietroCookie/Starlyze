/**
 * @file game.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manages the data structures of the games
 * @version 0.1
 * @date 2023-03-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __GAME_H__
#define __GAME_H__

#include "info_client.h"

// Constants
#define MAX_MSG 255

/**
 * @brief Structure that contains the information of a game
 *
 */
struct game_t
{
    int id;
    int nb_participants_final;
    int nb_participants_actual;
    char name_world[MAX_MSG];
    list_info_client_t *list_players;
    struct game_t *next;
    struct game_t *prev;
};
typedef struct game_t game_t;

/**
 * @brief Structure that contains the list of games
 *
 */
typedef struct
{
    game_t *head;
    int nb_games;
} list_game_t;

/**
 * @brief Structure that contains the information of a game without the list of players
 *
 */
typedef struct
{
    int id;
    char name_world[MAX_MSG];
    int nb_participants_final;
    int nb_participants_actual;
} game_without_players_t;

/**
 * @brief Structure that contains the list of games without the list of players
 *
 */
typedef struct
{
    game_without_players_t game[200];
    int nb_games;
} list_game_without_pointers_t;

/**
 * @brief Initialize the list of games
 *
 * @param nb_games
 * @return list_game_t*
 */
list_game_t *init_list_game(int nb_games);

/**
 * @brief Initialize a game
 *
 * @param id
 * @param nb_participants_final
 * @param nb_participants_actual
 * @param name_world
 * @param new_client
 * @return game_t*
 */
game_t *init_game(int id, int nb_participants_final, int nb_participants_actual, char name_world[MAX_MSG], info_client_t *new_client);

/**
 * @brief Check if the list of games is empty
 *
 * @param list
 * @return int
 */
int is_empty_game(list_game_t *list);

/**
 * @brief Add a game to the list of games
 *
 * @param list
 * @param game
 */
void add_game(list_game_t *list, game_t *game);

/**
 * @brief Print the list of games
 *
 * @param list
 */
void print_list_game(list_game_t list);

/**
 * @brief Search a game in the list of games
 *
 * @param list
 * @param id
 * @return game_t*
 */
game_t *search_game(list_game_t *list, int id);

/**
 * @brief Delete a game from the list of games
 *
 * @param list
 * @param game
 */
void delete_game(list_game_t *list, game_t *game);

/**
 * @brief Delete the list of games
 *
 * @param list
 */
void delete_list_game(list_game_t *list);

/**
 * @brief Convert a structure game to a structure game without players
 *
 * @param list
 * @return list_game_without_pointers_t
 */
list_game_without_pointers_t convert_struct_game_to_game_without_players(list_game_t *list);

#endif