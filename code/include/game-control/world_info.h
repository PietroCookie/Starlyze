/**
 * @file world_info.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manage world_info
 * @version 0.1
 * @date 2023-03-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __WORD_INFO_H__
#define __WORD_INFO_H__

#include <unistd.h>

#include "level_info.h"

#define NUMBER_DOOR 99

/**
 * @brief Represents the information of a world
 * 
 */
typedef struct
{
	int doors_level[NUMBER_DOOR][2];
	
	int total_level;
	level_info_t *levels;

	int start_level;
	int exit_level;
} world_info_t;

/**
 * @brief Load a world
 * 
 * @param world_info The variable that will contain the world's information
 * @param name_world The name of the world that we charge
 */
void load_world_info(world_info_t *world_info, char *name_world);

/**
 * @brief Delete a world from memory
 * 
 * @param world_info The world we want to suppress
 */
void delete_world_info(world_info_t *world_info);

#endif