/**
 * @file interface_game.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief This file manages the ncurses interface for the game display
 * @version 0.1
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __INTERFACE_GAME_H__
#define __INTERFACE_GAME_H__

#include "window.h"

#include "level_display.h"
#include "player.h"

#define DEFAULT_WIDTH_INTERFACE_GAME 62
#define DEFAULT_HEIGHT_INTERFACE_GAME 22

/**
 * @brief The structure of the interface
 * 
 */
typedef struct
{
	window_t *win_level;
	window_t *win_infos;
	window_t *win_message;
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

/**
 * @brief Refresh the window of level
 * 
 * @param interface The interface to refresh
 * @param level_display state of the game
 */
void refresh_win_level_game(interface_game_t* interface, level_display_t level_display);

/**
 * @brief Refresh the window of information
 * 
 * @param interface The interface to refresh
 * @param player The player whose information should be displayed
 */
void refresh_win_infos(interface_game_t* interface, player_t player);

#endif