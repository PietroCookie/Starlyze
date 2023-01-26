#ifndef __GAME_LEVEL_H__
#define __GAME_LEVEL_H__

#define DEFAULT_WIDTH_LEVEL_GAME 60
#define DEFAULT_HEIGHT_LEVEL_GAME 20

typedef struct
{
	int posX;
	int posY;
	int width;
	int height;
	int id_sprite;
} element_map_t;

typedef struct
{
	int width;
	int height;
	element_map_t*** elements_map;
} game_level_t;


void initialize_game_level(game_level_t* game_level, int width, int height);

void delete_game_level(game_level_t* game_level);

void add_element_map_in_case(game_level_t* game_level, element_map_t* element);

element_map_t* element_map_in_case(game_level_t game_level, int posX, int posY);

void delete_element_map_in_case(game_level_t* game_level, int posX, int posY);

#endif