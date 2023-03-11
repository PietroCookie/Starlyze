#ifndef __LEVEL_INFO_H__
#define __LEVEL_INFO_H__

#include "sprite.h"

typedef struct
{
	int width, height;
	sprite_t **map;
} level_info_t;


void load_level_info(level_info_t *level_info, int file);
void delete_level_info(level_info_t *level_info);

#endif