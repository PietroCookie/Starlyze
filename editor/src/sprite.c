#include "sprite.h"

#include "window.h"
#include "colors.h"

void paint_block(window_t* window, int posX, int posY){
	window_mvaddch_col(window, posY, posX, FD_CYAN, ' ');
	window_refresh(window);
}

void paint_ladder(window_t* window, int posX, int posY){
	window_mvaddch_col(window, posY, posX, YELLOW, ACS_LTEE);
	window_mvaddch_col(window, posY, ++posX, YELLOW, ACS_HLINE);
	window_mvaddch_col(window, posY, ++posX, YELLOW, ACS_RTEE);

	window_refresh(window);
}

void paint_trap(window_t* window, int posX, int posY){
	window_mvaddch_col(window, posY, posX, FD_CYAN, '#');
	window_refresh(window);
}

void paint_key(window_t* window, int posX, int posY){
	window_mvaddch_col(window, posY, posX, FD_MAGENTA, ' ');
	window_mvaddch_col(window, ++posY, posX, MAGENTA, ACS_LLCORNER);
	window_refresh(window);
}

void paint_gate(window_t* window, int posX, int posY, unsigned int color){
	window_mvaddch_col(window, posY, posX, color, ACS_PLUS);
	window_mvaddch_col(window, ++posY, posX, color, ACS_PLUS);
	window_mvaddch_col(window, ++posY, posX, color, ACS_PLUS);
	window_mvaddch_col(window, ++posY, posX, color, ACS_PLUS);
	window_refresh(window);
}

void paint_door(window_t* window, int posX, int posY){
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
			window_mvaddch_col(window, i+posY, j+posX, FD_GREEN, ' ');
	window_refresh(window);
}

void paint_exit(window_t* window, int posX, int posY){
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
			window_mvaddch_col(window, i+posY, j+posX, FD_YELLOW, ' ');
	window_refresh(window);
}

void paint_start(window_t* window, int posX, int posY){
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
			window_mvaddch_col(window, i+posY, j+posX, FD_MAGENTA, ' ');
	window_refresh(window);
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
	
	window_refresh(window);
}

void paint_probe(window_t* window, int posX, int posY){
	window_mvaddch(window, posY, posX, ACS_LTEE);
	window_mvaddch(window, posY, ++posX, ACS_HLINE);
	window_mvaddch(window, posY, ++posX, ACS_RTEE);
	posX -= 2;
	window_mvaddch(window, ++posY, posX, ACS_LLCORNER);
	window_mvaddch(window, posY, ++posX, ACS_HLINE);
	window_mvaddch(window, posY, ++posX, ACS_LRCORNER);

	window_refresh(window);
}

void paint_heart(window_t* window, int posX, int posY){
	window_mvaddch_col(window, posY, posX, RED, 'V');
	window_refresh(window);
}

void paint_bomb(window_t* window, int posX, int posY){
	window_mvaddch_col(window, posY, posX, WHITE, 'o');
	window_refresh(window);
}