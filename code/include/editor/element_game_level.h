/**
 * @file element_game_level.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief Files that manage element of a game_level
 * @version 0.1
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __ELEMENT_GAME_H__
#define __ELEMENT_GAME_H__

#include "sprite.h"

/**
 * @brief An element of game_level
 * 
 */
typedef struct
{
	int posX;
	int posY;
	int width;
	int height;
	sprite_t sprite;
} element_game_level_t;


/**
 * @brief Calculate the necessary size for save an element of game_level in file
 * 
 * @return size_t The size necessary
 */
size_t necessary_size_element_game_level();

/**
 * @brief Write an element game_level in file descriptor
 * 
 * @param file_descriptor The file descriptor in which we write
 * @param element_game_level The element of game_level to write
 */
void write_element_game_level_in_file_descriptor(int file_descriptor, element_game_level_t element_game_level);

/**
 * @brief Read an element game_level in file descriptor
 * 
 * @param file_descriptor The file descriptor in which we read
 * @param posX Position X of the element in game_level
 * @param posY Position Y of the element in game_level
 * @return element_game_level_t* The variable that will contain the element read
 */
element_game_level_t* read_element_game_level_in_file_descriptor(int file_descriptor, int posX, int posY);

#endif