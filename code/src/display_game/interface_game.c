#include "interface_game.h"

#include <string.h>

#include "window.h"
#include "paint_tools.h"
#include "colors.h"
#include "functions.h"
#include "colors.h"

#include "level_display.h"
#include "sprite.h"

void interface_dimensions_game(unsigned short width, unsigned short height) {
	if((COLS < width) || (LINES < height)) {
        ncurses_stop();
        fprintf(stderr, 
              "Terminal size is too small: actually w=%d,h=%d instead of l=%d,h=%d\n",
              COLS, LINES, width, height);
        exit(EXIT_FAILURE);
    } 
}

interface_game_t* interface_game_create() {
	interface_game_t *result;

	interface_dimensions_game(77, 27);

	if((result = malloc(sizeof(interface_game_t))) == NULL){
		ncurses_stop();
		perror("Error allocating structure interface_t");
		exit(EXIT_FAILURE);
	}

	result->win_level = window_create(0, 0, DEFAULT_WIDTH_INTERFACE_GAME, DEFAULT_HEIGHT_INTERFACE_GAME, "Level", FALSE);
	result->win_infos = window_create(DEFAULT_WIDTH_INTERFACE_GAME, 0, 15, DEFAULT_HEIGHT_INTERFACE_GAME, "", FALSE);

	return result;
}

void interface_game_delete(interface_game_t** interface) {
	window_delete(&(*interface)->win_level);
	window_delete(&(*interface)->win_infos);


	free(*interface);
	interface = NULL;
}

void refresh_win_level_game(interface_game_t* interface, level_display_t level_display) {
	int i, j, sprite;
	sprite_t sp;

	for (i = 0; i < WIDTH_LEVEL_GAME; i++)
		for (j = 0; j < HEIGHT_LEVEL_GAME; j++)
			window_mvaddch_col(interface->win_level, j, i, COLOR_BLACK, ' ');
	
	for (i = 0; i < WIDTH_LEVEL_GAME; i++)
		for (j = 0; j < HEIGHT_LEVEL_GAME; j++)
		{
			sprite = level_display.tab[i][j];
			if(sprite == SPRITE_BLOCK)
				paint_block(interface->win_level, i, j);
			else if(sprite == SPRITE_LADDER)
				paint_ladder(interface->win_level, i, j);
			else if(sprite == SPRITE_TRAP)
				paint_trap(interface->win_level, i, j);
			else if(sprite >= SPECIFICATION_GATE && sprite < (SPECIFICATION_GATE + INTERVALLE_SPECIFICATION))
				paint_gate(interface->win_level, i, j, sprite - SPECIFICATION_GATE);
			else if(sprite >= SPECIFICATION_KEY && sprite < (SPECIFICATION_KEY + INTERVALLE_SPECIFICATION))
				paint_key(interface->win_level, i, j, sprite - SPECIFICATION_KEY);
			else if(sprite >= SPECIFICATION_DOOR && sprite < (SPECIFICATION_DOOR + INTERVALLE_SPECIFICATION)) {
				sp.type = SPRITE_DOOR;
				sp.specification = sprite - SPECIFICATION_DOOR;
				paint_door(interface->win_level, i, j, sp);
			}
			else if(sprite == SPRITE_EXIT)
				paint_exit(interface->win_level, i, j);
			else if(sprite == SPRITE_START)
				paint_start(interface->win_level, i, j);
			else if(sprite == SPRITE_ROBOT)
				paint_robot(interface->win_level, i, j);
			else if(sprite == SPRITE_PROBE)
				paint_probe(interface->win_level, i, j);
			else if(sprite >= SPECIFICATION_PLAYERS && sprite < (SPECIFICATION_PLAYERS + INTERVALLE_SPECIFICATION)) {
				paint_player(interface->win_level, i, j, sprite - SPECIFICATION_PLAYERS + 8);
			}
			else if(sprite == SPRITE_BOMB)
				paint_bomb(interface->win_level, i, j);
			else if(sprite == SPRITE_LIFE)
				paint_heart(interface->win_level, i, j);
		}
	
	window_refresh(interface->win_level);
}

void refresh_win_infos(interface_game_t* interface, player_t player) {
	int i, posX = 0;
	char string[5];
	
	window_mvprintw(interface->win_infos, 0, 0, "Keys");
	for (i = 0; i < NUMBER_KEY; i++)
	{
		if(player.key[i]) {
			paint_key(interface->win_infos, posX+=2, 2, i);
		}
		else {
			paint_key(interface->win_infos, posX+=2, 2, 7);
		}
	}

	window_mvprintw(interface->win_infos, 4, 0, "Lives");
	for (i = 0; i < player.life; i++)
		window_mvaddch(interface->win_infos, 5, i+1, 'V');

	window_mvprintw(interface->win_infos, 7, 0, "Bombs");
	sprintf(string,"%d",player.bomb);
	window_mvprintw_col(interface->win_infos, 9, 3, RED, string);

	window_mvprintw(interface->win_infos, 11, 0, "Level");
	sprintf(string,"%d",player.level);
	window_mvprintw(interface->win_infos, 13, 3, string);
	

	window_refresh(interface->win_infos);
}
