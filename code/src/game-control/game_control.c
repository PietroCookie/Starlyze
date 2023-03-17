#include "game_control.h"

#include <stdlib.h>
#include <stdio.h>

#include "world_info.h"
#include "move_world.h"
#include "entity.h"

void game_control()
{
	int i, j;
	world_info_t world_info;
	// int number_player;
	// entity_t *players;
	// entity_t **enemy; // list of enemies according to their level

	load_world_info(&world_info, "test.bin");

	for (i = 0; i < world_info.levels[0].height; i++){
		for (j = 0; j < world_info.levels[0].width; j++)
			printf("%2d|", world_info.levels[0].map[j][i].type);
		printf("\n");
	}

	delete_world_info(&world_info);
}
