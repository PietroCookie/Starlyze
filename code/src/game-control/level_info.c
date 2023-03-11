#include "level_info.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void load_level_info(level_info_t *level_info, int file){
	int i, j;

	if(read(file, &level_info->width, sizeof(int)) == -1){
		perror("Error read width level in load_world_info");
		exit(EXIT_FAILURE);
	}

	if(read(file, &level_info->height, sizeof(int)) == -1){
		perror("Error read heigh level in load_world_info");
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
	

	for (i = 0; i < level_info->width; i++)
		for (j = 0; j < level_info->height; j++)
			read_sprite_in_file_descriptor(file, &level_info->map[i][j]);
}

void delete_level_info(level_info_t *level_info){
	int i;

	for (i = 0; i < level_info->width; i++)
		free(level_info->map[i]);

	free(level_info->map);
}