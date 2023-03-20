#include "interface_game.h"

#include "window.h"
#include "paint_tools.h"
#include "colors.h"
#include "functions.h"

#include "level_display.h"

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

	return result;
}

void interface_game_delete(interface_game_t** interface) {
	window_delete(&(*interface)->win_level);



	free(*interface);
	interface = NULL;
}

void refresh_win_level_game(interface_game_t* interface, level_display_t level_display) {
	int i, j;

	for (i = 0; i < WIDTH_LEVEL_GAME; i++)
		for (j = 0; j < HEIGHT_LEVEL_GAME; j++)
			window_mvaddch_col(interface->win_level, j, i, COLOR_BLACK, ' ');
	
	for (i = 0; i < WIDTH_LEVEL_GAME; i++)
		for (j = 0; j < HEIGHT_LEVEL_GAME; j++)
		{
			switch (level_display.tab[i][j])
			{
			case SPRITE_BLOCK:
				paint_block(interface->win_level, i, j);
				break;
			
			case SPRITE_ROBOT:
				paint_robot(interface->win_level, i, j);
				break;

			default:
				break;
			}
		}
	
	window_refresh(interface->win_level);
}
