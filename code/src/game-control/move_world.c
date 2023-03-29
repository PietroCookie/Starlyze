#include "move_world.h"

#include <pthread.h>
#include <stdio.h>

#include "game_control.h"
#include "sprite.h"

void * p_thread_invincible = thread_invincible;

void *thread_wait_item(void *arg) {

	int posX = ((infos_wait_item_t*)arg)->infos[0];
	int posY = ((infos_wait_item_t*)arg)->infos[1];
	int type_sprite = ((infos_wait_item_t*)arg)->infos[2];

	sleep(rand() % 5 +1);

	((infos_wait_item_t*)arg)->level->map[posX][posY].type = type_sprite;

	pthread_exit(NULL);
}

int move_level(game_control_t *game_control_info, int id_level, entity_t *entity_move, direction_enum direction){
	int validate = 1;
	int posX_dest = entity_move->posX, posY_dest = entity_move->posY;
	int posX_width = posX_dest, posY_height = posY_dest;
	int zone_dest;
	int zone_src[2];
	entity_t *collider;
	pthread_t thread_invincible;

	posX_width = posX_width_entity(*entity_move);
	posY_height = posY_height_entity(*entity_move);

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
			if((entity_move->type == PLAYER && (game_control_info->world_info.levels[id_level].map[entity_move->posX][entity_move->posY].type == SPRITE_LADDER || game_control_info->world_info.levels[id_level].map[entity_move->posX][posY_height].type == SPRITE_LADDER))
				|| (entity_move->type == ENEMY && entity_move->enemy.type  == PROBE) ) {
				posY_dest--;
				posY_height--;
			}
			break;

		case DOWN:
			if((entity_move->type == PLAYER && (game_control_info->world_info.levels[id_level].map[entity_move->posX][entity_move->posY].type == SPRITE_LADDER || game_control_info->world_info.levels[id_level].map[entity_move->posX][posY_height+1].type == SPRITE_LADDER)) 
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
		if(pthread_mutex_lock(&game_control_info->world_info.levels[id_level].mutex_zone[zone_src[0]]) != 0){
			fprintf(stderr, "Error lock mutex in move_level\n");
			exit(EXIT_FAILURE);
		}
		if(zone_dest != zone_src[0])
			if(pthread_mutex_lock(&game_control_info->world_info.levels[id_level].mutex_zone[zone_dest]) != 0){
				fprintf(stderr, "Error lock mutex in move_level\n");
				exit(EXIT_FAILURE);
			}


		validate = check_validation_move(&game_control_info->world_info.levels[id_level], posX_dest, posY_dest, posX_width, posY_height, entity_move);

		
		if(validate) {
			entity_move->posX = posX_dest;
			entity_move->posY = posY_dest;
			
			if(entity_move->type == PLAYER) {
				if(!entity_move->player.invincible && (collider = check_collision(entity_move, game_control_info->enemy[id_level], game_control_info->world_info.levels[id_level].number_enemy, id_level)) != NULL) {
					entity_move->player.life--;
					
					if(entity_move->player.life <= 0)
						reset_player(game_control_info->world_info, entity_move);
					if(pthread_create(&thread_invincible, NULL, p_thread_invincible, &entity_move->player) != 0) {
						fprintf(stderr, "Error create thread invincible\n");
					}
				}
				else
					take_item(&game_control_info->world_info.levels[id_level], &entity_move->player, posX_dest, posY_dest, posX_width, posY_height);
			}
			else if(entity_move->type == ENEMY) {
				if((collider = check_collision(entity_move, game_control_info->players, game_control_info->number_player, id_level)) != NULL && !collider->player.invincible) {
					collider->player.life--;
					
					if(collider->player.life <= 0)
						reset_player(game_control_info->world_info, collider);
					if(pthread_create(&thread_invincible, NULL, p_thread_invincible, &collider->player) != 0) {
						fprintf(stderr, "Error create thread invincible\n");
					}
				}
			}
			
		}

		if(pthread_mutex_unlock(&game_control_info->world_info.levels[id_level].mutex_zone[zone_src[0]]) != 0){
			fprintf(stderr, "Error unlock mutex in move_level\n");
			exit(EXIT_FAILURE);
		}
		if(zone_dest != zone_src[0])
			if(pthread_mutex_unlock(&game_control_info->world_info.levels[id_level].mutex_zone[zone_dest]) != 0){
				fprintf(stderr, "Error lock mutex in move_level\n");
				exit(EXIT_FAILURE);
			}
	}

	return validate;
}

