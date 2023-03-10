#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <stdlib.h>

#include "window.h"
#include "colors.h"

#define MAX_ID_DOOR 99
#define MAX_ID_GATE_KEY 7

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


unsigned int get_color_gate_key(int specification);


void paint_block(window_t* window, int posX, int posY);

void paint_ladder(window_t* window, int posX, int posY);

void paint_trap(window_t* window, int posX, int posY);

void paint_key(window_t* window, int posX, int posY, int id_key);

void paint_gate(window_t* window, int posX, int posY, int id_gate);

void paint_door(window_t* window, int posX, int posY, sprite_t sprite);

void paint_exit(window_t* window, int posX, int posY);

void paint_start(window_t* window, int posX, int posY);

void paint_robot(window_t* window, int posX, int posY);

void paint_probe(window_t* window, int posX, int posY);

void paint_heart(window_t* window, int posX, int posY);

void paint_bomb(window_t* window, int posX, int posY);

#endif