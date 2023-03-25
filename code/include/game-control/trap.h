#ifndef __TRAP_H__
#define __TRAP_H__

struct STrap
{
	int posX;
	int posY;
	struct STrap *succ;
};
typedef struct STrap trap_t;

struct SList_trap
{
	trap_t *traps;
	struct SList_trap* succ;
};
typedef struct SList_trap list_trap_t;

typedef struct
{
	list_trap_t *blocks;
} list_block_trap_t;


void initialise_trap(trap_t *trap, int posX, int posY);

void initialise_list_trap(list_trap_t *list);
void insert_list_trap(list_trap_t *list, trap_t *trap);
void delete_list_trap(list_trap_t *list, trap_t *trap);
void destroy_list_trap(list_trap_t *list);

void initialise_list_block_trap(list_block_trap_t *list_block);
void insert_list_block_trap(list_block_trap_t *list_block, list_trap_t *list_trap);
void delete_list_block_trap(list_block_trap_t *list_block, list_trap_t *list_trap);
void destroy_list_block_trap(list_block_trap_t *list_block);

void *thread_trap_level(void *arg);

#endif