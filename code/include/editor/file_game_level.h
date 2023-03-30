/**
 * @file file_game_level.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manage a file of game_level (file .world)
 * @version 0.1
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __FILE_GAME_LEVEL_H__
#define __FILE_GAME_LEVEL_H__

#include <stdlib.h>

#include "game_level.h"
#include "address_table.h"

/**
 * @brief Structure of a file of game_level
 * 
 */
typedef struct
{
	address_table_t address_table; // Address table
	address_table_t address_table_void; // Address table void
	int current_index_address_table; // Current index in address table represent level's load
	int file_descriptor; // File descriptor
} file_game_level_t;

/**
 * @brief Open a file of game_level
 * 
 * @param name_file The name of the file
 * @param file_game_level The variable that will contain the file of game_level
 * @return game_level_t The game level contained in the file of game_level
 */
game_level_t open_file_game_level(const char* name_file, file_game_level_t* file_game_level);

/**
 * @brief Delete in memeory the file of game_level (not storage)
 * 
 * @param file_game_level The file of game_level that will be destroy in memory
 */
void delete_file_game_level(file_game_level_t* file_game_level);

/**
 * @brief Add an address table in file of game_level
 * 
 * @param file_game_level The file of game_level to which we add an address table
 */
void add_address_table(file_game_level_t* file_game_level);
/**
 * @brief Add an address table of void in file of game_level
 * 
 * @param file_game_level The file of game_level to which we add an address table of void
 */
void add_address_table_void(file_game_level_t* file_game_level);

/**
 * @brief For the first backup of a game_level in file of game_level.
 * 
 * @param file_game_level The file of game_level in which we save
 * @param game_level The game_level that will be saved
 */
void first_save_game_level_in_file(file_game_level_t* file_game_level, game_level_t game_level);
/**
 * @brief Save the modification of a game level in the file
 * 
 * @param file_game_level The file of game_level in which we save
 * @param game_level The game_level that will be saved
 * @param posX Position X of the element that will be modified in the file
 * @param posY Position Y of the element that will be modified in the file
 */
void save_modification_game_level(file_game_level_t* file_game_level, game_level_t game_level, int posX, int posY);

/**
 * @brief Delete a game_level in file. Delete its entry in the address table and add it to the void table
 * 
 * @param file_game_level The file that contains the game_level deleted 
 */
void delete_game_level_in_file(file_game_level_t* file_game_level);

/**
 * @brief Load a game_level from the .world file in memory
 * 
 * @param file_game_level The game file containing the information 
 * @param game_level The variable in which we load the game_level
 * @param next Indicates whether to load the next (1) or previous (-1) file
 */
void load_level_in_file(file_game_level_t* file_game_level, game_level_t* game_level, int next);

/**
 * @brief Search for an empty location in the game file stored in the void tables and large enough
 * 
 * @param file_game_level The file in which the empty location is searched
 * @return int The position in the vacuum table currently in memory of a corresponding location. -1 otherwise
 */
int search_void_entry_address_table(file_game_level_t* file_game_level);
int search_position_free(file_game_level_t* file_game_level, size_t size_necessary);


#endif