/**
 * @file game_control.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manage a game_control
 * @version 0.1
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __GAME_CONTROL_H__
#define __GAME_CONTROL_H__

#include <pthread.h>

#include "world_info.h"
#include "entity.h"

/**
 * @brief The structure with all the game information
 * 
 */
typedef struct game_control_t{
	world_info_t world_info;
	int number_player;
	int number_total_enemy;
	pthread_cond_t cond_victory;
	pthread_mutex_t mutex_victory;
	int id_player_winner;

	entity_t *players;

	entity_t **enemy; // List of enemies according to their level
} game_control_t;

/**
 * @brief The information transmitted to an enemy's thread
 * 
 */
typedef struct {
	int level;
	int id_enemy;
	game_control_t *game_control;
} enemy_infos_thread_t;

/**
 * @brief The information transmitted to a player's thread
 * 
 */
typedef struct {
	int id_player;
	int *socket_client;
	game_control_t *game_control;
} player_infos_thread_t;

/**
 * @brief The manager when receiving the SIGINT signal
 * 
 * @param signum The received signal
 */
void handler_exit(int signum);

/**
 * @brief Starts a game, the associated threads and also waits for player connections
 * 
 * @param num_player The number of players
 * @param socket_game The socket of the game
 * @param name_world The name of the world
 */
void game_control(int num_player, int socket_game, char* name_world);

/**
 * @brief Removes the game manager
 * 
 * @param game_control_infos The manager to be deleted
 */
void delete_game_control(game_control_t *game_control_infos);

/**
 * @brief Launch enemy threads
 * 
 * @param game_control_infos The game manager
 * @return pthread_t* Enemies' threads
 */
pthread_t *launch_enemy(game_control_t *game_control_infos);

/**
 * @brief Charge the enemies of the world
 * 
 * @param game_control_infos The game manager
 */
void load_enemy_world(game_control_t *game_control_infos);

/**
 * @brief Launch player threads
 * 
 * @param game_control_infos The game manager
 * @param socket_game The game socket
 * @param socket_client The table that will contain the players' sockets
 * @return pthread_t* Players' threads
 */
pthread_t *launch_players(game_control_t *game_control_infos, int socket_game, int *socket_client);


#endif