#include "game_control.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "include_game.h"

#include "world_info.h"
#include "move_world.h"
#include "entity.h"
#include "player.h"


void * p_thread_player = thread_player;
void * p_thread_enemy = thread_enemy;

void game_control(int num_player)
{
	int i, current_robot, current_probe, current_enemy;
	int current_level, current_enemy_level;
	int *tab_infos;
	pthread_t *thread_player, *thread_enemy;
	int number_total_enemy = 0;
	

	load_world_info(&world_info, "test.world");

	number_player = num_player;

	// Create player and thread
	if((players = malloc(number_player * sizeof(entity_t))) == NULL) {
		perror("Error allocating player thread");
		exit(EXIT_FAILURE);
	}
	if((thread_player = malloc(number_player * sizeof(pthread_t))) == NULL) {
		perror("Error allocating player thread");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < number_player; i++)
		if(pthread_create(&thread_player[i], NULL, p_thread_player, NULL) != 0){
			fprintf(stderr, "Error create thread for player");
		}

	if((enemy = malloc(world_info.total_level * sizeof(entity_t*))) == NULL) {
		perror("Error allocating memory for enemies array");
		exit(EXIT_FAILURE);
	}

	// Create enemy
	for (i = 0; i < world_info.total_level; i++) {
		current_robot = 0;
		current_probe = 0;
		current_enemy = 0;
		number_total_enemy += world_info.levels[i].number_enemy;

		if((enemy[i] = malloc(world_info.levels[i].number_enemy * sizeof(entity_t))) == NULL) {
			perror("Error allocating memery for enemies array in level");
			exit(EXIT_FAILURE);
		}

		while (world_info.levels[i].robot[current_robot] != -1)
		{
			enemy[i][current_enemy].type = ENEMY;
			enemy[i][current_enemy].posX = world_info.levels[i].robot[current_robot] % WIDTH_LEVEL;
			enemy[i][current_enemy].posY = (world_info.levels[i].robot[current_robot] - enemy[i][current_enemy].posX) / WIDTH_LEVEL;
			enemy[i][current_enemy].freeze = 0;
			enemy[i][current_enemy].enemy.type = ROBOT;

			current_enemy++;
			current_robot++;
		}

		while (world_info.levels[i].probe[current_probe] != -1)
		{
			enemy[i][current_enemy].type = ENEMY;
			enemy[i][current_enemy].posX = world_info.levels[i].probe[current_probe] % WIDTH_LEVEL;
			enemy[i][current_enemy].posY = (world_info.levels[i].probe[current_probe] - enemy[i][current_enemy].posX) / WIDTH_LEVEL;
			enemy[i][current_enemy].freeze = 0;
			enemy[i][current_enemy].enemy.type = PROBE;

			current_enemy++;
			current_probe++;
		}
		
	}
	if((thread_enemy = malloc(number_total_enemy * sizeof(pthread_t))) == NULL){
		perror("Error allocating enemy thread");
		exit(EXIT_FAILURE);
	}

	current_level = 0;
	current_enemy_level = 0;
	for (i = 0; i < number_total_enemy; i++) {
		if((tab_infos = malloc(2 * sizeof(int))) == NULL) {
			perror("Error allocating memory for passing argument in thread enemy");
			exit(EXIT_FAILURE);
		}

		tab_infos[0] = current_level;
		tab_infos[1] = current_enemy_level++;

		if(pthread_create(&thread_enemy[i], NULL, p_thread_enemy, tab_infos) != 0){
			fprintf(stderr, "Error create thread for enemy");
		}

		if(current_enemy_level >= world_info.levels[current_level].number_enemy) {
			current_level++;
			current_enemy_level = 0;
		}
	}
	



	
	for (i = 0; i < number_player; i++)
		if(pthread_join(thread_player[i], NULL)) {
			fprintf(stderr, "Error join thread player");
		}

	for (i = 0; i < number_total_enemy; i++)
		if(pthread_join(thread_enemy[i], NULL)) {
			fprintf(stderr, "Error join thread enemy");
		}
	


	for (i = 0; i < world_info.total_level; i++)
		free(enemy[i]);
	free(enemy);

	delete_world_info(&world_info);

	free(thread_enemy);
	free(thread_player);
}
