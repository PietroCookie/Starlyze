/**
 * @file player.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manage a player
 * @version 0.1
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __PLAYER_H__
#define __PLAYER_H__

#define MAX_LIFE_PLAYER 5
#define NUMBER_KEY 4

typedef struct game_control_t game_control_t;

/**
 * @brief Reppresent a player
 * 
 */
typedef struct
{
	int key[NUMBER_KEY];
	int life;
	int bomb;
	int level;
	int id;
	int invincible;
} player_t;

/**
 * @brief Structure that contains informations transmit at end_thread_player_properly
*/
typedef struct 
{
	int socket;
	game_control_t *game_control_infos;
	player_t *player;
} infos_end_thread_properly_t;

/**
 * @brief Initialize a player
 * 
 * @param player The player we initialize
 * @param level The identifier of the level in which the player is positioned
 * @param id Player ID
 */
void initialise_player(player_t *player, int level, int id);

/**
 * @brief The method cancel thread_sending_level
 * 
 * @param arg The information needed by the cleaning manager
 */
void cancel_thread_send_player(void *arg);

/**
 * @brief The method send the request END_GAME to the client player
 * 
 * @param The information needed by the cleaning manager
*/
void end_thread_player_properly(void *arg);

/**
 * @brief The thread that makes the player invincible for three seconds
 * 
 * @param arg Information needed for the thread
 * @return void* The result of this Thread - there is NULL
 */
void *thread_invincible(void *arg);

/**
 * @brief The main thread of a player
 * 
 * @param arg Information needed for the thread
 * @return void* The result of this Thread - there is NULL
 */
void *thread_player(void *arg);

/**
 * @brief The thread that sends the game information to the player
 * 
 * @param arg Information needed for the thread
 * @return void* The result of this Thread - there is NULL
 */
void *thread_sending_level(void *arg);

#endif