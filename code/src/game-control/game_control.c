#include "game_control.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <locale.h>

#include "include_game.h"

#include "world_info.h"
#include "move_world.h"
#include "entity.h"
#include "player.h"

#include "functions.h"
#include "interface_game.h"
#include "level_display.h"


void * p_thread_player = thread_player;
void * p_thread_enemy = thread_enemy;

void game_control(int num_player)
{
	int i;
	int current_level, current_enemy_level;
	int *tab_infos;
	pthread_t *thread_player, *thread_enemy;
	int number_total_enemy;


	interface_game_t *interface;
	bool quit = FALSE;
	// char ch;
	level_display_t level_display;

	
	srand(time(NULL));

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


	// Create enemy
	number_total_enemy = load_enemy_world();
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



	setlocale(LC_ALL, "");
	ncurses_init();
	ncurses_init_mouse();
	ncurses_colors();
	palette();
	clear();
	refresh();


	interface = interface_game_create();
	while (quit == FALSE)
	{
		// ch = getch();
		// if((ch == 'Q') || (ch == 'q'))
		// 	quit = TRUE;
			
		convert_level_info(&level_display, &world_info.levels[2], enemy[2], world_info.levels[2].number_enemy);
		refresh_win_level_game(interface, level_display);
		
		sleep(1);
	}
	
	ncurses_stop();

	interface_game_delete(&interface);



	
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

int load_enemy_world() {
	int i, number_total_enemy = 0;
	int current_robot, current_probe, current_enemy;

	if((enemy = malloc(world_info.total_level * sizeof(entity_t*))) == NULL) {
		perror("Error allocating memory for enemies array");
		exit(EXIT_FAILURE);
	}

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

	return number_total_enemy;
}
