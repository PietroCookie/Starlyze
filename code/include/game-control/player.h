#ifndef __PLAYER_H__
#define __PLAYER_H__

#define MAX_LIFE_PLAYER 5
#define NUMBER_KEY 4

typedef struct
{
	int key[NUMBER_KEY];
	int life;
	int bomb;
	int level;
	int id;
	int invincible;
} player_t;


void initialise_player(player_t *player, int level, int id);

void cleanup_handler(void *arg);

void *thread_invincible(void *arg);

void *thread_player(void *arg);

void *thread_sending_level(void *arg);

#endif