/**
 * @file interface.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manage a interface of editor
 * @version 0.1
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <locale.h>

#include "window.h"
#include "paint_tools.h"
#include "game_level.h"
#include "file_game_level.h"

#define DEFAULT_WIDTH_INTERFACE_GAME 62
#define DEFAULT_HEIGHT_INTERFACE_GAME 22

/**
 * @brief Structure representing the interface of an editor
 * 
 */
typedef struct
{
	window_t* win_infos; // La fenêtre d'informations
	window_t* win_level; // La fenêtre du level
	window_t* win_tools; // La fenêtre d'outil

	file_game_level_t file_game_level;

	game_level_t game_level;
	paint_tool_t paint_tool;

	int id_door;
	int id_gate;
	int id_key;
} interface_t;

/**
 * Check terminal dimensions.
 */
void interface_dimensions(unsigned short width, unsigned short height);

/**
 * @brief Create interface
 * 
 * @return interface_t* created interface
 */
interface_t* interface_create();

/**
 * @brief Delete interface
 * 
 * @param interface interface to delete
 */
void interface_delete(interface_t** interface);

/**
 * @brief Manage actions of the user.
 * 
 * @param interface the interface
 * @param c the pressed key
 */
void interface_actions(interface_t* interface, int c);

/**
 * @brief Refresh window tool
 * 
 * @param interface The interface
 */
void refresh_win_tools(interface_t* interface);

/**
 * @brief Refresh window level
 * 
 * @param interface The interface
 */
void refresh_win_level(interface_t* interface);

#endif