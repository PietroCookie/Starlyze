/**
 * @file entity.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manage an entity
 * @version 0.1
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "sprite.h"
#include "player.h"
#include "enemy.h"

/**
 * @brief The type of the entity
 * 
 */
typedef enum {
	PLAYER = 1,
	ENEMY = 2
} type_entity_enum;

/**
 * @brief A game entity
 * 
 */
typedef struct {
	int posX;
	int posY;
	type_entity_enum type;
	int freeze;
	union {
		player_t player;
		enemy_t enemy;
	};
} entity_t;

/**
 * @brief Initialize an entity
 * 
 * @param entity The entity that is initialized
 * @param type The type of the entitys
 * @param posX Position X of the entity
 * @param posY Position Y of the entity
 */
void initialise_entity(entity_t *entity, type_entity_enum type, int posX, int posY);

/**
 * @brief Allows you to obtain the width of an entity
 * 
 * @param entity The entity whose width we want
 * @return int The width of the entity
 */
int posX_width_entity(entity_t entity);

/**
 * @brief Allows you to obtain the height of an entity
 * 
 * @param entity The entity whose height we want
 * @return int The height of the entity
 */
int posY_height_entity(entity_t entity);

#endif