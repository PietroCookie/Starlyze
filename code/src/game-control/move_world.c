#include "move_world.h"

#include <pthread.h>
#include <stdio.h>

#include "sprite.h"

int move_level(level_info_t *level, entity_t *entity_move, direction_enum direction, int number_collision, entity_t *collision){
	int validate = 1;
	int posX_dest = entity_move->posX, posY_dest = entity_move->posY;
	int posX_width, posY_height;
	int zone_dest;
	int zone_src[2];
	type_sprite_enum type_sprite;

	if(entity_move->type == ENEMY && entity_move->enemy.type == PROBE)
		type_sprite = SPRITE_PROBE;
	else
		type_sprite = SPRITE_ROBOT;

	posX_width = entity_move->posX + width_sprite(type_sprite)-1;
	posY_height = entity_move->posY + height_sprite(type_sprite)-1;

	zone_src[0] = (entity_move->posY / HEIGHT_ZONE_LEVEL) * (WIDTH_LEVEL / WIDTH_ZONE_LEVEL) + (entity_move->posX / WIDTH_ZONE_LEVEL);
	zone_src[1] = (posY_height / HEIGHT_ZONE_LEVEL) * (WIDTH_LEVEL / WIDTH_ZONE_LEVEL) + (posX_width / WIDTH_ZONE_LEVEL);

	switch (direction)
	{
		case LEFT:
			posX_dest--;
			posX_width--;
			break;

		case RIGHT:
			posX_dest++;
			posX_width++;
			break;

		case UP:
			if((entity_move->type == PLAYER && level->map[entity_move->posX][entity_move->posY].type == SPRITE_LADDER) || (entity_move->type == ENEMY && entity_move->enemy.type == PROBE)) {
				posY_dest--;
				posY_height--;
			}
			break;

		case DOWN:
			if((entity_move->type == PLAYER && level->map[entity_move->posX][entity_move->posY].type == SPRITE_LADDER) || (entity_move->type == ENEMY && entity_move->enemy.type == PROBE)) {
				posY_dest++;
				posY_height++;
			}
			break;
		
		default:
			validate = 0;
			break;
	}

	validate = check_validation_move(level, posX_dest, posY_dest, type_sprite, direction);

	if(validate){
		zone_dest = (posY_dest / HEIGHT_ZONE_LEVEL) * (WIDTH_LEVEL / WIDTH_ZONE_LEVEL) + (posX_dest / WIDTH_ZONE_LEVEL);
		if(pthread_mutex_lock(&level->mutex_zone[zone_src[0]]) != 0){
			fprintf(stderr, "Error lock mutex in move_level");
			exit(EXIT_FAILURE);
		}
		if(zone_dest != zone_src[0])
			if(pthread_mutex_lock(&level->mutex_zone[zone_dest]) != 0){
				fprintf(stderr, "Error lock mutex in move_level");
				exit(EXIT_FAILURE);
			}

		entity_move->posX = posX_dest;
		entity_move->posY = posY_dest;
		


		if(pthread_mutex_unlock(&level->mutex_zone[zone_src[0]]) != 0){
			fprintf(stderr, "Error unlock mutex in move_level");
			exit(EXIT_FAILURE);
		}
		if(zone_dest != zone_src[0])
			if(pthread_mutex_unlock(&level->mutex_zone[zone_dest]) != 0){
				fprintf(stderr, "Error lock mutex in move_level");
				exit(EXIT_FAILURE);
			}
	}

	return validate;
}

int check_validation_move(level_info_t *level, int posX_dest, int posY_dest, type_sprite_enum type_sprite, direction_enum direction){
	int validate = 1;
	int posX_width, posY_height;
	int x = posX_dest, y = posY_dest;

	posX_width = posX_dest + width_sprite(type_sprite)-1;
	posY_height = posY_dest + height_sprite(type_sprite)-1;

	if(posX_width >= WIDTH_LEVEL || posX_dest < 0 || posY_height >= HEIGHT_LEVEL || posY_dest < 0)
		validate = 0;


	while (validate && x <= posX_width)
	{
		if(level->map[x][y].type == SPRITE_BLOCK)
			validate = 0;

		y++;
		if(y > posY_height) {
			y = posY_dest;
			x++;
		}
	}

	if(validate && type_sprite != SPRITE_PROBE && (direction == LEFT || direction == RIGHT)) {
		if((level->map[posX_dest][posY_height+1].type != SPRITE_BLOCK && level->map[posX_dest][posY_height+1].type != SPRITE_LADDER)
			|| (level->map[posX_width][posY_height+1].type != SPRITE_BLOCK && level->map[posX_width][posY_height+1].type != SPRITE_LADDER))
			validate = 0;
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