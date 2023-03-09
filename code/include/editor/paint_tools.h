#ifndef __PAINT_TOOLS_H__
#define __PAINT_TOOLS_H__

#include "window.h"
#include "game_level.h"
#include "file_game_level.h"

typedef struct
{
	int id_tool;
	char* name_tool;
} paint_tool_t;

int select_paint_tool(paint_tool_t* tool, int id_tool);

void action_tool(file_game_level_t* file_game_level, game_level_t* game_level, window_t* win_infos, paint_tool_t tool, int posX, int posY, int specification);

char* select_name_tool(int tool);

void print_paint_tool(window_t* win_tools, int tool_select, int id_door, int id_gate, int id_key);

#endif