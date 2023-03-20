#include "level_display.h"

#include "level_info.h"
#include "sprite.h"
#include "entity.h"

void convert_level_info(level_display_t *level_display, level_info_t *level_info, entity_t *enemies, int number_enemies) {
	int i, j;

	if(pthread_mutex_lock(&level_info->mutex_level) != 0) {
		fprintf(stderr, "Error lock mutex level in convert_level_info");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < WIDTH_LEVEL; i++)
		for (j = 0; j < HEIGHT_LEVEL; j++)
		{
			switch (level_info->map[i][j].type)
			{
			case SPRITE_DOOR:
				level_display->tab[i][j] = SPECIFICATION_DOOR + level_info->map[i][j].specification;
				break;

			case SPRITE_GATE:
				level_display->tab[i][j] = SPECIFICATION_GATE + level_info->map[i][j].specification;
				break;

			case SPRITE_KEY:
				level_display->tab[i][j] = SPECIFICATION_KEY + level_info->map[i][j].specification;
				break;

			case SPRITE_TRAP:
				level_display->tab[i][j] = SPECIFICATION_TRAP + level_info->map[i][j].specification;
				break;
			
			default:
				level_display->tab[i][j] = level_info->map[i][j].type;
				break;
			}
		}

	if(pthread_mutex_unlock(&level_info->mutex_level) != 0) {
		fprintf(stderr, "Error unlock mutex level in convert_level_info");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < number_enemies; i++)
		level_display->tab[enemies[i].posX][enemies[i].posY] = enemies[i].enemy.type;
	
}
