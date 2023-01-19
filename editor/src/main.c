#include <stdlib.h>

#include "functions.h"
#include "interface.h"

#include "map_level.h"
#include "element_map.h"

void test(){

	map_level_t map;
	initialize_map_level(&map);

	element_map_t* element_map;
	element_map = malloc(sizeof(element_map_t));
	element_map->id_sprite = 1;
	element_map->posX = 1;
	element_map->posY = 2;
	element_map->width = 1;
	element_map->heigt = 1;

	add_element_map(&map, *element_map);

	printf("Recherche de l'element : ");
	fflush(stdout);
	element_map = search_element_with_position_map(map, 1, 2);
	if(element_map != NULL)
		printf("Element trouve !!\n");
	else
		printf("Element pas trouve !!\n");

	printf("Recherche de la cellule : ");
	fflush(stdout);
	cellule_t* cellule = search_cellule_element_with_position_map(map, 1, 2);
	if(cellule != NULL)
		printf("Element trouve !!\n");
	else
		printf("Element pas trouve !!\n");

	free(element_map);
	free(cellule);
}

int main(int argc, char const *argv[])
{
	// int ch;
	// interface_t* interface;
	// bool quit = FALSE;

	// // ncurses initialisation
    // setlocale(LC_ALL, "");
	// ncurses_init();
	// ncurses_init_mouse();
	// ncurses_colors();
	// palette();
	// clear();
	// refresh();

	// interface = interface_create();

	// // Main loop
	// while (quit == FALSE)
	// {
	// 	ch = getch();
	// 	if((ch == 'Q') || (ch == 'q'))
	// 		quit = TRUE;
	// 	else
	// 		interface_actions(interface, ch);
	// }

	// // Stop ncurses
	// ncurses_stop();

	// interface_delete(&interface);
	test();
	
	return EXIT_SUCCESS;
}
