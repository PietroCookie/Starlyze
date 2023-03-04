#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <locale.h>

#include "window.h"
#include "colors.h"
#include "paint_tools.h"
#include "game_level.h"
#include "file_game_level.h"

#define DEFAULT_WIDTH_INTERFACE_GAME 62
#define DEFAULT_HEIGHT_INTERFACE_GAME 22

/**
 * @brief Structure représentant l'interface demandée
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

void refresh_win_tools(interface_t* interface);

void refresh_win_level(interface_t* interface);

#endif