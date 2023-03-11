#include "game_control.h"

#include <stdlib.h>
#include <stdio.h>

#include "world_info.h"

void game_control()
{
	int i;
	world_info_t world_info;

	load_world_info(&world_info, "test.bin");

	delete_world_info(&world_info);
}
