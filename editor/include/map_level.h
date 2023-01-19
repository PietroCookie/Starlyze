#ifndef __MAP_LEVEL_H__
#define __MAP_LEVEL_H__

#include "liste.h"
#include "element_map.h"

typedef struct{
	int id_map;
	liste_t liste_element_map;
} map_level_t;

void initialize_map_level(map_level_t* map);
void add_element_map(map_level_t* map, element_map_t element);
cellule_t* search_cellule_element_with_position_map(map_level_t map, int posX, int posY);
element_map_t* search_element_with_position_map(map_level_t map, int posX, int posY);
void delete_element_map(map_level_t* map, element_map_t element);

#endif