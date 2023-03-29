#include "move_world.h"

#include <pthread.h>
#include <stdio.h>

#include "sprite.h"

int move_level(level_info_t *level, entity_t *entity_move, direction_enum direction, int number_collision, entity_t *collision){
	int validate = 1;
	int posX_dest = entity_move->posX, posY_dest = entity_move->posY;
	int posX_width = posX_dest, posY_height = posY_dest;
	int zone_dest;
	int zone_src[2];

	if(entity_move->type == PLAYER) {
		posX_width = entity_move->posX + width_sprite(SPRITE_PLAYER)-1;
		posY_height = entity_move->posY + height_sprite(SPRITE_PLAYER)-1;
	}
	else if(entity_move->type == ENEMY) {
		if(entity_move->enemy.type == PROBE) {
			posX_width = entity_move->posX + width_sprite(SPRITE_PROBE)-1;
			posY_height = entity_move->posY + height_sprite(SPRITE_PROBE)-1;
		}
		else if(entity_move->enemy.type == ROBOT) {
			posX_width = entity_move->posX + width_sprite(SPRITE_ROBOT)-1;
			posY_height = entity_move->posY + height_sprite(SPRITE_ROBOT)-1;
		}
	}

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
			if((entity_move->type == PLAYER && (level->map[entity_move->posX][entity_move->posY].type == SPRITE_LADDER || level->map[entity_move->posX][posY_height].type == SPRITE_LADDER))
				|| (entity_move->type == ENEMY && entity_move->enemy.type  == PROBE) ) {
				posY_dest--;
				posY_height--;
			}
			break;

		case DOWN:
			if((entity_move->type == PLAYER && (level->map[entity_move->posX][entity_move->posY].type == SPRITE_LADDER || level->map[entity_move->posX][posY_height+1].type == SPRITE_LADDER)) 
				|| (entity_move->type == ENEMY && entity_move->enemy.type == PROBE)) {
				posY_dest++;
				posY_height++;
			}
			break;
		
		default:
			validate = 0;
			break;
	}

	if(posX_width >= WIDTH_LEVEL || posX_dest < 0 || posY_height >= HEIGHT_LEVEL || posY_dest < 0)
		validate = 0;

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


		validate = check_validation_move(level, posX_dest, posY_dest, posX_width, posY_height, entity_move);

		if(validate) {
			entity_move->posX = posX_dest;
			entity_move->posY = posY_dest;
			if(entity_move->type == PLAYER)
				take_item(level, &entity_move->player, posX_dest, posY_dest, posX_width, posY_height);
		}


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

int check_validation_move(level_info_t *level, int posX_dest, int posY_dest, int posX_width, int posY_height, entity_t *entity_move){
	int validate = 1;
	int x = posX_dest, y = posY_dest;


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


	if(validate){
		if(entity_move->type == ENEMY)
			validate = check_validation_move_enemy(level, posX_dest, posY_dest, posX_width, posY_height, entity_move);
		else if(entity_move->type == PLAYER)
			validate = check_validation_move_player(level, posX_dest, posY_dest, posX_width, posY_height, entity_move);
	}

	return validate;
}

int check_validation_move_enemy(level_info_t *level, int posX_dest, int posY_dest, int posX_width, int posY_height, entity_t *entity_move) {
	int validate = 1;
	int i = posX_dest, j = posY_dest;

	while (validate && j <= posY_height)
	{
		if(level->map[i][j].type == SPRITE_TRAP || level->map[i][j].type == SPRITE_BLOCK) {
			validate = 0;
		}

		i++;
		if(i > posX_width) {
			i = posX_dest;
			j++;
		}
	}
	

	if(validate && entity_move->enemy.type != PROBE) {
		if((level->map[posX_dest][posY_height+1].type != SPRITE_BLOCK && level->map[posX_dest][posY_height+1].type != SPRITE_LADDER)
			|| (level->map[posX_width][posY_height+1].type != SPRITE_BLOCK && level->map[posX_width][posY_height+1].type != SPRITE_LADDER))
			validate = 0;
	}

	return validate;
}

