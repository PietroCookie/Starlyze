#include "paint_tools.h"

#include <string.h>

#include "colors.h"
#include "sprite.h"
#include "functions.h"
#include "element_game_level.h"

int select_paint_tool(window_t* win_tools, paint_tool_t* tool, int id_tool){
	if(id_tool >= 0 && id_tool < 13)
		tool->id_tool = id_tool;
	else
		tool->id_tool = -1;

	tool->name_tool = select_name_tool(tool->id_tool);
	print_paint_tool(win_tools, tool->id_tool);

	return tool->id_tool;
}

void action_tool(file_game_level_t* file_game_level, game_level_t* game_level, window_t* win_infos, paint_tool_t tool, int posX, int posY){
	int sprite_validate = 1, i, j;
	element_game_level_t* element_map, *element_delete;
	if((element_map = malloc(sizeof(element_game_level_t))) == NULL){
		ncurses_stop();
		perror("Error allocating memory");
		exit(EXIT_FAILURE);
	}

	element_map->sprite.specification = -1;

	switch (tool.id_tool)
	{
		case 0:
			if((element_delete = game_level->elements_map[posX][posY]) != NULL){
				delete_element_map_in_case(game_level, posX, posY);
				save_modification_game_level(file_game_level, *game_level, element_delete->posX, element_delete->posY);
				free(element_delete);
			}
			free(element_map);
			sprite_validate = 0;
			break;

		case SPRITE_BLOCK:
			element_map->sprite.type = SPRITE_BLOCK;
			break;

		case SPRITE_LADDER:
			element_map->sprite.type = SPRITE_LADDER;
			break;

		case SPRITE_TRAP:
			element_map->sprite.type = SPRITE_TRAP;
			break;

		case SPRITE_GATE:
			element_map->sprite.type = SPRITE_GATE;
			break;

		case SPRITE_KEY:
			element_map->sprite.type = SPRITE_KEY;
			break;

		case SPRITE_DOOR:
			element_map->sprite.type = SPRITE_DOOR;
			break;

		case SPRITE_EXIT:
			element_map->sprite.type = SPRITE_EXIT;
			break;

		case SPRITE_START:
			element_map->sprite.type = SPRITE_START;
			break;

		case SPRITE_ROBOT:
			element_map->sprite.type = SPRITE_ROBOT;
			break;

		case SPRITE_PROBE:
			element_map->sprite.type = SPRITE_PROBE;
			break;

		case SPRITE_LIFE:
			element_map->sprite.type = SPRITE_LIFE;
			break;

		case SPRITE_BOMB:
			element_map->sprite.type = SPRITE_BOMB;
			break;
		
		default:
			free(element_map);
			window_printw(win_infos, "\nL'outil souhaite n'existe pas");
			window_refresh(win_infos);
			sprite_validate = 0;
			break;
	}

	if(sprite_validate){
		element_map->posX = posX;
		element_map->posY = posY;
		element_map->width = width_sprite(element_map->sprite.type);
		element_map->height = height_sprite(element_map->sprite.type);

		for (i = element_map->posX; i < (element_map->posX + element_map->width); i++)
		{
			for (j = element_map->posY; j < (element_map->posY + element_map->height); j++)
			{
				if((element_delete = game_level->elements_map[i][j]) != NULL){
					delete_element_map_in_case(game_level, i, j);
					save_modification_game_level(file_game_level, *game_level, element_delete->posX, element_delete->posY);
					free(element_delete);
				}
			}
		}

		add_element_map_in_case(game_level, element_map);
		
		save_modification_game_level(file_game_level, *game_level, posX, posY);
	}

}

char* select_name_tool(int id_tool){
	char* name_tool;

	switch (id_tool)
	{
		case 0:
			name_tool = "Delete";
			break;

		case SPRITE_BLOCK:
			name_tool = "Block";
			break;

		case SPRITE_LADDER:
			name_tool = "Ladder";
			break;

		case SPRITE_TRAP:
			name_tool = "Trap";
			break;

		case SPRITE_GATE:
			name_tool = "Gate";
			break;

		case SPRITE_KEY:
			name_tool = "Key";
			break;

		case SPRITE_DOOR:
			name_tool = "Door";
			break;

		case SPRITE_EXIT:
			name_tool = "Exit";
			break;

		case SPRITE_START:
			name_tool = "Start";
			break;

		case SPRITE_ROBOT:
			name_tool = "Robot";
			break;

		case SPRITE_PROBE:
			name_tool = "Probe";
			break;

		case SPRITE_LIFE:
			name_tool = "Life";
			break;

		case SPRITE_BOMB:
			name_tool = "Bomb";
			break;
		
		default:
			name_tool = "";
			break;
	}

	return name_tool;
}

void print_paint_tool(window_t* win_tools, int tool_select){
	int i;
	char complete_name[15];

	for (i = 0; i < 13; i++)
	{
		if(i == tool_select){
			strcpy(complete_name, "> ");
			strcat(complete_name, select_name_tool(i));
			window_mvprintw_col(win_tools, i, 0, WHITE, complete_name);
		}
		else{
			strcpy(complete_name, "  ");
			strcat(complete_name, select_name_tool(i));
			window_mvprintw_col(win_tools, i, 0, RED, complete_name);
		}
	}

	window_refresh(win_tools);
}