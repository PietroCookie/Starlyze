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

unsigned int get_color_gate_key(int specification){
	unsigned int color;

	switch (specification){
		case 1:
			color = WHITE;
			break;
		case 2:
			color = GREEN;
			break;
		case 3:
			color = BLUE;
			break;
		case 4:
			color = RED;
			break;
		case 5:
			color = YELLOW;
			break;
		case 6:
			color = CYAN;
			break;
		case 7:
			color = MAGENTA;
			break;
		default:
			color = MAGENTA;
			break;
	};

	return color;
}

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

void paint_key(window_t* window, int posX, int posY, int id_key){
	unsigned int color = get_color_gate_key(id_key);

	window_mvaddch_col(window, posY, posX, color+7, ' ');
	window_mvaddch_col(window, ++posY, posX, color, ACS_LLCORNER);
}

void paint_gate(window_t* window, int posX, int posY, int id_gate){
	unsigned int color = get_color_gate_key(id_gate);

	window_mvaddch_col(window, posY, posX, color, ACS_PLUS);
	window_mvaddch_col(window, ++posY, posX, color, ACS_PLUS);
	window_mvaddch_col(window, ++posY, posX, color, ACS_PLUS);
	window_mvaddch_col(window, ++posY, posX, color, ACS_PLUS);
}

void paint_door(window_t* window, int posX, int posY, sprite_t sprite){
	int i, j;
	char char_value[4];

	sprintf(char_value, "%d", sprite.specification);

	window_mvaddch_col(window, posY, posX, FD_GREEN, '0');
	if(sprite.specification >= 10)
		window_mvprintw_col(window, posY, posX+1, FD_GREEN, char_value);
	else{
		window_mvaddch_col(window, posY, posX+1, FD_GREEN, '0');
		window_mvprintw_col(window, posY, posX+2, FD_GREEN, char_value);
	}

	for (i = 1; i < 4; i++)
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