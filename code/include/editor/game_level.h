/**
 * @file game_level.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manage a game_level
 * @version 0.1
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __GAME_LEVEL_H__
#define __GAME_LEVEL_H__

#include <stdlib.h>

#include "element_game_level.h"

#define WIDTH_LEVEL_GAME 60
#define HEIGHT_LEVEL_GAME 20

/**
 * @brief Represent a game_level
 * 
 */
typedef struct
{
	element_game_level_t *elements_map[WIDTH_LEVEL_GAME][HEIGHT_LEVEL_GAME];
} game_level_t;

/**
 * @brief Initialise the game_level
 * 
 * @param game_level The variable that will contain the game_level
 */
void initialise_game_level(game_level_t* game_level);

/**
 * @brief Delete a game_level from memory
 * 
 * @param game_level The game_level that will be deleted from memory
 */
void delete_game_level(game_level_t* game_level);

/**
 * @brief Adds an element to the game_level
 * 
 * @param game_level The game_level in which we add an element
 * @param element The element that is added
 */
void add_element_map_in_case(game_level_t* game_level, element_game_level_t* element);

/**
 * @brief Remove an element from a game_levels
 * 
 * @param game_level The game_level in which we delete the element
 * @param posX Position X of the element to be deleted
 * @param posY Position Y of the element to be deleted
 */
void delete_element_map_in_case(game_level_t* game_level, int posX, int posY);


/**
 * @brief Calculate the necessary size for save a game_level in file
 * 
 * @param game_level The game_level whose size we want to know
 * @return size_t The size necessary
 */
size_t necessary_size_game_level(game_level_t game_level);

/**
 * @brief Save a modification of game_level to a file
 * 
 * @param file_descriptor The file descriptor in which the game_level is stored
 * @param position The position in the file at which the game_level is written
 * @param game_level The game_level has recorded
 * @param posX Position X of the modified element to be saved in the file
 * @param posY Position Y of the modified element to be saved in the file
 */
void save_modification_game_level_in_file_descriptor(int file_descriptor, off_t position, game_level_t game_level, int posX, int posY);

/**
 * @brief writes a game_level to a file
 * 
 * @param file_descriptor The file in which we write the game_level
 * @param game_level The game_level to write 
 */
void write_game_level_in_file_descriptor(int file_descriptor, game_level_t game_level);

/**
 * @brief read a game_level to a file
 * 
 * @param file_descriptor The file in which we read the game_level
 * @param game_level The game_level to read
 */
void read_game_level_in_file_descriptor(int file_descriptor, game_level_t* game_level);

#endif