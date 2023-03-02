#ifndef __PAINT_TOOLS_H__
#define __PAINT_TOOLS_H__

#include "window.h"

typedef struct
{
	int id_tool;
	char* name_tool;
} paint_tool_t;

int select_paint_tool(window_t* win_tools, paint_tool_t* tool, int id_tool);

void action_tool(window_t* win_level, window_t* win_infos, paint_tool_t tool, int posX, int posY);

char* select_name_tool(int tool);

void print_paint_tool(window_t* win_tools, int tool_select);

#endif