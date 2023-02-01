#include "sprite.h"

#include "window.h"
#include "colors.h"

void paint_block(window_t* window, int posX, int posY){
	window_mvaddch_col(window, posY, posX, FD_CYAN, ' ');
}

void paint_ladder(window_t* window, int posX, int posY){
	window_mvaddch_col(window, posY, posX, YELLOW, ACS_LTEE);
	window_mvaddch_col(window, posY, ++posX, YELLOW, ACS_HLINE);
	window_mvaddch_col(window, posY, ++posX, YELLOW, ACS_RTEE);
}

void paint_trap(window_t* window, int posX, int posY){
	window_mvaddch_col(window, posY, posX, FD_CYAN, '#');
}

void paint_key(window_t* window, int posX, int posY){
	window_mvaddch_col(window, posY, posX, FD_MAGENTA, ' ');
	window_mvaddch_col(window, ++posY, posX, MAGENTA, ACS_LLCORNER);
}

void paint_gate(window_t* window, int posX, int posY, unsigned int color){
	window_mvaddch_col(window, posY, posX, color, ACS_PLUS);
	window_mvaddch_col(window, ++posY, posX, color, ACS_PLUS);
	window_mvaddch_col(window, ++posY, posX, color, ACS_PLUS);
	window_mvaddch_col(window, ++posY, posX, color, ACS_PLUS);
}

void paint_door(window_t* window, int posX, int posY){
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
			window_mvaddch_col(window, i+posY, j+posX, FD_GREEN, ' ');
}

void paint_exit(window_t* window, int posX, int posY){
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
			window_mvaddch_col(window, i+posY, j+posX, FD_YELLOW, ' ');
}

void paint_start(window_t* window, int posX, int posY){
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
			window_mvaddch_col(window, i+posY, j+posX, FD_MAGENTA, ' ');
}

void paint_robot(window_t* window, int posX, int posY){
	window_mvaddch(window, posY, posX, ACS_ULCORNER);
	window_mvaddch(window, posY, ++posX, ACS_BTEE);
	window_mvaddch(window, posY, ++posX, ACS_URCORNER);
	posX -= 2;
	window_mvaddch(window, ++posY, posX, ACS_LLCORNER);
	window_mvaddch(window, posY, ++posX, ACS_LTEE);
	window_mvaddch(window, posY, ++posX, ACS_LRCORNER);
	posX -= 2;
	window_mvaddch(window, ++posY, posX, ACS_HLINE);
	window_mvaddch(window, posY, ++posX, ACS_PLUS);
	window_mvaddch(window, posY, ++posX, ACS_HLINE);
	posX -= 2;
	window_mvaddch(window, ++posY, posX, ACS_ULCORNER);
	window_mvaddch(window, posY, ++posX, ACS_BTEE);
	window_mvaddch(window, posY, ++posX, ACS_URCORNER);
}

void paint_probe(window_t* window, int posX, int posY){
	window_mvaddch(window, posY, posX, ACS_LTEE);
	window_mvaddch(window, posY, ++posX, ACS_HLINE);
	window_mvaddch(window, posY, ++posX, ACS_RTEE);
	posX -= 2;
	window_mvaddch(window, ++posY, posX, ACS_LLCORNER);
	window_mvaddch(window, posY, ++posX, ACS_HLINE);
	window_mvaddch(window, posY, ++posX, ACS_LRCORNER);
}

void paint_heart(window_t* window, int posX, int posY){
	window_mvaddch_col(window, posY, posX, RED, 'V');
}

void paint_bomb(window_t* window, int posX, int posY){
	window_mvaddch_col(window, posY, posX, WHITE, 'o');
}

int width_sprite(int id_sprite){
	int width;

	switch (id_sprite)
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

int height_sprite(int id_sprite){
	int width;

	switch (id_sprite)
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