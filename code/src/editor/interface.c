#include "interface.h"

#include <stdio.h>

#include "functions.h"
#include "sprite.h"
#include "game_level.h"

void interface_dimensions(unsigned short width, unsigned short height) {
    if((COLS < width) || (LINES < height)) {
        ncurses_stop();
        fprintf(stderr, 
              "Terminal size is too small: actually w=%d,h=%d instead of l=%d,h=%d\n",
              COLS, LINES, width, height);
        exit(EXIT_FAILURE);
    } 
}

interface_t* interface_create(char *name_file_game){
	interface_t* result;

	interface_dimensions(77, 27);
	
	if((result = malloc(sizeof(interface_t))) == NULL){
		ncurses_stop();
		perror("Error allocating structure interface_t");
		exit(EXIT_FAILURE);
	}

	result->paint_tool.id_tool = 0;
	result->id_door = 1;
	result->id_gate = 1;
	result->id_key = 1;

	result->game_level = open_file_game_level(name_file_game, &result->file_game_level);

	result->win_level = window_create(0, 0, DEFAULT_WIDTH_INTERFACE_GAME, DEFAULT_HEIGHT_INTERFACE_GAME, "Level", FALSE);
	refresh_win_level(result);

	result->win_tools = window_create(DEFAULT_WIDTH_INTERFACE_GAME, 0, 15, DEFAULT_HEIGHT_INTERFACE_GAME, "Tools", TRUE);
	refresh_win_tools(result);
	window_refresh(result->win_tools);

	result->win_infos = window_create(0, 22, 77, 5, "Informations", TRUE);
	window_printw_col(result->win_infos, RED, "Press 'Q' to exit");
	window_refresh(result->win_infos);

	return result;
}

void interface_delete(interface_t **interface) {
    window_delete(&(*interface)->win_infos);
	window_delete(&(*interface)->win_level);
	window_delete(&(*interface)->win_tools);
	
	delete_game_level(&(*interface)->game_level);
	delete_file_game_level(&(*interface)->file_game_level);

    free(*interface);
    interface = NULL;
}

void interface_actions(interface_t* interface, int c){
	int mouseX, mouseY, posX, posY, specification = -1;

	if((c == KEY_MOUSE) && (mouse_getpos(&mouseX, &mouseY) == OK)){
		#ifdef _DEBUG_
        window_printw(interface->win_infos, "\nClick (%d,%d)", mouseX, mouseY);
        window_refresh(interface->win_infos);
		#endif

		if(window_getcoordinates(interface->win_level, mouseX, mouseY, &posX, &posY)){
			if(interface->paint_tool.id_tool == SPRITE_DOOR)
				specification = interface->id_door;
			else if(interface->paint_tool.id_tool == SPRITE_GATE)
				specification = interface->id_gate;
			else if(interface->paint_tool.id_tool == SPRITE_KEY)
				specification = interface->id_key;
			action_tool(&interface->file_game_level, &interface->game_level, interface->win_infos, interface->paint_tool, posX, posY, specification);
			refresh_win_level(interface);
		}
		else if(window_getcoordinates(interface->win_tools, mouseX, mouseY, &posX, &posY)){
			if(posX == 3 && posY == 17){
				delete_game_level(&interface->game_level);
				load_level_in_file(&interface->file_game_level, &interface->game_level, -1);
			}
			else if(posX == 9 && posY == 17){
				delete_game_level(&interface->game_level);
				load_level_in_file(&interface->file_game_level, &interface->game_level, 1);
			}
			else if((posX >= 3 || posX <= 8) && posY == 19){
				delete_game_level_in_file(&interface->file_game_level);
				delete_game_level(&interface->game_level);
				load_level_in_file(&interface->file_game_level, &interface->game_level, -1);
			}
			else if(posY == 4){
				if(posX == 7){
					if(interface->id_gate == 1)
						interface->id_gate = MAX_ID_GATE_KEY;
					else
						interface->id_gate--;
				}else if(posX == 12){
					if(interface->id_gate == MAX_ID_GATE_KEY)
						interface->id_gate = 1;
					else
						interface->id_gate++;
				}
				if(interface->paint_tool.id_tool != SPRITE_GATE)
					select_paint_tool(&interface->paint_tool, posY);
			}
			else if(posY == 5){
				if(posX == 7){
					if(interface->id_key == 1)
						interface->id_key = MAX_ID_GATE_KEY;
					else
						interface->id_key--;
				}else if(posX == 12){
					if(interface->id_key == MAX_ID_GATE_KEY)
						interface->id_key = 1;
					else
						interface->id_key++;
				}
				if(interface->paint_tool.id_tool != SPRITE_KEY)
					select_paint_tool(&interface->paint_tool, posY);
			}
			else if(posY == 6){
				if(posX == 7){
					if(interface->id_door == 1)
						interface->id_door = MAX_ID_DOOR;
					else
						interface->id_door--;
				}else if(posX == 12){
					if(interface->id_door == MAX_ID_DOOR)
						interface->id_door = 1;
					else
						interface->id_door++;
				}
				if(interface->paint_tool.id_tool != SPRITE_DOOR)
					select_paint_tool(&interface->paint_tool, posY);
			}
			else
				select_paint_tool(&interface->paint_tool, posY);

			refresh_win_level(interface);
			refresh_win_tools(interface);
		}
	}
}

void refresh_win_tools(interface_t* interface){
	int posX = 0;
	int posY = 15;
	char level_current[10];
	char level_select[8];
	
	print_paint_tool(interface->win_tools, interface->paint_tool.id_tool, interface->id_door, interface->id_gate, interface->id_key);

	sprintf(level_current, "Level %d", interface->file_game_level.current_index_address_table);
	window_mvprintw_col(interface->win_tools, posY, posX+2, WHITE, level_current);

	posY += 2;
	sprintf(level_select, "< %3d >", interface->file_game_level.current_index_address_table);
	window_mvprintw_col(interface->win_tools, posY, posX+3, WHITE, level_select);

	posY += 2;
	window_mvprintw_col(interface->win_tools, posY, posX+3, RED, "DELETE");

	window_refresh(interface->win_tools);
}

void refresh_win_level(interface_t* interface){
	int i, j;
	element_game_level_t* element_select;

	for (i = 0; i < WIDTH_LEVEL_GAME; i++)
		for (j = 0; j < HEIGHT_LEVEL_GAME; j++)
			window_mvaddch_col(interface->win_level, j, i, COLOR_BLACK, ' ');
	
	for (i = 0; i < WIDTH_LEVEL_GAME; i++)
		for (j = 0; j < HEIGHT_LEVEL_GAME; j++)
		{
			element_select = interface->game_level.elements_map[i][j];
			if(element_select != NULL && element_select->posX == i && element_select->posY == j)
				switch (element_select->sprite.type)
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
						paint_gate(interface->win_level, element_select->posX, element_select->posY, element_select->sprite.specification);
						break;

					case SPRITE_KEY:
						paint_key(interface->win_level, element_select->posX, element_select->posY, element_select->sprite.specification);
						break;

					case SPRITE_DOOR:
						paint_door(interface->win_level, element_select->posX, element_select->posY, element_select->sprite);
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
	
	window_refresh(interface->win_level);
}