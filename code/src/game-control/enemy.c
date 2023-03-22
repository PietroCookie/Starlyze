#include "enemy.h"

#include "game_control.h"
#include "move_world.h"
#include "entity.h"

#include <unistd.h>

void initialiser_enemy(enemy_t *enemy, type_enemy_enum type){
	enemy->type = type;
}

void *thread_enemy(void *arg){
	int level, id_enemy, direction;
	game_control_t *game_control;

	level = ((enemy_infos_thread_t *)arg)->level;
	id_enemy = ((enemy_infos_thread_t *)arg)->id_enemy;
	game_control = ((enemy_infos_thread_t *)arg)->game_control;
	free(arg);

	direction = direction_alea(game_control->enemy[level][id_enemy].enemy.type);

	while (1) {
		if(!game_control->enemy[level][id_enemy].freeze) {
			if(!move_level(&game_control->world_info.levels[level], &game_control->enemy[level][id_enemy], direction, game_control->number_player, game_control->players)) {
				if(game_control->enemy[level][id_enemy].enemy.type == ROBOT) {
					if(direction == LEFT)
						direction = RIGHT;
					else
						direction = LEFT;
				}
				else {
					direction = direction_alea(game_control->enemy[level][id_enemy].enemy.type);
				}
			}

			sleep(1);
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
		direction = LEFT;
	}

	return direction;
}