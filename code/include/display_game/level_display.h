#ifndef __LEVEL_DISPLAY_H__
#define __LEVEL_DISPLAY_H__

#include "level_info.h"

#include "entity.h"

#define INTERVALLE_SPECIFICATION 100

#define SPECIFICATION_DOOR 100
#define SPECIFICATION_GATE (SPECIFICATION_DOOR + INTERVALLE_SPECIFICATION)
#define SPECIFICATION_KEY (SPECIFICATION_GATE + INTERVALLE_SPECIFICATION)
#define SPECIFICATION_PLAYERS (SPECIFICATION_KEY + INTERVALLE_SPECIFICATION)

typedef struct
{
	int tab[WIDTH_LEVEL][HEIGHT_LEVEL];
} level_display_t;


void convert_level_info(int id_level, level_display_t *level_display, level_info_t level_info, entity_t *enemies, int number_enemies, entity_t *players, int number_players);

#endif