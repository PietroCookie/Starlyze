#include "level_display.h"

#include "level_info.h"
#include "sprite.h"
#include "entity.h"

#include <stdio.h>

void convert_level_info(int id_level, level_display_t *level_display, level_info_t level_info, entity_t *enemies, int number_enemies, entity_t *players, int number_players) {
	int i, j, m, n;
	type_sprite_enum type_sprite;

	for (i = 0; i < WIDTH_LEVEL; i++)
		for (j = 0; j < HEIGHT_LEVEL; j++)
		{
			type_sprite = level_info.map[i][j].type;
			switch (type_sprite)
			{
			case SPRITE_DOOR:
				level_display->tab[i][j] = SPECIFICATION_DOOR + level_info.map[i][j].specification;
				break;

			case SPRITE_GATE:
				level_display->tab[i][j] = SPECIFICATION_GATE + level_info.map[i][j].specification;
				break;

			case SPRITE_KEY:
				level_display->tab[i][j] = SPECIFICATION_KEY + level_info.map[i][j].specification;
				break;

			case SPRITE_TRAP:
				if(level_info.map[i][j].specification < 0)
					level_display->tab[i][j] = 0;
				else
					level_display->tab[i][j] = SPRITE_TRAP;
				break;
			
			default:
				level_display->tab[i][j] = level_info.map[i][j].type;
				break;
			}

			for (m = i; m < i+width_sprite(type_sprite); m++)
				for (n = j; n < j+height_sprite(type_sprite); n++)
					level_info.map[m][n].type = 0;
		}


	for (i = 0; i < number_enemies; i++)
		level_display->tab[enemies[i].posX][enemies[i].posY] = enemies[i].type;
	
	for (i = 0; i < number_players; i++)
		if(players[i].player.level == id_level)
			level_display->tab[players[i].posX][players[i].posY] = SPECIFICATION_PLAYERS + players[i].player.id;
	
}
