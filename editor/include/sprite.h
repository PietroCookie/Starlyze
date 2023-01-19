#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "window.h"

#define SPRITE_BLOCK 1
#define SPRITE_LADDER 2
#define SPRITE_TRAP 3
#define SPRITE_GATE 4
#define SPRITE_KEY 5
#define SPRITE_DOOR 6
#define SPRITE_EXIT 7
#define SPRITE_START 8
#define SPRITE_ROBOT 9
#define SPRITE_PROBE 10
#define SPRITE_LIFE 11
#define SPRITE_BOMB 12

void paint_block(window_t* window, int posX, int posY);

void paint_ladder(window_t* window, int posX, int posY);

void paint_trap(window_t* window, int posX, int posY);

void paint_key(window_t* window, int posX, int posY);

void paint_gate(window_t* window, int posX, int posY, unsigned int color);

void paint_door(window_t* window, int posX, int posY);

void paint_exit(window_t* window, int posX, int posY);

void paint_start(window_t* window, int posX, int posY);

void paint_robot(window_t* window, int posX, int posY);

void paint_probe(window_t* window, int posX, int posY);

void paint_heart(window_t* window, int posX, int posY);

void paint_bomb(window_t* window, int posX, int posY);

#endif