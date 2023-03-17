#include "game_level.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void initialise_game_level(game_level_t* game_level){
	int i, j;

	for (i = 0; i < WIDTH_LEVEL_GAME; i++)
		for (j = 0; j < HEIGHT_LEVEL_GAME; j++)
			game_level->elements_map[i][j] = NULL;
}

void delete_game_level(game_level_t* game_level){
	int i, j;
	element_game_level_t* element_delete;

	for (i = 0; i < WIDTH_LEVEL_GAME; i++)
		for (j = 0; j < HEIGHT_LEVEL_GAME; j++)
			if((element_delete = game_level->elements_map[i][j]) != NULL){
				delete_element_map_in_case(game_level, i, j);
				free(element_delete);
			}
}

void add_element_map_in_case(game_level_t* game_level, element_game_level_t* element){
	int i, j;

	for (i = element->posX; i < (element->posX + element->width); i++)
		for (j = element->posY; j < (element->posY + element->height); j++)
			if(game_level->elements_map[i][j] != NULL)
				delete_element_map_in_case(game_level, i, j);

	for (i = element->posX; i < (element->posX + element->width); i++)
		for (j = element->posY; j < (element->posY + element->height); j++)
			game_level->elements_map[i][j] = element;
}

void delete_element_map_in_case(game_level_t* game_level, int posX, int posY){
	element_game_level_t* element_delete;
	int i, j;

	if((element_delete = game_level->elements_map[posX][posY]) == NULL)
		return;

	for (i = element_delete->posX; i < (element_delete->posX + element_delete->width); i++)
		for (j = element_delete->posY; j < (element_delete->posY + element_delete->height); j++)
			game_level->elements_map[i][j] = NULL;
}

size_t necessary_size_game_level(game_level_t game_level){
	size_t size;

	size = WIDTH_LEVEL_GAME * HEIGHT_LEVEL_GAME * necessary_size_element_game_level();

	return size;
}

void save_modification_game_level_in_file_descriptor(int file_descriptor, off_t position, game_level_t game_level, int posX, int posY){
	element_game_level_t element_write = {posX, posY, 0, 0, {0, -1}};

	position += 2 * sizeof(int); // Size of width and height save
	position += posX * HEIGHT_LEVEL_GAME * necessary_size_element_game_level() + posY * necessary_size_element_game_level(); // Move to position of element to save

	if(lseek(file_descriptor, position, SEEK_SET) == -1){
		perror("Error lseek in save_modification_game_level_in_file_descriptor");
		exit(EXIT_FAILURE);
	}

	if(game_level.elements_map[posX][posY] != NULL)
		element_write = *game_level.elements_map[posX][posY];
	
	write_element_game_level_in_file_descriptor(file_descriptor, element_write);
}

void write_game_level_in_file_descriptor(int file_descriptor, game_level_t game_level){
	int i, j;
	element_game_level_t element_game_level;

	for (i = 0; i < WIDTH_LEVEL_GAME; i++)
		for (j = 0; j < HEIGHT_LEVEL_GAME; j++) {
			if(game_level.elements_map[i][j] == NULL || game_level.elements_map[i][j]->posX != i || game_level.elements_map[i][j]->posY != j){
				element_game_level.posX = -1;
				element_game_level.posY = -1;
				element_game_level.width = 1;
				element_game_level.height = 1;
				element_game_level.sprite.type = 0;
				element_game_level.sprite.specification = -1;
			}else{
				element_game_level = *game_level.elements_map[i][j];
			}

			write_element_game_level_in_file_descriptor(file_descriptor, element_game_level);
		}
}

void read_game_level_in_file_descriptor(int file_descriptor, game_level_t* game_level){
	int i, j;
	element_game_level_t* element_read;

	initialise_game_level(game_level);

	for (i = 0; i < WIDTH_LEVEL_GAME; i++)
		for (j = 0; j < HEIGHT_LEVEL_GAME; j++)
			if((element_read = read_element_game_level_in_file_descriptor(file_descriptor, i, j)) != NULL){
				add_element_map_in_case(game_level, element_read);
			}
}
