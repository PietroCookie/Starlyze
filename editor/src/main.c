#include <stdlib.h>

#include "functions.h"
#include "interface.h"

#include <stdio.h>

int main(int argc, char const *argv[])
{
	int ch;
	interface_t* interface;
	bool quit = FALSE;

	// ncurses initialisation
    setlocale(LC_ALL, "");
	ncurses_init();
	ncurses_init_mouse();
	ncurses_colors();
	palette();
	clear();
	refresh();

	interface = interface_create();

	// Main loop
	while (quit == FALSE)
	{
		ch = getch();
		if((ch == 'Q') || (ch == 'q'))
			quit = TRUE;
		else
			interface_actions(interface, ch);
	}

	// Stop ncurses
	ncurses_stop();

	interface_delete(&interface);
	
	return EXIT_SUCCESS;
}
