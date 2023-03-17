#include "world_info.h"

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include "address_table.h"
#include "sprite.h"

void load_world_info(world_info_t *world_info, char *name_world){
	address_table_t address_table;
	int i, j, k, current_level = 0;
	int file;
	off_t position_next_address_table = 0;
	sprite_t sprite;

	world_info->total_level = 0;
	world_info->levels = NULL;

	if((file = open(name_world, O_RDONLY)) == -1){
		perror("Error opening file world");
		exit(EXIT_FAILURE);
	}


	// Load levels of world
	while (position_next_address_table != -1)
	{
		address_table = read_address_table_in_file_descriptor(file);

		for (i = 1; i < DEFAULT_SIZE_ADDRESS_TABLE-1; i++)
			if(address_table.table[i].position != -1)
				world_info->total_level++;
		
		if(world_info->levels == NULL){
			if((world_info->levels = malloc(world_info->total_level * sizeof(level_info_t))) == NULL){
				perror("Error allocating levels in load_world_info");
				exit(EXIT_FAILURE);
			}
		} else {
			if((world_info->levels = realloc(world_info->levels, world_info->total_level * sizeof(level_info_t))) == NULL){
				perror("Error reallocating levels in load_world_info");
				exit(EXIT_FAILURE);
			}
		}

		for (i = 1; i < DEFAULT_SIZE_ADDRESS_TABLE-1; i++)
			if(address_table.table[i].position != -1){
				if(lseek(file, address_table.table[i].position, SEEK_SET) == -1){
					perror("Error lseek in load_game_info");
					exit(EXIT_FAILURE);
				}
				
				load_level_info(&world_info->levels[current_level++], file);
			}

		if( (position_next_address_table = address_table.table[DEFAULT_SIZE_ADDRESS_TABLE-1].position) != -1)
			if(lseek(file, position_next_address_table, SEEK_SET) == -1){
				perror("Error lseek in load_game_info");
				exit(EXIT_FAILURE);
			}
	}


	// Load doors info of all level
	for (i = 0; i < NUMBER_DOOR; i++) {
		world_info->doors_level[i][0] = -1;
		world_info->doors_level[i][1] = -1;
	}

	for (i = 0; i < world_info->total_level; i++)
		for (j = 0; j < world_info->levels[i].width; j++)
			for(k = 0; k < world_info->levels[i].height; k++) {
				sprite = world_info->levels[i].map[j][k];
				if (sprite.type == SPRITE_DOOR){
					if(sprite.specification >= 1 || sprite.specification <= NUMBER_DOOR){
						if(world_info->doors_level[sprite.specification-1][0] == -1)
							world_info->doors_level[sprite.specification-1][0] = i;
						else
							world_info->doors_level[sprite.specification-1][1] = i;
					}
				}
				else if (sprite.type == SPRITE_START)
					world_info->start_level = i;
				else if(sprite.type == SPRITE_EXIT)
					world_info->exit_level = i;
			}


	// Close file world
	if(close(file)){
		perror("Error closing file world");
		exit(EXIT_FAILURE);
	}
}

void delete_world_info(world_info_t *world_info){
	int i;

	for (i = 0; i < world_info->total_level; i++)
		delete_level_info(&world_info->levels[i]);

	free(world_info->levels);
}