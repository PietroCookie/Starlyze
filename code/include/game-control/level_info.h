#ifndef __LEVEL_INFO_H__
#define __LEVEL_INFO_H__

#include "sprite.h"

#define NUMBER_ROBOT 10
#define NUMBER_PROBE 10
#define NUMBER_TRAP 40

typedef struct
{
	int width, height;
	sprite_t **map;

	int robot[NUMBER_ROBOT];
	int probe[NUMBER_PROBE];
	int trap[NUMBER_TRAP];
} level_info_t;


void load_level_info(level_info_t *level_info, int file);
void delete_level_info(level_info_t *level_info);

#endif