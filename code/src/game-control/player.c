#include "player.h"

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

#include "functions.h"

#include "game_control.h"
#include "move_world.h"
#include "level_display.h"
#include "request_exchange.h"


void initialise_player(player_t *player, int level, int id){
	int i;

	player->life = MAX_LIFE_PLAYER;
	player->bomb = 0;
	player->level = level;
	player->id = id;
	player->invincible = 0;

	for (i = 0; i < NUMBER_KEY; i++)
		player->key[i] = 0;
}

void cleanup_handler(void *arg) {
	if(pthread_cancel(*(pthread_t*)arg) != 0)
		fprintf(stderr, "Error cancel thread_sending_level\n");

	if(pthread_join(*(pthread_t*)arg, NULL) != 0)
		fprintf(stderr, "Error join thread_sending_level\n");
}

void *thread_invincible(void *arg) {
	player_t *player = ((player_t*)arg);

	player->invincible = 1;
	sleep(3);
	player->invincible = 0;

	pthread_exit(NULL);
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
		if(read(socket_client, &ch, sizeof(char))== -1) {
			perror("Error receive value");
			quit = 1;
		}

		if(!player_entity->freeze) {
			if(ch == 'd' || ch == 'D')
				move_level(game_control, player_entity->player.level, player_entity, RIGHT);
			else if(ch == 'q' || ch == 'Q')
				move_level(game_control, player_entity->player.level, player_entity, LEFT);
			else if(ch == 'z' || ch == 'Z')
				move_level(game_control, player_entity->player.level, player_entity, UP);
			else if(ch == 's' || ch == 'S')
				move_level(game_control, player_entity->player.level, player_entity, DOWN);
			else if(ch == 'e' || ch == 'E')
				enter_door(&game_control->world_info, player_entity);
			else if(ch == 'g' || ch == 'G')
				drop_bomb(game_control, player_entity);
		}
		else {
			sleep(5);
			player_entity->freeze = 0;
		}
	}

	pthread_cleanup_pop(0);

	cleanup_handler(&thread_display);

	printf("Thread player %d TERMINATED\n", player_entity->player.id);

	pthread_exit(NULL);
}

void *thread_sending_level(void *arg) {
	int quit = 0;
	int id_player = ((player_infos_thread_t *)arg)->id_player;
	game_control_t *game_control = ((player_infos_thread_t *)arg)->game_control;
	int socket_client = *((player_infos_thread_t *)arg)->socket_client;
	entity_t *player_entity = &game_control->players[id_player];
	struct timespec time_wait;
	request_send_player_t request_send;


	free(arg);

	time_wait.tv_sec = 0;
	time_wait.tv_nsec = 100000000;

	while (!quit)
	{
		convert_level_info(player_entity->player.level, &request_send.level_display, game_control->world_info.levels[player_entity->player.level], game_control->enemy[player_entity->player.level], game_control->number_total_enemy, game_control->players, game_control->number_player);

		request_send.player = player_entity->player;

		if(write(socket_client, &request_send, sizeof(request_send_player_t)) == -1) {
			perror("Error sending value");
			quit = 1;
		}

		nanosleep(&time_wait, NULL);
	}

	if(close(socket_client) == -1) {
        perror("Error closing socket in cleanup_handler");
    }

	pthread_exit(NULL);
}
