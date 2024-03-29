#include "level_info.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

void load_level_info(level_info_t *level_info, int file){
	int i, j, m, n;
	int current_robot = 0, current_probe = 0;
	sprite_t sprite;


	for (i = 0; i < NUMBER_ROBOT; i++)
		level_info->robot[i] = -1;
	for (i = 0; i < NUMBER_PROBE; i++)
		level_info->probe[i] = -1;

	initialise_list_block_trap(&level_info->list_block_trap);

	level_info->number_mutex_zone = (WIDTH_LEVEL * HEIGHT_LEVEL) / (WIDTH_ZONE_LEVEL * HEIGHT_ZONE_LEVEL);
	if((level_info->mutex_zone = malloc(level_info->number_mutex_zone * sizeof(pthread_mutex_t))) == NULL){
		perror("Error allocating memory for mutex zone");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < level_info->number_mutex_zone; i++)
		if(pthread_mutex_init(&level_info->mutex_zone[i], NULL) != 0){
			fprintf(stderr, "Error intialise mutex zone\n");
			exit(EXIT_FAILURE);
		}

	for (i = 0; i < WIDTH_LEVEL; i++)
		for (j = 0; j < HEIGHT_LEVEL; j++)
			level_info->map[i][j].type = 0;
	
	// Load sprite of level
	for (i = 0; i < WIDTH_LEVEL; i++)
		for (j = 0; j < HEIGHT_LEVEL; j++){
			read_sprite_in_file_descriptor(file, &sprite);

			if(sprite.type != 0) {

				if(sprite.type != SPRITE_ROBOT && sprite.type != SPRITE_PROBE)
					for (m = 0; m < width_sprite(sprite.type); m++)
						for (n = 0; n < height_sprite(sprite.type); n++)
							level_info->map[i+m][j+n] = sprite;

				if(sprite.type == SPRITE_ROBOT)
					level_info->robot[current_robot++] = j * WIDTH_LEVEL + i;
				else if (sprite.type == SPRITE_PROBE)
					level_info->probe[current_probe++] = j * WIDTH_LEVEL + i;
			}
		}

	level_info->number_enemy = current_probe + current_robot;

	load_block_trap(*level_info, &level_info->list_block_trap);
}

void delete_level_info(level_info_t *level_info){
	int i;

	for (i = 0; i < level_info->number_mutex_zone; i++)
		if(pthread_mutex_destroy(&level_info->mutex_zone[i]) != 0){
			fprintf(stderr, "Error destroy mutex zone\n");
			exit(EXIT_FAILURE);
		}
	free(level_info->mutex_zone);

	destroy_list_block_trap(&level_info->list_block_trap);
}

void load_block_trap(level_info_t level_info, list_block_trap_t *list_block_trap) {
	int i, j, m;
	trap_t *trap;
	list_trap_t *list_trap;

	for (i = 0; i < WIDTH_LEVEL; i++)
	{
		for (j = 0; j < HEIGHT_LEVEL; j++)
		{
			if(level_info.map[i][j].type == SPRITE_TRAP) {
				if((list_trap = malloc(sizeof(list_trap_t))) == NULL) {
					perror("Error allocating memory list_trap in load_block_trap");
					exit(EXIT_FAILURE);
				}

				initialise_list_trap(list_trap);
				insert_list_block_trap(list_block_trap, list_trap);

				if((trap = malloc(sizeof(trap_t))) == NULL) {
					perror("Error allocating memory trap in load_bloack_trap");
					exit(EXIT_FAILURE);
				}
				initialise_trap(trap, i, j);
				insert_list_trap(list_trap, trap);
				level_info.map[i][j].type = 0;

				if(level_info.map[i+1][j].type == SPRITE_TRAP) {
					m = i+1;
					while (level_info.map[m][j].type == SPRITE_TRAP)
					{
						if((trap = malloc(sizeof(trap_t))) == NULL) {
							perror("Error allocating memory trap in load_bloack_trap");
							exit(EXIT_FAILURE);
						}
						initialise_trap(trap, m, j);
						insert_list_trap(list_trap, trap);
						
						level_info.map[m][j].type = 0;

						m++;
					}
					
				}
				else if(level_info.map[i][j+1].type == SPRITE_TRAP) {
					m = j+1;
					while (level_info.map[i][m].type == SPRITE_TRAP)
					{
						if((trap = malloc(sizeof(trap_t))) == NULL) {
							perror("Error allocating memory trap in load_bloack_trap");
							exit(EXIT_FAILURE);
						}
						initialise_trap(trap, i, m);
						insert_list_trap(list_trap, trap);

						level_info.map[i][m].type = 0;

						m++;
					}
				}
			}
		}
	}
	
}