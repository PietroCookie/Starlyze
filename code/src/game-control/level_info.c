#include "level_info.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void load_level_info(level_info_t *level_info, int file){
	int i, j, m, n;
	int current_robot = 0, current_probe = 0, current_trap = 0;
	sprite_t sprite;

	for (i = 0; i < NUMBER_ROBOT; i++)
		level_info->robot[i] = -1;
	for (i = 0; i < NUMBER_PROBE; i++)
		level_info->probe[i] = -1;
	for (i = 0; i < NUMBER_TRAP; i++)
		level_info->trap[i] = -1;	
	

	if(read(file, &level_info->width, sizeof(int)) == -1){
		perror("Error read width level in load_world_info");
		exit(EXIT_FAILURE);
	}

	if(read(file, &level_info->height, sizeof(int)) == -1){
		perror("Error read heigh level in load_world_info");
		exit(EXIT_FAILURE);
	}


	level_info->number_mutex_zone = (level_info->width * level_info->height) / (WIDTH_ZONE_LEVEL * HEIGHT_ZONE_LEVEL);
	if((level_info->mutex_zone = malloc(level_info->number_mutex_zone * sizeof(pthread_mutex_t))) == NULL){
		perror("Error allocating memory for mutex zone");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < level_info->number_mutex_zone; i++)
		if(pthread_mutex_init(&level_info->mutex_zone[i], NULL) != 0){
			fprintf(stderr, "Error intialise mutex zone");
			exit(EXIT_FAILURE);
		}
	


	if((level_info->map = malloc(level_info->width * sizeof(sprite_t*))) == NULL){
		perror("Error allocating width map in load_level_info");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < level_info->width; i++)
		if((level_info->map[i] = malloc(level_info->height * sizeof(sprite_t))) == NULL){
			perror("Error allocating height map in load_level_info");
			exit(EXIT_FAILURE);
		}
	
	// Load sprite of level
	for (i = 0; i < level_info->width; i++)
		for (j = 0; j < level_info->height; j++){
			read_sprite_in_file_descriptor(file, &sprite);

			if(sprite.type != 0) {

				if(sprite.type != SPRITE_ROBOT && sprite.type != SPRITE_PROBE)
					for (m = 0; m < width_sprite(sprite.type); m++)
						for (n = 0; n < height_sprite(sprite.type); n++)
							level_info->map[i+m][j+n] = sprite;

				if(sprite.type == SPRITE_ROBOT)
					level_info->robot[current_robot++] = j * level_info->width + i;
				else if (sprite.type == SPRITE_PROBE)
					level_info->probe[current_probe++] = j * level_info->width + i;
				else if (sprite.type == SPRITE_TRAP)
					level_info->trap[current_trap++] = j * level_info->width + i;
			}
		}

	level_info->number_enemy = current_probe + current_robot;
}

void delete_level_info(level_info_t *level_info){
	int i;

	for (i = 0; i < level_info->width; i++)
		free(level_info->map[i]);
	free(level_info->map);


	for (i = 0; i < level_info->number_mutex_zone; i++)
		if(pthread_mutex_destroy(&level_info->mutex_zone[i]) != 0){
			fprintf(stderr, "Error destroy mutex zone");
			exit(EXIT_FAILURE);
		}
	free(level_info->mutex_zone);
}