#include "element_game_level.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

size_t necessary_size_element_game_level(){
	return necessary_size_sprite();
}

void write_element_game_level_in_file_descriptor(int file_descriptor, element_game_level_t element_game_level){
	write_sprite_in_file_descriptor(file_descriptor, element_game_level.sprite);
}

element_game_level_t* read_element_game_level_in_file_descriptor(int file_descriptor, int posX, int posY){
	element_game_level_t* element_read;
	sprite_t sprite_read;

	read_sprite_in_file_descriptor(file_descriptor, &sprite_read);

	if(sprite_read.type == 0){
		element_read = NULL;
	}else{
		if((element_read = malloc(sizeof(element_game_level_t))) == NULL){
			perror("Error allocating memory for element_game_level_t in read_element_game_level_in_file_descriptor");
			exit(EXIT_FAILURE);
		}

		element_read->posX = posX;
		element_read->posY = posY;
		element_read->sprite = sprite_read;
		element_read->width = width_sprite(element_read->sprite.type);
		element_read->height = height_sprite(element_read->sprite.type);
	}

	return element_read;
}
