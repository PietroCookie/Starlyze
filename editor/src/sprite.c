#include "sprite.h"

#include <stdio.h>
#include <unistd.h>

int width_sprite(type_sprite_enum type_sprite){
	int width;

	switch (type_sprite)
	{
		case SPRITE_BLOCK:
			width = 1;
			break;

		case SPRITE_LADDER:
			width = 3;
			break;

		case SPRITE_TRAP:
			width = 1;
			break;

		case SPRITE_GATE:
			width = 1;
			break;

		case SPRITE_KEY:
			width = 1;
			break;

		case SPRITE_DOOR:
			width = 3;
			break;

		case SPRITE_EXIT:
			width = 3;
			break;

		case SPRITE_START:
			width = 3;
			break;

		case SPRITE_ROBOT:
			width = 3;
			break;

		case SPRITE_PROBE:
			width = 3;
			break;

		case SPRITE_LIFE:
			width = 1;
			break;

		case SPRITE_BOMB:
			width = 1;
			break;

		default:
			width = -1;
			break;
	}

	return width;
}

int height_sprite(type_sprite_enum type_sprite){
	int width;

	switch (type_sprite)
	{
		case SPRITE_BLOCK:
			width = 1;
			break;

		case SPRITE_LADDER:
			width = 1;
			break;

		case SPRITE_TRAP:
			width = 1;
			break;

		case SPRITE_GATE:
			width = 4;
			break;

		case SPRITE_KEY:
			width = 2;
			break;

		case SPRITE_DOOR:
			width = 4;
			break;

		case SPRITE_EXIT:
			width = 4;
			break;

		case SPRITE_START:
			width = 4;
			break;

		case SPRITE_ROBOT:
			width = 4;
			break;

		case SPRITE_PROBE:
			width = 2;
			break;

		case SPRITE_LIFE:
			width = 1;
			break;

		case SPRITE_BOMB:
			width = 1;
			break;

		default:
			width = -1;
			break;
	}

	return width;
}

size_t necessary_size_sprite(){
	return (2 * sizeof(int));
}

void write_sprite_in_file_descriptor(int file_descriptor, sprite_t sprite){
	if(write(file_descriptor, &sprite.type, sizeof(int)) == -1){
		perror("Error write type sprite");
		exit(EXIT_FAILURE);
	}

	if(write(file_descriptor, &sprite.specification, sizeof(int)) == -1){
		perror("Error write specification sprite");
		exit(EXIT_FAILURE);
	}
}

void read_sprite_in_file_descriptor(int file_descriptor, sprite_t* sprite){
	if(read(file_descriptor, &sprite->type, sizeof(int)) == -1){
		perror("Error read type sprite");
		exit(EXIT_FAILURE);
	}

	if(read(file_descriptor, &sprite->specification, sizeof(int)) == -1){
		perror("Error read specification sprite");
		exit(EXIT_FAILURE);
	}
}
