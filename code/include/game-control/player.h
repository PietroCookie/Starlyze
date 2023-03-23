#ifndef __PLAYER_H__
#define __PLAYER_H__


#define MAX_LIFE_PLAYER 5
#define NUMBER_KEY 6

typedef struct
{
	int key[NUMBER_KEY];
	int life;
	int bomb;
	int level;
	int id;
} player_t;


void initialise_player(player_t *player, int level, int id);

void *thread_player(void *arg);

#endif