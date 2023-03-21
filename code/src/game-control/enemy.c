#include "enemy.h"

#include "entity.h"
#include "move_world.h"

#include "include_game.h"

#include <unistd.h>

void initialiser_enemy(enemy_t *enemy, type_enemy_enum type){
	enemy->type = type;
}

void *thread_enemy(void *arg){
	int level, id_enemy, direction;

	level = ((int *)arg)[0];
	id_enemy = ((int *)arg)[1];
	free(arg);

	direction = direction_alea(enemy[level][id_enemy].enemy.type);

	while (1) {
		if(!enemy[level][id_enemy].freeze) {
			if(!move_level(&world_info.levels[level], &enemy[level][id_enemy], direction, number_player, players)) {
				if(enemy[level][id_enemy].enemy.type == ROBOT) {
					if(direction == LEFT)
						direction = RIGHT;
					else
						direction = LEFT;
				}
				else {
					direction = direction_alea(enemy[level][id_enemy].enemy.type);
				}
			}

			sleep(1);
		}
		else {
			sleep(5);
			enemy[level][id_enemy].freeze = 0;
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