void reset_player(world_info_t world_info, entity_t *player) {
	int m, n;

	m = 0;
	n = 0;
	while (world_info.levels[world_info.start_level].map[m][n].type != SPRITE_START)
	{
		n++;
		if(n == HEIGHT_LEVEL) {
			m++;
			n = 0;
		}
	}

	player->posX = m;
	player->posY = n;

	for (m = 0; m < NUMBER_KEY; m++)
		player->player.key[m] = 0;
	

	player->player.life = MAX_LIFE_PLAYER;
	player->player.bomb = 0;
	player->player.level = world_info.start_level;
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

entity_t *check_collision(entity_t *entity_collision, entity_t *collider, int number_collider, int level) {
	int i;
	int posX_width, posY_height, posX_width_collider, posY_height_collider;
	entity_t *collision = NULL;

	posX_width = posX_width_entity(*entity_collision);
	posY_height = posY_height_entity(*entity_collision);

	i = 0;
	while (collision == NULL && i < number_collider)
	{
		if((collider[i].type == PLAYER && collider[i].player.level == level && !collider[i].player.invincible) || (collider[i].type == ENEMY && !collider[i].freeze) ) {
			posX_width_collider = posX_width_entity(collider[i]);
			posY_height_collider = posY_height_entity(collider[i]);
			
			if((entity_collision->posX <= posX_width_collider && entity_collision->posX >= collider[i].posX && entity_collision->posY <= posY_height_collider && entity_collision->posY >= collider[i].posY)
				|| (posX_width <= posX_width_collider && posX_width >= collider[i].posX && entity_collision->posY <= posY_height_collider && entity_collision->posY >= collider[i].posY )
				|| (entity_collision->posX <= posX_width_collider && entity_collision->posX >= collider[i].posX && posY_height <= posY_height_collider && posY_height >= collider[i].posY)
				|| (posX_width <= posX_width_collider && posX_width >= collider[i].posX && posY_height <=posY_height_collider && posY_height >= collider[i].posY) )
				collision = &collider[i];
		}
		
		i++;
	}

	return collision;
}

void take_item(level_info_t *level, player_t *player, int posX, int posY, int posX_width, int posY_height){
	int i, j;
	pthread_t thread;
	infos_wait_item_t infos_thread;

	for (i = posX; i <= posX_width; i++)
		for (j = posY; j <= posY_height; j++)
		{
			if(level->map[i][j].type == SPRITE_KEY)
				player->key[level->map[i][j].specification] = 1;
			else if(level->map[i][j].type == SPRITE_LIFE && player->life < MAX_LIFE_PLAYER) {
				player->life = MAX_LIFE_PLAYER;
				infos_thread.infos[0] = i;
				infos_thread.infos[1] = j;
				infos_thread.infos[2] = SPRITE_LIFE;
				infos_thread.level = level;

				if(pthread_create(&thread, NULL, thread_wait_item, &infos_thread) != 0)
					fprintf(stderr, "Error create thread wait item\n");

				level->map[i][j].type = 0;
			}
			else if(level->map[i][j].type == SPRITE_BOMB && level->map[i][j].specification == -1) {
				player->bomb += rand() % 3 + 1;
				infos_thread.infos[0] = i;
				infos_thread.infos[1] = j;
				infos_thread.infos[2] = SPRITE_BOMB;
				infos_thread.level = level;

				level->map[i][j].type = 0;
				
				if(pthread_create(&thread, NULL, thread_wait_item, &infos_thread) != 0)
					fprintf(stderr, "Error create thread wait item\n");
			}
		}
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

void drop_bomb(game_control_t *game_control, entity_t *player){
	pthread_t explosion;
	infos_bomb_explose_t infos_bomb;
	int zone_drop;
	int posX_bomb, posY_bomb;

	if(player->player.bomb <= 0)
		return;

	posX_bomb = player->posX + 1;
	posY_bomb = player->posY + height_sprite(SPRITE_PLAYER)-1;

	zone_drop = (posY_bomb / HEIGHT_ZONE_LEVEL) * (WIDTH_LEVEL / WIDTH_ZONE_LEVEL) + (posX_bomb / WIDTH_ZONE_LEVEL);

	infos_bomb.world_info = &game_control->world_info;
	infos_bomb.position[0] = posX_bomb;
	infos_bomb.position[1] = posY_bomb;
	infos_bomb.id_level = player->player.level;
	infos_bomb.enemy_level = game_control->enemy[player->player.level];
	infos_bomb.number_enemy = game_control->world_info.levels[player->player.level].number_enemy;
	infos_bomb.players = game_control->players;
	infos_bomb.number_players = game_control->number_player;
	infos_bomb.delay_explosion = rand() % 10 + 4;

	if(pthread_mutex_lock(&game_control->world_info.levels[player->player.level].mutex_zone[zone_drop]) != 0) {
		fprintf(stderr, "Error mutex lock zone drop bomb\n");
		exit(EXIT_FAILURE);
	}

	infos_bomb.last_sprite = game_control->world_info.levels[player->player.level].map[posX_bomb][posY_bomb].type;
	game_control->world_info.levels[player->player.level].map[posX_bomb][posY_bomb].type = SPRITE_BOMB;
	game_control->world_info.levels[player->player.level].map[posX_bomb][posY_bomb].specification = infos_bomb.delay_explosion;

	if(pthread_mutex_unlock(&game_control->world_info.levels[player->player.level].mutex_zone[zone_drop]) != 0) {
		fprintf(stderr, "Error mutex unlock zone drop bomb\n");
		exit(EXIT_FAILURE);
	}

	player->player.bomb--;

	if(pthread_create(&explosion, NULL, thread_explose_bomb, &infos_bomb) != 0) {
		fprintf(stderr, "Error create thread explosion bomb\n");
	}
}

void *thread_explose_bomb(void *arg) {
	int i, j, current_zone;
	int id_level = ((infos_bomb_explose_t*)arg)->id_level;
	int posX = ((infos_bomb_explose_t*)arg)->position[0];
	int posY = ((infos_bomb_explose_t*)arg)->position[1];
	int posX_bomb = posX, posY_bomb = posY;
	int posX_width = posX, posY_height = posY;
	world_info_t *world_info = ((infos_bomb_explose_t*)arg)->world_info;
	entity_t *enemy = ((infos_bomb_explose_t*)arg)->enemy_level;
	int number_enemy = ((infos_bomb_explose_t*)arg)->number_enemy;
	entity_t *players = ((infos_bomb_explose_t*)arg)->players;
	int number_players = ((infos_bomb_explose_t*)arg)->number_players;
	int delay = ((infos_bomb_explose_t*)arg)->delay_explosion;
	type_sprite_enum last_sprite = ((infos_bomb_explose_t*)arg)->last_sprite;
	int zone_explosion[9];

	if(posX < 5)
		posX = 0;
	else
		posX -= 5;

	if(posY < 5)
		posY = 0;
	else
		posY -= 5;

	if((posX_width += 5) > WIDTH_LEVEL)
		posX_width = WIDTH_LEVEL;
	if((posY_height += 5) > HEIGHT_LEVEL)
		posY_height = HEIGHT_LEVEL;


	current_zone = 0;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
		{
			zone_explosion[current_zone] = ((posY + j*HEIGHT_ZONE_LEVEL) / HEIGHT_ZONE_LEVEL) * (WIDTH_LEVEL / WIDTH_ZONE_LEVEL) + ((posX + i*WIDTH_ZONE_LEVEL) / WIDTH_ZONE_LEVEL);
			current_zone++;
		}

	sleep( delay );

	
	for (i = 0; i < 9; i++){
		if(zone_explosion[i] < world_info->levels[id_level].number_mutex_zone && zone_explosion[i] >= 0)
			if(pthread_mutex_lock(&world_info->levels[id_level].mutex_zone[zone_explosion[i]]) != 0) {
				fprintf(stderr, "Error lock mutex zone explosion\n");
			}
	}

	for (i = 0; i < number_enemy; i++)
		if( enemy[i].posX >= posX && enemy[i].posX <= posX_width && enemy[i].posY >= posY && enemy[i].posY <= posY_height)
			enemy->freeze = 1;

	for (i = 0; i < number_players; i++)
		if(players[i].player.level == id_level && players[i].posX >= posX && players[i].posX <= posX_width && players[i].posY >= posY && players[i].posY <= posY_height) {
			players[i].freeze = 1;
			players[i].player.life--;
			
			if(players[i].player.life <= 0)
				reset_player(*world_info, players);
		}

	
	world_info->levels[id_level].map[posX_bomb][posY_bomb].type = last_sprite;
	world_info->levels[id_level].map[posX_bomb][posY_bomb].specification = -1;

	
	for (i = 0; i < 9; i++){
		if(zone_explosion[i] < world_info->levels[id_level].number_mutex_zone && zone_explosion[i] >= 0)
			if(pthread_mutex_unlock(&world_info->levels[id_level].mutex_zone[zone_explosion[i]]) != 0) {
				fprintf(stderr, "Error unlock mutex zone explosion\n");
			}
	}


	pthread_exit(NULL);
}
