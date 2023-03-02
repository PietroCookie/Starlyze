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

	result->win_level = window_create(0, 0, 62, 22, "Level", FALSE);
	initialise_win_level(result);
	window_refresh(result->win_level);

	result->win_tools = window_create(62, 0, 15, 22, "Tools", TRUE);
	initialise_win_tools(result);
	window_refresh(result->win_tools);

	result->win_infos = window_create(0, 22, 77, 5, "Informations", TRUE);
	window_printw_col(result->win_infos, RED, "Press 'Q' to exit");
	window_refresh(result->win_infos);

	result->paint_tool.id_tool = -1;

	return result;
}

void interface_delete(interface_t **interface) {
    window_delete(&(*interface)->win_infos);
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
			action_tool(interface->win_level, interface->win_infos, interface->paint_tool, posX, posY);
		}
	}
}

void initialise_win_level(interface_t* interface){
	int i;

	for (i = 0; i < 60; i++)
	{
		paint_block(interface->win_level, i, 0);
		paint_block(interface->win_level, i, 19);
	}
	for (i = 0; i < 19; i++)
	{
		paint_block(interface->win_level, 0, i);
		paint_block(interface->win_level, 59, i);
	}
	
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