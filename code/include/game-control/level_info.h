#ifndef __LEVEL_INFO_H__
#define __LEVEL_INFO_H__

#include <pthread.h>

#include "sprite.h"

#define NUMBER_ROBOT 10
#define NUMBER_PROBE 10
#define NUMBER_TRAP 40

#define WIDTH_ZONE_LEVEL 5
#define HEIGHT_ZONE_LEVEL 5

typedef struct
{
	int width, height;
	sprite_t **map;

	int number_enemy;
	int robot[NUMBER_ROBOT];
	int probe[NUMBER_PROBE];
	int trap[NUMBER_TRAP];

	int number_mutex_zone;
	pthread_mutex_t *mutex_zone;
} level_info_t;





void load_level_info(level_info_t *level_info, int file);
void delete_level_info(level_info_t *level_info);

#endif