#include "enemy.h"

<<<<<<< HEAD
=======
#include <unistd.h>
#include <time.h>

>>>>>>> main
#include "game_control.h"
#include "move_world.h"
#include "entity.h"

<<<<<<< HEAD
#include <unistd.h>
=======
>>>>>>> main

void initialiser_enemy(enemy_t *enemy, type_enemy_enum type){
	enemy->type = type;
}

void *thread_enemy(void *arg){
	int level, id_enemy, direction;
	game_control_t *game_control;
<<<<<<< HEAD
=======
	struct timespec time_wait;

	time_wait.tv_sec = 0;
	time_wait.tv_nsec = 100000000;
>>>>>>> main

	level = ((enemy_infos_thread_t *)arg)->level;
	id_enemy = ((enemy_infos_thread_t *)arg)->id_enemy;
	game_control = ((enemy_infos_thread_t *)arg)->game_control;
	free(arg);

	direction = direction_alea(game_control->enemy[level][id_enemy].enemy.type);

	while (1) {
<<<<<<< HEAD
=======
		pthread_testcancel();

>>>>>>> main
		if(!game_control->enemy[level][id_enemy].freeze) {
			if(!move_level(&game_control->world_info.levels[level], &game_control->enemy[level][id_enemy], direction, game_control->number_player, game_control->players)) {
				if(game_control->enemy[level][id_enemy].enemy.type == ROBOT) {
					if(direction == LEFT)
						direction = RIGHT;
					else
						direction = LEFT;
				}
<<<<<<< HEAD
				else {
					direction = direction_alea(game_control->enemy[level][id_enemy].enemy.type);
				}
			}

			sleep(1);
=======
			}

			if(game_control->enemy[level][id_enemy].enemy.type != ROBOT)
				direction = direction_alea(game_control->enemy[level][id_enemy].enemy.type);

			nanosleep(&time_wait, NULL);
>>>>>>> main
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
<<<<<<< HEAD
		direction = LEFT;
=======
		direction = rand() % 4 + 1;
		if(direction == 1)
			direction = LEFT;
		else if(direction == 2)
			direction = RIGHT;
		else if(direction == 3)
			direction = UP;
		else if(direction == 4)
			direction = DOWN;
>>>>>>> main
	}

	return direction;
}