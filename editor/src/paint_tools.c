#include "paint_tools.h"

#include <string.h>

#include "colors.h"
#include "sprite.h"

int select_paint_tool(window_t* win_tools, paint_tool_t* tool, int id_tool){
	if(id_tool >= 0 && id_tool < 13)
		tool->id_tool = id_tool;
	else
		tool->id_tool = -1;

	tool->name_tool = select_name_tool(tool->id_tool);
	print_paint_tool(win_tools, tool->id_tool);

	return tool->id_tool;
}

void action_tool(window_t* win_level, window_t* win_infos, paint_tool_t tool, int posX, int posY){
	switch (tool.id_tool)
	{
		case 1:
			paint_block(win_level, posX, posY);
			break;

		case 2:
			paint_ladder(win_level, posX, posY);
			break;

		case 3:
			paint_trap(win_level, posX, posY);
			break;

		case 4:
			paint_gate(win_level, posX, posY, MAGENTA);
			break;

		case 5:
			paint_key(win_level, posX, posY);
			break;

		case 6:
			paint_door(win_level, posX, posY);
			break;

		case 7:
			paint_exit(win_level, posX, posY);
			break;

		case 8:
			paint_start(win_level, posX, posY);
			break;

		case 9:
			paint_robot(win_level, posX, posY);
			break;

		case 10:
			paint_probe(win_level, posX, posY);
			break;

		case 11:
			paint_heart(win_level, posX, posY);
			break;

		case 12:
			paint_bomb(win_level, posX, posY);
			break;
		
		default:
			window_printw(win_infos, "\nL'outil souhaite n'existe pas");
			window_refresh(win_infos);
			break;
	}
}

char* select_name_tool(int id_tool){
	char* name_tool;

	switch (id_tool)
	{
		case 0:
			name_tool = "Delete";
			break;

		case 1:
			name_tool = "Block";
			break;

		case 2:
			name_tool = "Ladder";
			break;

		case 3:
			name_tool = "Trap";
			break;

		case 4:
			name_tool = "Gate";
			break;

		case 5:
			name_tool = "Key";
			break;

		case 6:
			name_tool = "Door";
			break;

		case 7:
			name_tool = "Exit";
			break;

		case 8:
			name_tool = "Start";
			break;

		case 9:
			name_tool = "Robot";
			break;

		case 10:
			name_tool = "Probe";
			break;

		case 11:
			name_tool = "Life";
			break;

		case 12:
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