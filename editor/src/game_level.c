#include "game_level.h"

#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

void initialize_game_level(game_level_t* game_level, int width, int height){
	int i, j;

	game_level->width = width;
	game_level->height = height;

	if((game_level->elements_map = malloc(height * sizeof(element_map_t**))) == NULL){
		ncurses_stop();
		perror("Error allocating width elements of game");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < width; i++)
	{
		if((game_level->elements_map[i] = malloc(width * sizeof(element_map_t*))) == NULL){
			ncurses_stop();
			perror("Error allocating height elements of game");
			exit(EXIT_FAILURE);
		}

		for (j = 0; j < height; j++)
		{
			game_level->elements_map[i][j] = NULL;
		}
	}
}

void delete_game_level(game_level_t* game_level){
	int i, j;

	for (i = 0; i < game_level->width; i++)
	{
		for (j = 0; j < game_level->height; j++)
		{
			if(game_level->elements_map[i][j] == NULL){
				free(game_level->elements_map[i][j]);
			}
		}
		free(game_level->elements_map[i]);
	}
	
	free(game_level->elements_map);

	game_level->width = 0;
	game_level->height = 0;
}

void add_element_map_in_case(game_level_t* game_level, element_map_t* element){
	int i, j;

	for (i = element->posX; i < (element->posX + element->height); i++)
	{
		for (j = element->posY; j < (element->posY + element->width); j++)
		{
			if(game_level->elements_map[i][j] != NULL){
				printf("Suppression case %d %d\n", i ,j);
				delete_element_map_in_case(game_level, i, j);
			}
		}
	}

	for (i = element->posX; i < (element->posX + element->height); i++)
	{
		for (j = element->posY; j < (element->posY + element->width); j++)
		{
			game_level->elements_map[i][j] = element;
		}
	}
}

element_map_t* element_map_in_case(game_level_t game_level, int posX, int posY){
	return game_level.elements_map[posX][posY];
}

void delete_element_map_in_case(game_level_t* game_level, int posX, int posY){
	element_map_t* element_delete;	
	int i, j;

	if((element_delete = game_level->elements_map[posX][posY]) == NULL){
		return;
	}

	for (i = element_delete->posX; i < (element_delete->posX + element_delete->height); i++)
	{
		for (j = element_delete->posY; j < (element_delete->posY + element_delete->width); j++)
		{
			game_level->elements_map[i][j] = NULL;
			printf("Bonjour %d %d\n", i, j);
		}
	}
}