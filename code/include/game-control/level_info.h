#ifndef __LEVEL_INFO_H__
#define __LEVEL_INFO_H__

#include <pthread.h>

#include "sprite.h"
#include "trap.h"

#define NUMBER_ROBOT 10
#define NUMBER_PROBE 10
#define NUMBER_TRAP 40

#define WIDTH_LEVEL 60
#define HEIGHT_LEVEL 20

#define WIDTH_ZONE_LEVEL 5
#define HEIGHT_ZONE_LEVEL 5

typedef struct
{
	sprite_t map[WIDTH_LEVEL][HEIGHT_LEVEL];

	int number_enemy;
	int robot[NUMBER_ROBOT];
	int probe[NUMBER_PROBE];
	list_block_trap_t list_block_trap;

	int number_mutex_zone;
	pthread_mutex_t *mutex_zone;
} level_info_t;


void load_level_info(level_info_t *level_info, int file);
void delete_level_info(level_info_t *level_info);

void load_block_trap(level_info_t level_info, list_block_trap_t *list_block_trap);

#endif