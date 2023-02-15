#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <stdlib.h>

typedef enum {
	SPRITE_BLOCK = 1,
	SPRITE_LADDER = 2,
	SPRITE_TRAP = 3,
	SPRITE_GATE = 4,
	SPRITE_KEY = 5,
	SPRITE_DOOR = 6,
	SPRITE_EXIT = 7,
	SPRITE_START = 8,
	SPRITE_ROBOT = 9,
	SPRITE_PROBE = 10,
	SPRITE_LIFE = 11,
	SPRITE_BOMB = 12
} type_sprite_enum;

typedef struct{
	type_sprite_enum type;
	int specification;
} sprite_t;

int width_sprite(type_sprite_enum type_sprite);

int height_sprite(type_sprite_enum type_sprite);


size_t necessary_size_sprite();

void write_sprite_in_file_descriptor(int file_descriptor, sprite_t sprite);

void read_sprite_in_file_descriptor(int file_descriptor, sprite_t* sprite);

#endif