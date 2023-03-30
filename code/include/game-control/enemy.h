/**
 * @file enemy.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manage an enemy
 * @version 0.1
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "sprite.h"

/**
 * @brief The type of an enemy
 * 
 */
typedef enum {
	ROBOT = 1,
	PROBE = 2
} type_enemy_enum;

/**
 * @brief Represents an enemys
 * 
 */
typedef struct
{
	type_enemy_enum type;
} enemy_t;

/**
 * @brief Initialize an enemy
 * 
 * @param enemy Enemy initialized
 * @param type The type of the enemy
 */
void initialise_enemy(enemy_t *enemy, type_enemy_enum type);

/**
 * @brief thread of operation of an enemy
 * 
 * @param arg The necessary information in the form of the enemy_infos_thread_t structure
 * @return void* The result of this Thread - there is NULL
 */
void *thread_enemy(void *arg);

/**
 * @brief Gets a random direction depending on the type of an enemy
 * 
 * @param type_enemy The type of the enemy
 * @return int The random direction
 */
int direction_alea(type_enemy_enum type_enemy);

#endif