#ifndef __FILE_GAME_LEVEL_H__
#define __FILE_GAME_LEVEL_H__

#include <stdlib.h>

#include "game_level.h"
#include "address_table.h"

typedef struct
{
	address_table_t address_table; // Address table
	address_table_t address_table_void; // Address table void
	int current_index_address_table; // Current index in address table represent level's load
	int file_descriptor; // File descriptor
} file_game_level_t;


game_level_t open_file_game_level(const char* name_file, file_game_level_t* file_game_level);

void delete_file_game_level(file_game_level_t* file_game_level);


void add_address_table(file_game_level_t* file_game_level);
void add_address_table_void(file_game_level_t* file_game_level);

void first_save_game_level_in_file(file_game_level_t* file_game_level, game_level_t game_level);
void save_modification_game_level(file_game_level_t* file_game_level, game_level_t game_level, int posX, int posY);

void delete_game_level_in_file(file_game_level_t* file_game_level);

void load_level_in_file(file_game_level_t* file_game_level, game_level_t* game_level, int next);

int search_void_entry_address_table(file_game_level_t* file_game_level);
int search_position_free(file_game_level_t* file_game_level, size_t size_necessary);


#endif