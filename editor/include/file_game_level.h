#ifndef __FILE_GAME_LEVEL_H__
#define __FILE_GAME_LEVEL_H__

#include <stdlib.h>

#include "game_level.h"
#include "address_table.h"

typedef struct
{
	address_table_t address_table; // Address table
	address_table_t address_table_void; // Address table void
	int current_level_index_address_table; // Current index in address table represent level's load
	int fd; // File descriptor
} file_game_level_t;


void open_file_game_level(const char* name_file, file_game_level_t* file_game_level);

void delete_file_game_level(file_game_level_t* file_game_level);

void save_in_file_game_level(file_game_level_t* file_game_level, game_level_t game_level);

void delete_in_file_game_level(file_game_level_t* file_game_level);

void load_level(file_game_level_t* file_game_level, game_level_t* game_level, int next);

int search_position_free(file_game_level_t* file_game_level, size_t size_necessary);

size_t calculate_necessary_size_save_game_level(game_level_t game_level);

void read_game_level_in_file(int fd, off_t position, game_level_t* game_level);

void write_game_level_in_file(int fd, game_level_t game_level);

#endif