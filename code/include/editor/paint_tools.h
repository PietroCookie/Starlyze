/**
 * @file paint_tools.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manage a paint_tool
 * @version 0.1
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __PAINT_TOOLS_H__
#define __PAINT_TOOLS_H__

#include "window.h"
#include "game_level.h"
#include "file_game_level.h"

/**
 * @brief A paint tool
 * 
 */
typedef struct
{
	int id_tool;
	char* name_tool;
} paint_tool_t;

/**
 * @brief Selects a paint_tool based on its id
 * 
 * @param tool The paint_tool in which we select
 * @param id_tool The id of the desired paint_tool
 * @return int The id of the paint_tool or -1 if the paint_tool does not exist
 */
int select_paint_tool(paint_tool_t* tool, int id_tool);

/**
 * @brief Use the tool on a square of a game_level
 * 
 * @param file_game_level The file_game_level in which the modification is saved
 * @param game_level The game_level in which the modification is made
 * @param win_infos The information window of the interface
 * @param tool The tool used
 * @param posX Position X of the modified cell
 * @param posY Position Y of the modified cell
 * @param specification The specification associated with the element in the box
 */
void action_tool(file_game_level_t* file_game_level, game_level_t* game_level, window_t* win_infos, paint_tool_t tool, int posX, int posY, int specification);

/**
 * @brief Selects the name of the tool according to its identifier
 * 
 * @param tool The identifier of the tool whose name we want to know
 * @return char* The name of the tool
 */
char* select_name_tool(int tool);

/**
 * @brief Displays the list of available tools in a window
 * 
 * @param win_tools The window in which the list of tools is displayed
 * @param tool_select The selected tool
 * @param id_door The identifier of the door selected to display it
 * @param id_gate The identifier of the portal selected to display it
 * @param id_key The identifier of the key selected to display its
 */
void print_paint_tool(window_t* win_tools, int tool_select, int id_door, int id_gate, int id_key);

#endif