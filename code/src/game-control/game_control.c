#include "game_control.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <locale.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>


#include "world_info.h"
#include "level_info.h"
#include "move_world.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "trap.h"



void * p_thread_player = thread_player;
void * p_thread_enemy = thread_enemy;
void * p_thread_trap_level = thread_trap_level;

bool quit = FALSE;

void handler_exit(int signum) {
	quit = TRUE;
}

void game_control(int num_player, int socket_game, char* name_world)
{
	struct sigaction action;
	game_control_t game_control_infos;
	int i, m, n;
	int *socket_client;
	pthread_t *thread_player, *thread_enemy, *thread_trap;
	char path_world[255] = "world/";

	strcat(path_world, name_world);
	strcat(path_world, ".world");
	
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

	load_world_info(&game_control_infos.world_info, path_world);

	printf("[GAME %s] : Loaded world\n", name_world);

	if(pthread_cond_init(&game_control_infos.cond_victory, NULL) != 0) {
		fprintf(stderr, "[GAME] - error init condition victory\n");
		exit(EXIT_FAILURE);
	}
	if(pthread_mutex_init(&game_control_infos.mutex_victory, NULL) != 0) {
		fprintf(stderr, "[GAME] - error init mutex victory");
		exit(EXIT_FAILURE);
	}

	game_control_infos.number_player = num_player;
	game_control_infos.id_player_winner = -1;

	m = 0;
	n = 0;
	while (game_control_infos.world_info.levels[game_control_infos.world_info.start_level].map[m][n].type != SPRITE_START)
	{
		n++;
		if(n == HEIGHT_LEVEL) {
			m++;
			n = 0;
		}
	}

	// Create player and thread
	if((game_control_infos.players = malloc(game_control_infos.number_player * sizeof(entity_t))) == NULL) {
		perror("Error allocating player thread");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < game_control_infos.number_player; i++)
	{
		initialise_entity(&game_control_infos.players[i], PLAYER, m+2, n);
		initialise_player(&game_control_infos.players[i].player, game_control_infos.world_info.start_level, i);
	}

	if((socket_client = malloc(game_control_infos.number_player * sizeof(int))) == NULL) {
		perror("Error allocating memory for socket_client in game_control");
		exit(EXIT_FAILURE);
	}
	
	thread_player = launch_players(&game_control_infos, socket_game, socket_client);

	
	// Create enemy
	thread_enemy = launch_enemy(&game_control_infos);

	// Create thread trap
	if((thread_trap = malloc(game_control_infos.world_info.total_level * sizeof(pthread_t))) == NULL) {
		perror("Error allocating memory for thread_trap\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < game_control_infos.world_info.total_level; i++)
		if(pthread_create(&thread_trap[i], NULL, p_thread_trap_level, &game_control_infos.world_info.levels[i]) != 0) {
			fprintf(stderr, "Error create thread for trap\n");
		}

	
	printf("[GAME] - Waiting winner\n");
	if(pthread_cond_wait(&game_control_infos.cond_victory, &game_control_infos.mutex_victory) != 0) {
		fprintf(stderr, "[GAME] - error waiting condition victory\n");
	}
	printf("[GAME] - There are a winner : player %d\n", game_control_infos.id_player_winner);


	for (i = 0; i < game_control_infos.number_player; i++)
		if(pthread_cancel(thread_player[i]) != 0) {
			fprintf(stderr, "Error cancel thread player\n");
		}
	for (i = 0; i < game_control_infos.world_info.total_level; i++)
		if(pthread_cancel(thread_trap[i]) != 0) {
			fprintf(stderr, "Error cancel thread for trap\n");
		}
	for (i = 0; i < game_control_infos.number_total_enemy; i++)
		if(pthread_cancel(thread_enemy[i]) != 0) {
			fprintf(stderr, "Error cancel thread enemy\n");
		}

	for (i = 0; i < game_control_infos.number_player; i++)
		if(pthread_join(thread_player[i], NULL)) {
			fprintf(stderr, "Error join thread player\n");
		}
	for (i = 0; i < game_control_infos.world_info.total_level; i++)
		if(pthread_join(thread_trap[i], NULL) != 0) {
			fprintf(stderr, "Error join thread for trap\n");
		}
	for (i = 0; i < game_control_infos.number_total_enemy; i++)
		if(pthread_join(thread_enemy[i], NULL)) {
			fprintf(stderr, "Error join thread enemy\n");
		}
	
	delete_game_control(&game_control_infos);

	free(thread_player);
	free(thread_enemy);
	free(thread_trap);

	printf("[GAME] - /!\\ Game terminated /!\\ \n");
}

void delete_game_control(game_control_t *game_control_infos) {
	int i;

	for (i = 0; i < game_control_infos->world_info.total_level; i++)
		free(game_control_infos->enemy[i]);
	free(game_control_infos->enemy);
	free(game_control_infos->players);

	delete_world_info(&game_control_infos->world_info);

	if(pthread_cond_destroy(&game_control_infos->cond_victory) != 0) {
		fprintf(stderr, "[GAME] - error destroy condition victory\n");
	}
	if(pthread_mutex_destroy(&game_control_infos->mutex_victory) != 0) {
		fprintf(stderr, "[GAME] - error destroy mutex victory\n");
		exit(EXIT_FAILURE);
	}
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
			fprintf(stderr, "Error create thread for enemy\n");
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
			initialise_entity(&game_control_infos->enemy[i][current_enemy], ENEMY, game_control_infos->world_info.levels[i].robot[current_robot] % WIDTH_LEVEL, ((game_control_infos->world_info.levels[i].robot[current_robot] - game_control_infos->enemy[i][current_enemy].posX) / WIDTH_LEVEL));
			initialise_enemy(&game_control_infos->enemy[i][current_enemy].enemy, ROBOT);

			current_enemy++;
			current_robot++;
		}

		while (game_control_infos->world_info.levels[i].probe[current_probe] != -1)
		{
			initialise_entity(&game_control_infos->enemy[i][current_enemy], ENEMY, game_control_infos->world_info.levels[i].probe[current_probe] % WIDTH_LEVEL, ((game_control_infos->world_info.levels[i].probe[current_probe] - game_control_infos->enemy[i][current_enemy].posX) / WIDTH_LEVEL));
			initialise_enemy(&game_control_infos->enemy[i][current_enemy].enemy, PROBE);

			current_enemy++;
			current_probe++;
		}
		
	}
}

