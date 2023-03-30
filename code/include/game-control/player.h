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
 * @brief Initialize a player
 * 
 * @param player The player we initialize
 * @param level The identifier of the level in which the player is positioned
 * @param id Player ID
 */
void initialise_player(player_t *player, int level, int id);

/**
 * @brief The cleaning manager of the player's main thread
 * 
 * @param arg The information needed by the cleaning manager
 */
void cleanup_handler(void *arg);

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