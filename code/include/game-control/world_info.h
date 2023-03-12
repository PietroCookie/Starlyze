#ifndef __WORD_INFO_H__
#define __WORD_INFO_H__

#include <unistd.h>

#include "level_info.h"

#define NUMBER_DOOR 99

typedef struct
{
	int doors_level[NUMBER_DOOR][2];
	
	int total_level;
	level_info_t *levels;

	int start_level;
	int exit_level;

} world_info_t;

void load_world_info(world_info_t *world_info, char *name_world);
void delete_world_info(world_info_t *world_info);

#endif