#include "game_control.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <locale.h>
#include <signal.h>
#include <time.h>



#include "world_info.h"
#include "level_info.h"
#include "move_world.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"

#include "functions.h"
#include "interface_game.h"
#include "level_display.h"


void * p_thread_player = thread_player;
void * p_thread_enemy = thread_enemy;
// void * p_thread_trap = thread_trap;

bool quit = FALSE;

void handler_exit(int signum) {
	quit = TRUE;
}

void game_control(int num_player)
{
	struct sigaction action;
	game_control_t game_control_infos;
	int i;
	// int *tab_infos;
	pthread_t *thread_player, *thread_enemy, *thread_trap;


	interface_game_t *interface;
	// char ch;
	level_display_t level_display;

	
	srand(time(NULL));
	sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    action.sa_handler = handler_exit;
    if(sigaction(SIGCHLD, &action, NULL) == -1) {
        perror("Error positioning handler (1)");
        exit(EXIT_FAILURE);    
    }
    if(sigaction(SIGINT, &action, NULL) == -1) {
        perror("Error positioning handler (2)");
        exit(EXIT_FAILURE);    
    }

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
	thread_enemy = launch_enemy(&game_control_infos);

	// Create thread trap
	if((thread_trap = malloc(game_control_infos.world_info.total_level)) == NULL) {
		perror("Error allocating memory for thread_trap");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < game_control_infos.world_info.total_level; i++)
		if(pthread_create(&thread_trap[i], NULL, thread_trap_level, &game_control_infos.world_info.levels[i]) != 0) {
			fprintf(stderr, "Error create thread for trap");
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
			
		convert_level_info(&level_display, game_control_infos.world_info.levels[0], game_control_infos.enemy[0], game_control_infos.world_info.levels[0].number_enemy);
		refresh_win_level_game(interface, level_display);
		

		
	}
	
	ncurses_stop();

	interface_game_delete(&interface);


	for (i = 0; i < game_control_infos.world_info.total_level; i++)
		if(pthread_cancel(thread_trap[i]) != 0) {
			fprintf(stderr, "Error cancel thread for trap");
		}

	for (i = 0; i < game_control_infos.number_player; i++)
		if(pthread_cancel(thread_player[i]) != 0) {
			fprintf(stderr, "Error cancel thread player");
		}
	for (i = 0; i < game_control_infos.number_total_enemy; i++)
		if(pthread_cancel(thread_enemy[i]) != 0) {
			fprintf(stderr, "Error cancel thread enemy");
		}

	for (i = 0; i < game_control_infos.world_info.total_level; i++)
		if(pthread_join(thread_trap[i], NULL) != 0) {
			fprintf(stderr, "Error join thread for trap");
		}
	for (i = 0; i < game_control_infos.number_player; i++)
		if(pthread_join(thread_player[i], NULL)) {
			fprintf(stderr, "Error join thread player");
		}
	for (i = 0; i < game_control_infos.number_total_enemy; i++)
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

pthread_t* launch_enemy(game_control_t *game_control_infos) {
	int i, current_level, current_enemy_level;
	enemy_infos_thread_t *enemy_infos_thread;
	pthread_t *thread_enemy;

	load_enemy_world(game_control_infos);
	if((thread_enemy = malloc(game_control_infos->number_total_enemy * sizeof(pthread_t))) == NULL){
		perror("Error allocating enemy thread");
		exit(EXIT_FAILURE);
	}

	current_level = 0;
	current_enemy_level = 0;
	for (i = 0; i < game_control_infos->number_total_enemy; i++) {
		if((enemy_infos_thread = malloc(sizeof(enemy_infos_thread_t))) == NULL) {
			perror("Error allocating memory for passing argument in thread enemy");
			exit(EXIT_FAILURE);
		}

		enemy_infos_thread->level = current_level;
		enemy_infos_thread->id_enemy = current_enemy_level++;
		enemy_infos_thread->game_control = game_control_infos;

		if(pthread_create(&thread_enemy[i], NULL, p_thread_enemy, enemy_infos_thread) != 0){
			fprintf(stderr, "Error create thread for enemy");
		}

		if(current_enemy_level >= game_control_infos->world_info.levels[current_level].number_enemy) {
			current_level++;
			current_enemy_level = 0;
		}
	}

	return thread_enemy;
}

void load_enemy_world(game_control_t *game_control_infos) {
	int i;
	int current_robot, current_probe, current_enemy;

	game_control_infos->number_total_enemy = 0;

	if((game_control_infos->enemy = malloc(game_control_infos->world_info.total_level * sizeof(entity_t*))) == NULL) {
		perror("Error allocating memory for enemies array");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < game_control_infos->world_info.total_level; i++) {
		current_robot = 0;
		current_probe = 0;
		current_enemy = 0;
		game_control_infos->number_total_enemy += game_control_infos->world_info.levels[i].number_enemy;

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
}

void *thread_trap_level(void *arg) {
	level_info_t *level_info;
	int i;
	int posX, posY, zone_trap;
	struct timespec time_wait;

	level_info = (level_info_t *)arg;

	time_wait.tv_sec = 0;
	time_wait.tv_nsec = 100000000;

	while (1)
	{
		i = 0;
		while (i < NUMBER_TRAP && level_info->trap[i] != -1)
		{
			posX = level_info->trap[i] % WIDTH_LEVEL;
			posY = (level_info->trap[i] - posX) / WIDTH_LEVEL;


			zone_trap = (posY / HEIGHT_ZONE_LEVEL) * (WIDTH_LEVEL / WIDTH_ZONE_LEVEL) + (posX / WIDTH_ZONE_LEVEL);

			if(pthread_mutex_lock(&level_info->mutex_zone[zone_trap]) != 0) {
				fprintf(stderr, "Error mutex lock zone level in thread_trap_level");
				exit(EXIT_FAILURE);
			}


			if(level_info->map[posX][posY].specification == -1)
				level_info->map[posX][posY].specification = 1;
			else
				level_info->map[posX][posY].specification = -1;


			if(pthread_mutex_unlock(&level_info->mutex_zone[zone_trap]) != 0) {
				fprintf(stderr, "Error mutex unlock zone level in thread_trap_level");
				exit(EXIT_FAILURE);
			}

			i++;
			pthread_testcancel();
			if(nanosleep(&time_wait, NULL) == -1) {
				fprintf(stderr, "Error with nanosleep in thread_trap_level");
			}
		}
	}

	return NULL;
}
