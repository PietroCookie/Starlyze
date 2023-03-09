#include <stdlib.h>

#include "functions.h"
#include "interface.h"

#include <stdio.h>

int main(int argc, char const *argv[])
{
	int ch;
	interface_t* interface;
	bool quit = FALSE;

	if(argc != 2){
		fprintf(stderr, "Missing parameters : name of game file\n");
		exit(EXIT_FAILURE);
	}

	// ncurses initialisation
    setlocale(LC_ALL, "");
	ncurses_init();
	ncurses_init_mouse();
	ncurses_colors();
	palette();
	clear();
	refresh();

	interface = interface_create(argv[1]);

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
