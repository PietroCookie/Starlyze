#include "player.h"

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

#include "functions.h"

#include "game_control.h"
#include "move_world.h"
#include "level_display.h"


void initialise_player(player_t *player, int level, int id){
	int i;

	player->life = MAX_LIFE_PLAYER;
	player->bomb = 0;
	player->level = level;
	player->id = id;

	for (i = 0; i < NUMBER_KEY; i++)
		player->key[i] = 0;
}

void cleanup_handler(void *arg) {
	if(pthread_cancel(*(pthread_t*)arg) != 0)
		fprintf(stderr, "Error cancel thread_sending_level\n");

	if(pthread_join(*(pthread_t*)arg, NULL) != 0)
		fprintf(stderr, "Error join thread_sending_level\n");
}

void *thread_player(void *arg) {
	int quit = 0;
	int id_player = ((player_infos_thread_t *)arg)->id_player;
	game_control_t *game_control = ((player_infos_thread_t *)arg)->game_control;
	int socket_client = *((player_infos_thread_t *)arg)->socket_client;
	entity_t *player_entity = &game_control->players[id_player];
	pthread_t thread_display;
	char ch;
	

	if(pthread_create(&thread_display, NULL, thread_sending_level, arg)) {
		fprintf(stderr, "Error create thread display player\n");
	}
	
	pthread_cleanup_push(cleanup_handler, &thread_display);
	

	while (quit == 0)
	{
		// enter_gate(&game_control->world_info.levels[player_entity->player.level], player_entity);
		if(read(socket_client, &ch, sizeof(char))== -1) {
			perror("Error receive value");
			quit = 1;
		}

		if(ch == 'd' || ch == 'D')
			move_level(&game_control->world_info.levels[player_entity->player.level], player_entity, RIGHT, game_control->world_info.levels[player_entity->player.level].number_enemy, game_control->enemy[player_entity->player.level]);
		else if(ch == 'q' || ch == 'Q')
			move_level(&game_control->world_info.levels[player_entity->player.level], player_entity, LEFT, game_control->world_info.levels[player_entity->player.level].number_enemy, game_control->enemy[player_entity->player.level]);
	}

	pthread_cleanup_pop(0);

	return NULL;
}

void *thread_sending_level(void *arg) {
	int quit = 0;
	int id_player = ((player_infos_thread_t *)arg)->id_player;
	game_control_t *game_control = ((player_infos_thread_t *)arg)->game_control;
	int socket_client = *((player_infos_thread_t *)arg)->socket_client;
	entity_t *player_entity = &game_control->players[id_player];
	level_display_t level_display;
	struct timespec time_wait;


	free(arg);

	time_wait.tv_sec = 0;
	time_wait.tv_nsec = 100000000;

	while (!quit)
	{
		convert_level_info(player_entity->player.level, &level_display, game_control->world_info.levels[player_entity->player.level], game_control->enemy[player_entity->player.level], game_control->number_total_enemy, game_control->players, game_control->number_player);

		if(write(socket_client, &level_display, sizeof(level_display_t)) == -1) {
			perror("Error sending value");
			quit = 1;
		}

		nanosleep(&time_wait, NULL);
	}

	if(close(socket_client) == -1) {
        perror("Error closing socket in cleanup_handler");
    }

	return NULL;
}
