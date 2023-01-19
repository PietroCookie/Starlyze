#include "paint_tools.h"

#include <string.h>

#include "colors.h"
#include "sprite.h"
#include "element_map.h"

int select_paint_tool(window_t* win_tools, paint_tool_t* tool, int id_tool){
	if(id_tool >= 0 && id_tool < 13)
		tool->id_tool = id_tool;
	else
		tool->id_tool = -1;

	tool->name_tool = select_name_tool(tool->id_tool);
	print_paint_tool(win_tools, tool->id_tool);

	return tool->id_tool;
}

void action_tool(map_level_t* map_level, window_t* win_level, window_t* win_infos, paint_tool_t tool, int posX, int posY){
	element_map_t* element_map;
	element_map = malloc(sizeof(element_map_t));
	element_map->posX = posX;
	element_map->posY = posY;

	switch (tool.id_tool)
	{
		case 0:
			element_map = search_element_with_position_map(*map_level, posX, posY);
			// if(element_map != NULL)
			window_printw(win_infos, "\nBonjour");
			window_refresh(win_infos);
			break;

		case SPRITE_BLOCK:
			element_map->id_sprite = SPRITE_BLOCK;
			element_map->width = 1;
			element_map->heigt = 1;
			add_element_map(map_level, *element_map);
			paint_block(win_level, posX, posY);
			break;

		case SPRITE_LADDER:
			element_map->id_sprite = SPRITE_LADDER;
			element_map->width = 3;
			element_map->heigt = 1;
			add_element_map(map_level, *element_map);
			paint_ladder(win_level, posX, posY);
			break;

		case SPRITE_TRAP:
			element_map->id_sprite = SPRITE_TRAP;
			element_map->width = 1;
			element_map->heigt = 1;
			add_element_map(map_level, *element_map);
			paint_trap(win_level, posX, posY);
			break;

		case SPRITE_GATE:
			element_map->id_sprite = SPRITE_GATE;
			element_map->width = 1;
			element_map->heigt = 4;
			add_element_map(map_level, *element_map);
			paint_gate(win_level, posX, posY, MAGENTA);
			break;

		case SPRITE_KEY:
			element_map->id_sprite = SPRITE_KEY;
			element_map->width = 1;
			element_map->heigt = 2;
			add_element_map(map_level, *element_map);
			paint_key(win_level, posX, posY);
			break;

		case SPRITE_DOOR:
			element_map->id_sprite = SPRITE_DOOR;
			element_map->width = 3;
			element_map->heigt = 4;
			add_element_map(map_level, *element_map);
			paint_door(win_level, posX, posY);
			break;

		case SPRITE_EXIT:
			element_map->id_sprite = SPRITE_EXIT;
			element_map->width = 3;
			element_map->heigt = 4;
			add_element_map(map_level, *element_map);
			paint_exit(win_level, posX, posY);
			break;

		case SPRITE_START:
			element_map->id_sprite = SPRITE_START;
			element_map->width = 3;
			element_map->heigt = 4;
			add_element_map(map_level, *element_map);
			paint_start(win_level, posX, posY);
			break;

		case SPRITE_ROBOT:
			element_map->id_sprite = SPRITE_ROBOT;
			element_map->width = 3;
			element_map->heigt = 4;
			add_element_map(map_level, *element_map);
			paint_robot(win_level, posX, posY);
			break;

		case SPRITE_PROBE:
			element_map->id_sprite = SPRITE_PROBE;
			element_map->width = 3;
			element_map->heigt = 2;
			add_element_map(map_level, *element_map);
			paint_probe(win_level, posX, posY);
			break;

		case SPRITE_LIFE:
			element_map->id_sprite = SPRITE_LIFE;
			element_map->width = 1;
			element_map->heigt = 1;
			add_element_map(map_level, *element_map);
			paint_heart(win_level, posX, posY);
			break;

		case SPRITE_BOMB:
			element_map->id_sprite = SPRITE_BOMB;
			element_map->width = 1;
			element_map->heigt = 1;
			add_element_map(map_level, *element_map);
			paint_bomb(win_level, posX, posY);
			break;
		
		default:
			window_printw(win_infos, "\nL'outil souhaite n'existe pas");
			window_refresh(win_infos);
			break;
	}

	free(element_map);
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