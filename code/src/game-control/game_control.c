#include "game_control.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <locale.h>


#include "world_info.h"
#include "move_world.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"

#include "functions.h"
#include "interface_game.h"
#include "level_display.h"


void * p_thread_player = thread_player;
void * p_thread_enemy = thread_enemy;

void game_control(int num_player)
{
	game_control_t game_control_infos;
	int i;
	int current_level, current_enemy_level;
	// int *tab_infos;
	enemy_infos_thread_t *enemy_infos_thread;
	pthread_t *thread_player, *thread_enemy;
	int number_total_enemy;


	interface_game_t *interface;
	bool quit = FALSE;
	// char ch;
	level_display_t level_display;

	
	srand(time(NULL));

	load_world_info(&game_control_infos.world_info, "test.world");

	game_control_infos.number_player = num_player;

	// Create player and thread
	if((game_control_infos.players = malloc(game_control_infos.number_player * sizeof(entity_t))) == NULL) {
		perror("Error allocating player thread");
		exit(EXIT_FAILURE);
	}
	if((thread_player = malloc(game_control_infos.number_player * sizeof(pthread_t))) == NULL) {
		perror("Error allocating player thread");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < game_control_infos.number_player; i++)
		if(pthread_create(&thread_player[i], NULL, p_thread_player, NULL) != 0){
			fprintf(stderr, "Error create thread for player");
		}


	// Create enemy
	number_total_enemy = load_enemy_world(&game_control_infos);
	if((thread_enemy = malloc(number_total_enemy * sizeof(pthread_t))) == NULL){
		perror("Error allocating enemy thread");
		exit(EXIT_FAILURE);
	}

	current_level = 0;
	current_enemy_level = 0;
	for (i = 0; i < number_total_enemy; i++) {
		if((enemy_infos_thread = malloc(sizeof(enemy_infos_thread_t))) == NULL) {
			perror("Error allocating memory for passing argument in thread enemy");
			exit(EXIT_FAILURE);
		}

		enemy_infos_thread->level = current_level;
		enemy_infos_thread->id_enemy = current_enemy_level++;
		enemy_infos_thread->game_control = &game_control_infos;

		if(pthread_create(&thread_enemy[i], NULL, p_thread_enemy, enemy_infos_thread) != 0){
			fprintf(stderr, "Error create thread for enemy");
		}

		if(current_enemy_level >= game_control_infos.world_info.levels[current_level].number_enemy) {
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
			
		convert_level_info(&level_display, game_control_infos.world_info.levels[2], game_control_infos.enemy[2], game_control_infos.world_info.levels[2].number_enemy);
		refresh_win_level_game(interface, level_display);

		sleep(1);
	}
	
	ncurses_stop();

	interface_game_delete(&interface);



	
	for (i = 0; i < game_control_infos.number_player; i++)
		if(pthread_join(thread_player[i], NULL)) {
			fprintf(stderr, "Error join thread player");
		}

	for (i = 0; i < number_total_enemy; i++)
		if(pthread_join(thread_enemy[i], NULL)) {
			fprintf(stderr, "Error join thread enemy");
		}
	


	for (i = 0; i < game_control_infos.world_info.total_level; i++)
		free(game_control_infos.enemy[i]);
	free(game_control_infos.enemy);

	delete_world_info(&game_control_infos.world_info);

	free(thread_enemy);
	free(thread_player);
}

int load_enemy_world(game_control_t *game_control_infos) {
	int i, number_total_enemy = 0;
	int current_robot, current_probe, current_enemy;

	if((game_control_infos->enemy = malloc(game_control_infos->world_info.total_level * sizeof(entity_t*))) == NULL) {
		perror("Error allocating memory for enemies array");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < game_control_infos->world_info.total_level; i++) {
		current_robot = 0;
		current_probe = 0;
		current_enemy = 0;
		number_total_enemy += game_control_infos->world_info.levels[i].number_enemy;

		if((game_control_infos->enemy[i] = malloc(game_control_infos->world_info.levels[i].number_enemy * sizeof(entity_t))) == NULL) {
			perror("Error allocating memery for enemies array in level");
			exit(EXIT_FAILURE);
		}

		while (game_control_infos->world_info.levels[i].robot[current_robot] != -1)
		{
			game_control_infos->enemy[i][current_enemy].type = ENEMY;
			game_control_infos->enemy[i][current_enemy].posX = game_control_infos->world_info.levels[i].robot[current_robot] % WIDTH_LEVEL;
			game_control_infos->enemy[i][current_enemy].posY = (game_control_infos->world_info.levels[i].robot[current_robot] - game_control_infos->enemy[i][current_enemy].posX) / WIDTH_LEVEL;
			game_control_infos->enemy[i][current_enemy].freeze = 0;
			game_control_infos->enemy[i][current_enemy].enemy.type = ROBOT;

			current_enemy++;
			current_robot++;
		}

		while (game_control_infos->world_info.levels[i].probe[current_probe] != -1)
		{
			game_control_infos->enemy[i][current_enemy].type = ENEMY;
			game_control_infos->enemy[i][current_enemy].posX = game_control_infos->world_info.levels[i].probe[current_probe] % WIDTH_LEVEL;
			game_control_infos->enemy[i][current_enemy].posY = (game_control_infos->world_info.levels[i].probe[current_probe] - game_control_infos->enemy[i][current_enemy].posX) / WIDTH_LEVEL;
			game_control_infos->enemy[i][current_enemy].freeze = 0;
			game_control_infos->enemy[i][current_enemy].enemy.type = PROBE;

			current_enemy++;
			current_probe++;
		}
		
	}

	return number_total_enemy;
}
