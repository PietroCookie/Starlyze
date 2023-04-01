/**
 * @file level_display.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief This file allows to define the methods and structures to display the state of a level
 * @version 0.1
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __LEVEL_DISPLAY_H__
#define __LEVEL_DISPLAY_H__

#include "level_info.h"

#include "entity.h"

#define INTERVALLE_SPECIFICATION 100

#define SPECIFICATION_DOOR 100
#define SPECIFICATION_GATE (SPECIFICATION_DOOR + INTERVALLE_SPECIFICATION)
#define SPECIFICATION_KEY (SPECIFICATION_GATE + INTERVALLE_SPECIFICATION)
#define SPECIFICATION_PLAYERS (SPECIFICATION_KEY + INTERVALLE_SPECIFICATION)

/**
 * @brief Structure represent a minimal version of a level
 * 
 */
typedef struct
{
	int tab[WIDTH_LEVEL][HEIGHT_LEVEL];
} level_display_t;

/**
 * @brief Convert the state of a level with its entities into a minimal level
 * 
 * @param id_level Id of the level
 * @param level_display The variable in which the minimum level will be contained
 * @param level_info The level info
 * @param enemies Enemies presents in the level
 * @param number_enemies Number enemies presents in the level
 * @param players Players presents in the level
 * @param number_players Number players presents int the level
 */
void convert_level_info(int id_level, level_display_t *level_display, level_info_t level_info, entity_t *enemies, int number_enemies, entity_t *players, int number_players);

#endif