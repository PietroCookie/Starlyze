#include "enemy.h"

#include <unistd.h>
#include <time.h>

#include "game_control.h"
#include "move_world.h"
#include "entity.h"


void initialiser_enemy(enemy_t *enemy, type_enemy_enum type){
	enemy->type = type;
}

void *thread_enemy(void *arg){
	int level, id_enemy, direction;
	game_control_t *game_control;
	struct timespec time_wait;


	level = ((enemy_infos_thread_t *)arg)->level;
	id_enemy = ((enemy_infos_thread_t *)arg)->id_enemy;
	game_control = ((enemy_infos_thread_t *)arg)->game_control;
	free((enemy_infos_thread_t *) arg);

	if(game_control->enemy[level][id_enemy].enemy.type == PROBE) {
		time_wait.tv_sec = 0;
		time_wait.tv_nsec = 250000000;
	}
	else {
		time_wait.tv_sec = 0;
		time_wait.tv_nsec = 100000000;
	}


	direction = direction_alea(game_control->enemy[level][id_enemy].enemy.type);

	while (1) {
		pthread_testcancel();

		if(!game_control->enemy[level][id_enemy].freeze) {
			if(!move_level(&game_control->world_info.levels[level], &game_control->enemy[level][id_enemy], direction, game_control->number_player, game_control->players)) {
				if(game_control->enemy[level][id_enemy].enemy.type == ROBOT) {
					if(direction == LEFT)
						direction = RIGHT;
					else
						direction = LEFT;
				}
			}

			if(game_control->enemy[level][id_enemy].enemy.type != ROBOT)
				direction = direction_alea(game_control->enemy[level][id_enemy].enemy.type);

			nanosleep(&time_wait, NULL);
		}
		else {
			sleep(5);
			game_control->enemy[level][id_enemy].freeze = 0;
		}
	}


	return NULL;
}

int direction_alea(type_enemy_enum type_enemy) {
	int direction;

	if(type_enemy == ROBOT) {
		direction = rand() % 2 + 1;
		if(direction == 1)
			direction = LEFT;
		else if(direction == 2)
			direction = RIGHT;
	}
	else {
		direction = rand() % 4 + 1;
		if(direction == 1)
			direction = LEFT;
		else if(direction == 2)
			direction = RIGHT;
		else if(direction == 3)
			direction = UP;
		else if(direction == 4)
			direction = DOWN;
	}

	return direction;
}