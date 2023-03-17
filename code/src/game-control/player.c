#include "player.h"

void initialiser_player(player_t *player, int posX, int posY){
	player->life = MAX_LIFE_PLAYER;
	player->bomb = 0;
	// player->posX = posX;
	// player->posY = posY;
}