pthread_t *launch_players(game_control_t *game_control_infos, int socket_game, int *socket_client) {
	pthread_t *thread;
	struct sockaddr_in address;
	socklen_t size_address;
	player_infos_thread_t *player_info;
	int i;
	
	if((thread = malloc(game_control_infos->number_player * sizeof(pthread_t))) == NULL) {
		perror("Error allocating player thread");
		exit(EXIT_FAILURE);
	}

	size_address = sizeof(address);
	if(getsockname(socket_game, (struct sockaddr*)&address, &size_address) == -1){
		perror("Error getsockname");
		exit(EXIT_FAILURE);
	}

	printf("[GAME] - Waiting connexion on port %d\n", ntohs(address.sin_port));
	i = 0;
	while (i < game_control_infos->number_player)
	{
		if((socket_client[i] = accept(socket_game, NULL, NULL)) == -1) {
            if(errno != EINTR) {
                perror("Error waiting connexion");
                exit(EXIT_FAILURE);
            }
        }
		else {
			printf("[GAME] - Player id %d connecting ...\n", i);
			i++;
		}
	}
	


	for (i = 0; i < game_control_infos->number_player; i++) {
		if((player_info = malloc(sizeof(player_infos_thread_t))) == NULL) {
			perror("Error allocating memory for infos player");
			exit(EXIT_FAILURE);
		}

		player_info->id_player = i;
		player_info->game_control = game_control_infos;
		player_info->socket_client = &socket_client[i];

		if(pthread_create(&thread[i], NULL, p_thread_player, player_info) != 0){
			fprintf(stderr, "Error create thread for player\n");
		}
	}

	return thread;
}

