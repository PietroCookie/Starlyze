#include "enemy.h"

void initialiser_enemy(enemy_t *enemy, type_enemy_enum type){
	enemy->type = type;
	// enemy->freeze = 0;
}