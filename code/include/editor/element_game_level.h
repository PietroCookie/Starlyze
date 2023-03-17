#ifndef __ELEMENT_GAME_H__
#define __ELEMENT_GAME_H__

#include "sprite.h"

typedef struct
{
	int posX;
	int posY;
	int width;
	int height;
	sprite_t sprite;
} element_game_level_t;


size_t necessary_size_element_game_level();

void write_element_game_level_in_file_descriptor(int file_descriptor, element_game_level_t element_game_level);

element_game_level_t* read_element_game_level_in_file_descriptor(int file_descriptor, int posX, int posY);

#endif