#ifndef __PAYER_H__
#define __PLAYER_H__

#define MAX_LIFE_PLAYER 5
#define NUMBER_KEY 6

typedef struct
{
	int life;
	int bomb;
	int key[NUMBER_KEY];
} player_t;


void initialiser_player(player_t *player, int posX, int posY);


#endif