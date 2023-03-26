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

	posX_width = entity_move->posX + width_sprite(entity_move->type)-1;
	posY_height = entity_move->posY + height_sprite(entity_move->type)-1;

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
			if((entity_move->type == SPRITE_PLAYER && (level->map[entity_move->posX][entity_move->posY].type == SPRITE_LADDER || level->map[entity_move->posX][posY_height].type == SPRITE_LADDER))
				|| (entity_move->type  == SPRITE_PROBE) ) {
				posY_dest--;
				posY_height--;
			}
			break;

		case DOWN:
			if((entity_move->type == SPRITE_PLAYER && level->map[entity_move->posX][entity_move->posY].type == SPRITE_LADDER) || (entity_move->type == SPRITE_PROBE)) {
				posY_dest++;
				posY_height++;
			}
			break;
		
		default:
			validate = 0;
			break;
	}

	validate = check_validation_move(level, posX_dest, posY_dest, entity_move->type, direction);

	if(validate && entity_move->type != SPRITE_PLAYER) {
		if(level->map[posX_dest][posY_height+1].type == SPRITE_TRAP || level->map[posX_width][posY_height+1].type == SPRITE_TRAP)
			validate = 0;
	}

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
		if((level->map[posX_dest][posY_height+1].type != SPRITE_BLOCK && level->map[posX_dest][posY_height+1].type != SPRITE_LADDER && level->map[posX_dest][posY_height+1].type != SPRITE_TRAP)
			|| (level->map[posX_width][posY_height+1].type != SPRITE_BLOCK && level->map[posX_width][posY_height+1].type != SPRITE_LADDER && level->map[posX_width][posY_height+1].type != SPRITE_TRAP))
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

void enter_door(world_info_t *world_info, entity_t *player) {
	
}

void enter_gate(level_info_t *level, entity_t *player){
	int i = 0, j = 0, posX, posY, id_gate = -1;
	int zone_player, zone_dest;
	int validate = 0;

	zone_player = (player->posY / HEIGHT_ZONE_LEVEL) * (WIDTH_LEVEL / WIDTH_ZONE_LEVEL) + (player->posX / WIDTH_ZONE_LEVEL);

	if(pthread_mutex_lock(&level->mutex_zone[zone_player]) != 0) {
		fprintf(stderr, "Error lock zone mutex in enter_gate\n");
		exit(EXIT_FAILURE);
	}


	posY = player->posY;
	if(level->map[player->posX][player->posY].type == SPRITE_GATE) {
		id_gate = level->map[player->posX][player->posY].specification;
		posX = player->posX;
	}
	else if(level->map[player->posX+1][player->posY].type == SPRITE_GATE) {
		id_gate = level->map[player->posX+1][player->posY].specification;
		posX = player->posX+1;
	}
	else if(level->map[player->posX+2][player->posY].type == SPRITE_GATE) {
		id_gate = level->map[player->posX+2][player->posY].specification;
		posX = player->posX+2;
	}


	if(id_gate != -1) {
		while (!validate && j < HEIGHT_LEVEL)
		{
			if(level->map[i][j].type == SPRITE_GATE && level->map[i][j].specification == id_gate && (i != posX || j != posY) && !(i == posX && j >= posY && j <= posY+height_sprite(SPRITE_GATE)))
				validate = 1;
			else {
				i++;
				if(i >= WIDTH_LEVEL) {
					j++;
					i = 0;
				}
			}
		}

		if(validate) {
			zone_dest = (j / HEIGHT_ZONE_LEVEL) * (WIDTH_LEVEL / WIDTH_ZONE_LEVEL) + (i / WIDTH_ZONE_LEVEL);
			if(zone_dest != zone_player)
				if(pthread_mutex_lock(&level->mutex_zone[zone_dest]) != 0) {
					fprintf(stderr, "Error lock zone mutex in enter_gate\n");
					exit(EXIT_FAILURE);
				}

			player->posX = i;
			player->posY = j;

			if(zone_dest != zone_player)
				if(pthread_mutex_unlock(&level->mutex_zone[zone_dest]) != 0) {
					fprintf(stderr, "Error unlock zone mutex in enter_gate\n");
					exit(EXIT_FAILURE);
				}
		}
		else
			printf("Gate non trouve !\n");
	}


	if(pthread_mutex_unlock(&level->mutex_zone[zone_player]) != 0) {
		fprintf(stderr, "Error unlock zone mutex in enter_gate\n");
		exit(EXIT_FAILURE);
	}
}