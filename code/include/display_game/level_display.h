#ifndef __LEVEL_DISPLAY_H__
#define __LEVEL_DISPLAY_H__

#include "level_info.h"

#include "entity.h"

<<<<<<< HEAD
#define SPECIFICATION_DOOR 100
#define SPECIFICATION_GATE 200
#define SPECIFICATION_KEY 300
#define SPECIFICATION_TRAP 400
=======
#define INTERVALLE_SPECIFICATION 100

#define SPECIFICATION_DOOR 100
#define SPECIFICATION_GATE (SPECIFICATION_DOOR + INTERVALLE_SPECIFICATION)
#define SPECIFICATION_KEY (SPECIFICATION_GATE + INTERVALLE_SPECIFICATION)
>>>>>>> main

typedef struct
{
	int tab[WIDTH_LEVEL][HEIGHT_LEVEL];
} level_display_t;


void convert_level_info(level_display_t *level_display, level_info_t level_info, entity_t *enemies, int number_enemies);

#endif