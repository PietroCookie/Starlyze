#include "enemy.h"

#include "entity.h"

#include "include_game.h"

void initialiser_enemy(enemy_t *enemy, type_enemy_enum type){
	enemy->type = type;
	// enemy->freeze = 0;
}

void *thread_enemy(void *arg){
	int level, id_enemy;

	level = ((int *)arg)[0];
	id_enemy = ((int *)arg)[1];

	free(arg);

	printf("Level %d id %d enemy position = [%d,%d] type : %d\n", level, id_enemy, enemy[level][id_enemy].posX, enemy[level][id_enemy].posY, enemy[level][id_enemy].enemy.type);

	return NULL;
}