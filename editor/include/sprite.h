#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "window.h"

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