int check_validation_move_player(level_info_t *level, int posX_dest, int posY_dest, int posX_width, int posY_height, entity_t *entity_move) {
	int validate = 1;
	int i = posX_dest, j = posY_dest;

	while (validate && j <= posY_height)
	{
		if((level->map[i][j].type == SPRITE_TRAP && level->map[i][j].specification > 0) || level->map[i][j].type == SPRITE_BLOCK)
			validate = 0;

		if(level->map[i][j].type == SPRITE_GATE && !entity_move->player.key[level->map[i][j].specification])
			validate = 0;

		i++;
		if(i > posX_width) {
			i = posX_dest;
			j++;
		}
	}

	if((level->map[posX_dest][posY_height+1].type != SPRITE_BLOCK && level->map[posX_dest][posY_height+1].type != SPRITE_LADDER && !(level->map[posX_dest][posY_height+1].type == SPRITE_TRAP && level->map[posX_dest][posY_height+1].specification > 0)) ||
		(level->map[posX_width][posY_height+1].type != SPRITE_BLOCK && level->map[posX_width][posY_height+1].type != SPRITE_LADDER && !(level->map[posX_width][posY_height+1].type == SPRITE_TRAP && level->map[posX_width][posY_height+1].specification > 0)))
			validate = 0;


	return validate;
}

void take_item(level_info_t *level, player_t *player, int posX_dest, int posY_dest, int posX_width, int posY_height){
	int i, j;

	for (i = posX_dest; i < posX_width; i++)
		for (j = posY_dest; j < posY_height; j++)
		{
			if(level->map[i][j].type == SPRITE_KEY) 
				player->key[level->map[i][j].specification] = 1;
			else if(level->map[i][j].type == SPRITE_LIFE)
				player->life = MAX_LIFE_PLAYER;
			else if(level->map[i][j].type == SPRITE_BOMB)
				player->bomb += rand() % 3 + 1;
		}
}

void drop_bomb(level_info_t *level, player_t *player, int posX, int posY){

}

void enter_door(world_info_t *world_info, entity_t *player) {
	int zone_player, zone_dest;
	int id_level = player->player.level, id_level_dest = player->player.level;
	int id_door = -1;
	int posX_dest, posY_dest;
	int i = player->posX, j = player->posY;
	int find = 0;

	zone_player = (player->posY / HEIGHT_ZONE_LEVEL) * (WIDTH_LEVEL / WIDTH_ZONE_LEVEL) + (player->posX / WIDTH_ZONE_LEVEL);

	if(pthread_mutex_lock(&world_info->levels[id_level].mutex_zone[zone_player]) != 0) {
		fprintf(stderr, "Error mutex lock in enter_door\n");
		exit(EXIT_FAILURE);
	}

	while (id_door == -1 && j < player->posY + height_sprite(SPRITE_PLAYER))
	{
		if(world_info->levels[id_level].map[i][j].type == SPRITE_DOOR)
			id_door = world_info->levels[id_level].map[i][j].specification-1;

		i++;
		if(i > player->posX + width_sprite(SPRITE_PLAYER)) {
			i = player->posX;
			j++;
		}
	}
	
	if(id_door > -1) {
		if(world_info->doors_level[id_door][0] == id_level)
			id_level_dest = world_info->doors_level[id_door][1];
		else
			id_level_dest = world_info->doors_level[id_door][0];
	}

	if(id_level_dest != id_level) {
		posX_dest = 0;
		posY_dest = 0;

		while (!find && posY_dest < HEIGHT_LEVEL)
		{
			if(world_info->levels[id_level_dest].map[posX_dest][posY_dest].type == SPRITE_DOOR 
				&& world_info->levels[id_level_dest].map[posX_dest][posY_dest].specification-1 == id_door) {
					find = 1;
			}

			if(!find) {
				posX_dest++;
				if(posX_dest >= WIDTH_LEVEL) {
					posY_dest++;
					posX_dest = 0;
				}
			}
		}

		zone_dest = (posY_dest / HEIGHT_ZONE_LEVEL) * (WIDTH_LEVEL / WIDTH_ZONE_LEVEL) + (posX_dest / WIDTH_ZONE_LEVEL);

		if(pthread_mutex_lock(&world_info->levels[id_level_dest].mutex_zone[zone_dest]) != 0) {
			fprintf(stderr, "Error mutex lock in enter_door\n");
			exit(EXIT_FAILURE);
		}
		
		player->posX = posX_dest+1;
		player->posY = posY_dest;
		player->player.level = id_level_dest;

		if(pthread_mutex_unlock(&world_info->levels[id_level_dest].mutex_zone[zone_dest]) != 0){
			fprintf(stderr, "Error unlock mutex in move_level\n");
			exit(EXIT_FAILURE);
		}
	}

	if(pthread_mutex_unlock(&world_info->levels[id_level].mutex_zone[zone_player]) != 0){
		fprintf(stderr, "Error unlock mutex in move_level\n");
		exit(EXIT_FAILURE);
	}
}

// void enter_gate(level_info_t *level, entity_t *player){
	
// }