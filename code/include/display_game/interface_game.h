#ifndef __INTERFACE_GAME_H__
#define __INTERFACE_GAME_H__

#include "window.h"

#include "level_display.h"

#define DEFAULT_WIDTH_INTERFACE_GAME 62
#define DEFAULT_HEIGHT_INTERFACE_GAME 22

typedef struct
{
	window_t *win_level;

} interface_game_t;

/**
 * Check terminal dimensions.
 */
void interface_dimensions_game(unsigned short width, unsigned short height);

/**
 * @brief Create interface
 * 
 * @return interface_t* created interface
 */
interface_game_t* interface_game_create();

/**
 * @brief Delete interface
 * 
 * @param interface interface to delete
 */
void interface_game_delete(interface_game_t** interface);


void refresh_win_level_game(interface_game_t* interface, level_display_t level_display);

#endif