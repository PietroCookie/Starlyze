#include "trap.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <locale.h>
#include <signal.h>
#include <time.h>

#include "level_info.h"

void initialise_trap(trap_t *trap, int posX, int posY) {
	trap->posX = posX;
	trap->posY = posY;
	trap->succ = NULL;
}

void initialise_list_trap(list_trap_t *list) {
	list->traps = NULL;
	list->succ = NULL;
}

void insert_list_trap(list_trap_t *list, trap_t *trap) {
	trap->succ = list->traps;
	list->traps = trap;
}

void delete_list_trap(list_trap_t *list, trap_t *trap) {
	trap_t *pred = list->traps;

	if(pred == trap)
		list->traps = trap->succ;
	else
	{
		while (pred->succ != NULL && pred->succ != trap)
			pred = pred->succ;
		
		pred->succ = trap->succ;
	}
}

void destroy_list_trap(list_trap_t *list) {
	trap_t *trap = list->traps;
	trap_t *tmp;

	while (trap != NULL)
	{
		tmp = trap->succ;
		delete_list_trap(list, trap);
		free(trap);
		trap = tmp;
	}
	
	list = NULL;
}

void initialise_list_block_trap(list_block_trap_t *list_block) {
	list_block->blocks = NULL;
}

void insert_list_block_trap(list_block_trap_t *list_block, list_trap_t *list_trap) {
	list_trap->succ = list_block->blocks;
	list_block->blocks = list_trap;
}

void delete_list_block_trap(list_block_trap_t *list_block, list_trap_t *list_trap) {
	list_trap_t *pred = list_block->blocks;

	if(pred == list_trap)
		list_block->blocks = list_trap->succ;
	else
	{
		while (pred->succ != NULL && pred->succ != list_trap)
			pred = pred->succ;
		
		pred->succ = list_trap->succ;
	}
}

void destroy_list_block_trap(list_block_trap_t *list_block) {
	list_trap_t *list_trap = list_block->blocks;
	list_trap_t *list_trap_tmp;

	while (list_trap != NULL)
	{
		list_trap_tmp = list_trap->succ;
		delete_list_block_trap(list_block, list_trap);
		destroy_list_trap(list_trap);
		free(list_trap);
		list_trap = list_trap_tmp;
	}

	list_block = NULL;
}

void *thread_trap_level(void *arg) {
	level_info_t *level_info;
	struct timespec time_wait;
	list_trap_t *list_trap;
	trap_t *trap;
	int zone_trap, zone_next, specification;

	level_info = (level_info_t *)arg;

	time_wait.tv_sec = 0;
	time_wait.tv_nsec = 100000000;

	while (1)
	{
		list_trap = level_info->list_block_trap.blocks;

		while (list_trap != NULL && list_trap->traps != NULL)
		{
			trap = list_trap->traps;

			zone_trap = (trap->posY / HEIGHT_ZONE_LEVEL) * (WIDTH_LEVEL / WIDTH_ZONE_LEVEL) + (trap->posX / WIDTH_ZONE_LEVEL);

			if(pthread_mutex_lock(&level_info->mutex_zone[zone_trap]) != 0)	{
				fprintf(stderr, "Error mutex lock zone level in thread_trap_level\n");
				exit(EXIT_FAILURE);
			}

			if(level_info->map[trap->posX][trap->posY].specification == -1) {
				specification = rand() % 15;
				if((rand() % 2 + 1) == 1)
					specification = -specification;
			}
			else if(level_info->map[trap->posX][trap->posY].specification > -1)
				specification = level_info->map[trap->posX][trap->posY].specification - 1;
			else
				specification = level_info->map[trap->posX][trap->posY].specification + 1;

			while (trap != NULL)
			{
				zone_next = (trap->posY / HEIGHT_ZONE_LEVEL) * (WIDTH_LEVEL / WIDTH_ZONE_LEVEL) + (trap->posX / WIDTH_ZONE_LEVEL);
				
				if(zone_next != zone_trap) {
					if(pthread_mutex_unlock(&level_info->mutex_zone[zone_trap]) != 0) {
						fprintf(stderr, "Error mutex unlock zone level in thread_trap_level\n");
						exit(EXIT_FAILURE);
					}
					if(pthread_mutex_lock(&level_info->mutex_zone[zone_next]) != 0)	{
						fprintf(stderr, "Error mutex lock zone level in thread_trap_level\n");
						exit(EXIT_FAILURE);
					}

					zone_trap = zone_next;
				}

				level_info->map[trap->posX][trap->posY].specification = specification;

				trap = trap->succ;
			}

			if(pthread_mutex_unlock(&level_info->mutex_zone[zone_trap]) != 0) {
				fprintf(stderr, "Error mutex unlock zone level in thread_trap_level\n");
				exit(EXIT_FAILURE);
			}

			list_trap = list_trap->succ;
			
			pthread_testcancel();
			if(nanosleep(&time_wait, NULL) == -1) {
				fprintf(stderr, "Error with nanosleep in thread_trap_level");
			}
		}

		pthread_testcancel();
	}

	return NULL;
}
