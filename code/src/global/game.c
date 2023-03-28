/**
 * @file game.c
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manages the data structures of the games
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

#include "game.h"

/**
 * @brief Initialize the list of games
 *
 * @param nb_games
 * @return list_game_t*
 */
list_game_t *init_list_game(int nb_games)
{
    list_game_t *list = malloc(sizeof(list_game_t));
    list->head = NULL;
    list->nb_games = nb_games;
    return list;
}

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
game_t *init_game(int id, int nb_participants_final, int nb_participants_actual, char name_world[MAX_MSG], info_client_t *new_client)
{
    game_t *game = malloc(sizeof(game_t));
    game->id = id;
    game->nb_participants_final = nb_participants_final;
    game->nb_participants_actual = nb_participants_actual;
    strcpy(game->name_world, name_world);
    game->list_players = malloc(sizeof(list_info_client_t));
    init_list_info_client(game->list_players);
    add_client(game->list_players, new_client);
    game->next = NULL;
    game->prev = NULL;
    return game;
}

/**
 * @brief Check if the list of games is empty
 *
 * @param list
 * @return int
 */
int is_empty_game(list_game_t *list)
{
    if (list->head == NULL)
    {
        return 1; // Right
    }
    else
    {
        return 0; // False
    }
}

/**
 * @brief Add a game to the list of games
 *
 * @param list
 * @param game
 */
void add_game(list_game_t *list, game_t *game)
{
    if (is_empty_game(list) == 1)
    {
        list->head = game;
        list->head->next = NULL;
        list->head->prev = NULL;
    }
    else
    {
        game->next = list->head;
        if (list->head != NULL)
        {
            list->head->prev = game;
        }
        list->head = game;
        game->prev = NULL;
    }
}

/**
 * @brief Print the list of games
 *
 * @param list
 */
void print_list_game(list_game_t list)
{
    printf("========== Liste des partie ================\n");
    game_t *current = list.head;
    while (current != NULL)
    {
        printf(">> Informations sur la partie n°%d\n", current->id);
        printf("Partie %d - Nombre de participants: %d - Nom du monde: %s\n", current->id, current->nb_participants_final, current->name_world);
        printf(">> Joueurs inscrits :\n");
        print_list_client(*current->list_players);
        printf("\n\n");
        current = current->next;
    }
}

/**
 * @brief Search a game in the list of games
 *
 * @param list
 * @param id
 * @return game_t*
 */
game_t *search_game(list_game_t *list, int id)
{
    game_t *current = list->head;
    while (current != NULL)
    {
        if (current->id == id)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * @brief Delete a game from the list of games
 *
 * @param list
 * @param game
 */
void delete_game(list_game_t *list, game_t *game)
{
    if (game->prev == NULL)
    {
        list->head = game->next;
    }
    else
    {
        game->prev->next = game->next;
    }
    if (game->next != NULL)
    {
        game->next->prev = game->prev;
    }
    free(game);
}

/**
 * @brief Delete the list of games
 *
 * @param list
 */
void delete_list_game(list_game_t *list)
{
    game_t *current = list->head;
    while (current != NULL)
    {
        game_t *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}

/**
 * @brief Convert a structure game to a structure game without pointers
 *
 * @param list
 * @return list_game_without_pointers_t
 */
list_game_without_pointers_t convert_struct_game_to_game_without_players(list_game_t *list)
{
    list_game_without_pointers_t list_without_pointers;
    game_t *current = list->head;
    int i = 0;
    while (current != NULL)
    {
        if (current->nb_participants_actual == current->nb_participants_final)
        {
            current = current->next;
            continue;
        }
        else
        {
            list_without_pointers.game[i].id = current->id;
            list_without_pointers.game[i].nb_participants_final = current->nb_participants_final;
            list_without_pointers.game[i].nb_participants_actual = current->nb_participants_actual;
            strcpy(list_without_pointers.game[i].name_world, current->name_world);
            current = current->next;
            i++;
        }
    }
    list_without_pointers.nb_games = i;

    return list_without_pointers;
}