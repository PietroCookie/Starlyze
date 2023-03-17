#include "move_world.h"

#include <pthread.h>
#include <stdio.h>

int move_level(level_info_t *level, entity_t *entity_move, direction_enum direction, int number_collision, entity_t *collision){
	int validate = 1;
	int posX_dest = entity_move->posX, posY_dest = entity_move->posY;
	int zone_src, zone_dest;

	zone_src = (entity_move->posY / HEIGHT_ZONE_LEVEL) * (level->width / WIDTH_ZONE_LEVEL) + (entity_move->posX / WIDTH_ZONE_LEVEL);

	switch (direction)
	{
		case LEFT:
			posX_dest--;
			break;

		case RIGHT:
			posX_dest++;
			break;

		case UP:
			if(entity_move->type == PLAYER && level->map[entity_move->posX][entity_move->posY].type == SPRITE_LADDER)
				posY_dest--;
			break;

		case DOWN:
			if(entity_move->type == PLAYER && level->map[entity_move->posX][entity_move->posY].type == SPRITE_LADDER)
				posY_dest++;
			break;
		
		default:
			validate = 0;
			break;
	}

	if(posX_dest >= level->width || posX_dest < 0 || entity_move->posY >= level->height || posY_dest < 0 || level->map[posX_dest][posY_dest].type == SPRITE_BLOCK)
		validate = 0;

	if(validate){
		zone_dest = (posY_dest / HEIGHT_ZONE_LEVEL) * (level->width / WIDTH_ZONE_LEVEL) + (posX_dest / WIDTH_ZONE_LEVEL);
		if(pthread_mutex_lock(&level->mutex_zone[zone_src]) != 0){
			fprintf(stderr, "Error lock mutex in move_level");
			exit(EXIT_FAILURE);
		}
		if(zone_dest != zone_src)
			if(pthread_mutex_lock(&level->mutex_zone[zone_dest]) != 0){
				fprintf(stderr, "Error lock mutex in move_level");
				exit(EXIT_FAILURE);
			}

		entity_move->posX = posX_dest;
		entity_move->posY = posY_dest;
		


		if(pthread_mutex_unlock(&level->mutex_zone[zone_src]) != 0){
			fprintf(stderr, "Error unlock mutex in move_level");
			exit(EXIT_FAILURE);
		}
		if(zone_dest != zone_src)
			if(pthread_mutex_unlock(&level->mutex_zone[zone_dest]) != 0){
				fprintf(stderr, "Error lock mutex in move_level");
				exit(EXIT_FAILURE);
			}
	}

	return validate;
}

int take_item(level_info_t *level, player_t *player, int posX, int posY){
	int validate = 1;



	return validate;
}

void drop_bomb(level_info_t *level, player_t *player, int posX, int posY){

}

void change_level(level_info_t *level_src, player_t *player, level_info_t *level_dest){

}

void enter_gate(level_info_t *level, player_t *player){

}