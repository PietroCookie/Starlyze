#include "interface.h"

#include "functions.h"
#include "sprite.h"

void interface_dimensions(unsigned short width, unsigned short height) {
    if((COLS < width) || (LINES < height)) {
        ncurses_stop();
        fprintf(stderr, 
              "Terminal size is too small: actually w=%d,h=%d instead of l=%d,h=%d\n",
              COLS, LINES, width, height);
        exit(EXIT_FAILURE);
    } 
}

interface_t* interface_create(){
	interface_t* result;

	interface_dimensions(77, 27);
	
	if((result = malloc(sizeof(interface_t))) == NULL){
		ncurses_stop();
		perror("Error allocating structure interface_t");
		exit(EXIT_FAILURE);
	}

	result->win_level = window_create(0, 0, DEFAULT_WIDTH_INTERFACE_GAME, DEFAULT_HEIGHT_INTERFACE_GAME, "Level", FALSE);
	initialise_win_level(result);
	window_refresh(result->win_level);

	result->win_tools = window_create(DEFAULT_WIDTH_INTERFACE_GAME, 0, 15, DEFAULT_HEIGHT_INTERFACE_GAME, "Tools", TRUE);
	initialise_win_tools(result);
	window_refresh(result->win_tools);

	result->win_infos = window_create(0, 22, 77, 5, "Informations", TRUE);
	window_printw_col(result->win_infos, RED, "Press 'Q' to exit");
	window_refresh(result->win_infos);

	result->paint_tool.id_tool = -1;
	initialise_game_level(&result->game_level, DEFAULT_WIDTH_INTERFACE_GAME-2, DEFAULT_HEIGHT_INTERFACE_GAME-2);

	return result;
}

void interface_delete(interface_t **interface) {
    window_delete(&(*interface)->win_infos);
	window_delete(&(*interface)->win_level);
	window_delete(&(*interface)->win_tools);
	
	delete_game_level(&(*interface)->game_level);

    free(*interface);
    interface = NULL;
}

void interface_actions(interface_t* interface, int c){
	int mouseX, mouseY, posX, posY;

	if((c == KEY_MOUSE) && (mouse_getpos(&mouseX, &mouseY) == OK)){
		#ifdef _DEBUG_
        window_printw(interface->win_infos, "\nClick (%d,%d)", mouseX, mouseY);
        window_refresh(interface->win_infos);
		#endif
		if(window_getcoordinates(interface->win_tools, mouseX, mouseY, &posX, &posY)){
			select_paint_tool(interface->win_tools, &interface->paint_tool, posY);
			#ifdef _DEBUG_
			window_printw(interface->win_infos, "\nTools %d", interface->paint_tool.id_tool);
			window_refresh(interface->win_infos);
			#endif
		}

		if(window_getcoordinates(interface->win_level, mouseX, mouseY, &posX, &posY)){
			action_tool(&interface->game_level, interface->win_infos, interface->paint_tool, posX, posY);
			refresh_win_level(interface);
		}
	}
}

void initialise_win_level(interface_t* interface){
	// int i;
	// element_map_t* element_block;
	// element_block.width = 1;
	// element_block.height = 1;
	// element_block.id_sprite = SPRITE_BLOCK;

	// for (i = 0; i < 60; i++)
	// {
	// 	element_block.posX = i;
	// 	element_block.posY = 0;
	// 	add_element_map_in_case(&interface->game_level, &element_block);
	// 	paint_block(interface->win_level, i, 0);
	// 	paint_block(interface->win_level, i, 19);
	// }
	// for (i = 1; i < 19; i++)
	// {
	// 	paint_block(interface->win_level, 0, i);
	// 	paint_block(interface->win_level, 59, i);
	// }
}

void initialise_win_tools(interface_t* interface){
	int posX = 0;
	int posY = 15;
	
	print_paint_tool(interface->win_tools, 0);

	window_mvprintw_col(interface->win_tools, posY, posX, WHITE, "Current level");

	posY += 2;
	window_mvprintw_col(interface->win_tools, posY, posX+3, WHITE, "< 001 >");

	posY += 2;
	window_mvprintw_col(interface->win_tools, posY, posX+3, RED, "DELETE");

	window_refresh(interface->win_tools);
}

void refresh_win_level(interface_t* interface){
	int i, j;
	element_map_t* element_select;

	for (i = 0; i < interface->game_level.width; i++)
	{
		for (j = 0; j < interface->game_level.height; j++)
		{
			window_mvaddch_col(interface->win_level, j, i, COLOR_BLACK, ' ');
		}
	}
	
	for (i = 0; i < interface->game_level.width; i++)
	{
		for (j = 0; j < interface->game_level.height; j++)
		{
			element_select = interface->game_level.elements_map[i][j];
			if(element_select != NULL && element_select->posX == i && element_select->posY == j){
				switch (element_select->id_sprite)
				{
					case SPRITE_BLOCK:
						paint_block(interface->win_level, element_select->posX, element_select->posY);
						break;
					
					case SPRITE_LADDER:
						paint_ladder(interface->win_level, element_select->posX, element_select->posY);
						break;

					case SPRITE_TRAP:
						paint_trap(interface->win_level, element_select->posX, element_select->posY);
						break;

					case SPRITE_GATE:
						paint_gate(interface->win_level, element_select->posX, element_select->posY, MAGENTA);
						break;

					case SPRITE_KEY:
						paint_key(interface->win_level, element_select->posX, element_select->posY);
						break;

					case SPRITE_DOOR:
						paint_door(interface->win_level, element_select->posX, element_select->posY);
						break;

					case SPRITE_EXIT:
						paint_exit(interface->win_level, element_select->posX, element_select->posY);
						break;

					case SPRITE_START:
						paint_start(interface->win_level, element_select->posX, element_select->posY);
						break;

					case SPRITE_ROBOT:
						paint_robot(interface->win_level, element_select->posX, element_select->posY);
						break;

					case SPRITE_PROBE:
						paint_probe(interface->win_level, element_select->posX, element_select->posY);
						break;

					case SPRITE_LIFE:
						paint_heart(interface->win_level, element_select->posX, element_select->posY);
						break;

					case SPRITE_BOMB:
						paint_bomb(interface->win_level, element_select->posX, element_select->posY);
						break;

					default:
						break;
				}
			}
		}
	}
	
	window_refresh(interface->win_level);
}