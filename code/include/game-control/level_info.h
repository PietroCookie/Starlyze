/**
 * @file level_info.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manage a level_info
 * @version 0.1
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __LEVEL_INFO_H__
#define __LEVEL_INFO_H__

#include <pthread.h>

#include "sprite.h"
#include "trap.h"

#define NUMBER_ROBOT 10
#define NUMBER_PROBE 10
#define NUMBER_TRAP 40

#define WIDTH_LEVEL 60
#define HEIGHT_LEVEL 20

#define WIDTH_ZONE_LEVEL 5
#define HEIGHT_ZONE_LEVEL 5

/**
 * @brief The structure representing the information of a level
 * 
 */
typedef struct
{
	sprite_t map[WIDTH_LEVEL][HEIGHT_LEVEL];

	int number_enemy;
	int robot[NUMBER_ROBOT];
	int probe[NUMBER_PROBE];
	list_block_trap_t list_block_trap;

	int number_mutex_zone;
	pthread_mutex_t *mutex_zone;
} level_info_t;

/**
 * @brief Allows to load a level from a file descriptor
 * 
 * @param level_info The variable that will contain the level information
 * @param file The file descriptor
 */
void load_level_info(level_info_t *level_info, int file);
/**
 * @brief Deletes the information of a level
 * 
 * @param level_info The information of the level you want to delete
 */
void delete_level_info(level_info_t *level_info);

/**
 * @brief Load the trap blocks of a level
 * 
 * @param level_info The level to load the trap blocks with
 * @param list_block_trap The list that will contain the trap blocks
 */
void load_block_trap(level_info_t level_info, list_block_trap_t *list_block_trap);

#endif