<<<<<<< HEAD
#ifndef __GAME_LEVEL_H__
#define __GAME_LEVEL_H__

#include <stdlib.h>

#include "element_game_level.h"

#define WIDTH_LEVEL_GAME 60
#define HEIGHT_LEVEL_GAME 20

typedef struct
{
	element_game_level_t *elements_map[WIDTH_LEVEL_GAME][HEIGHT_LEVEL_GAME];
} game_level_t;


void initialise_game_level(game_level_t* game_level);

void delete_game_level(game_level_t* game_level);

void add_element_map_in_case(game_level_t* game_level, element_game_level_t* element);

void delete_element_map_in_case(game_level_t* game_level, int posX, int posY);


size_t necessary_size_game_level(game_level_t game_level);

void save_modification_game_level_in_file_descriptor(int file_descriptor, off_t position, game_level_t game_level, int posX, int posY);

void write_game_level_in_file_descriptor(int file_descriptor, game_level_t game_level);

void read_game_level_in_file_descriptor(int file_descriptor, game_level_t* game_level);

=======
#ifndef __GAME_LEVEL_H__
#define __GAME_LEVEL_H__

#include <stdlib.h>

#include "element_game_level.h"

#define WIDTH_LEVEL_GAME 60
#define HEIGHT_LEVEL_GAME 20

typedef struct
{
	element_game_level_t *elements_map[WIDTH_LEVEL_GAME][HEIGHT_LEVEL_GAME];
} game_level_t;


void initialise_game_level(game_level_t* game_level);

void delete_game_level(game_level_t* game_level);

void add_element_map_in_case(game_level_t* game_level, element_game_level_t* element);

void delete_element_map_in_case(game_level_t* game_level, int posX, int posY);


size_t necessary_size_game_level(game_level_t game_level);

void save_modification_game_level_in_file_descriptor(int file_descriptor, off_t position, game_level_t game_level, int posX, int posY);

void write_game_level_in_file_descriptor(int file_descriptor, game_level_t game_level);

void read_game_level_in_file_descriptor(int file_descriptor, game_level_t* game_level);

>>>>>>> main
#endif