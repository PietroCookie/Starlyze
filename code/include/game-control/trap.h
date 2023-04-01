/**
 * @file trap.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manage a trap
 * @version 0.1
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __TRAP_H__
#define __TRAP_H__

/**
 * @brief A square of a trap
 * 
 */
struct STrap
{
	int posX;
	int posY;
	struct STrap *succ;
};
typedef struct STrap trap_t;

/**
 * @brief A trap block, which is a list of trap boxess
 * 
 */
struct SList_trap
{
	trap_t *traps;
	struct SList_trap* succ;
};
typedef struct SList_trap list_trap_t;

/**
 * @brief A list of trap blocks
 * 
 */
typedef struct
{
	list_trap_t *blocks;
} list_block_trap_t;

/**
 * @brief Initializes a trap box
 * 
 * @param trap The trap box that is initialized
 * @param posX Position X of the trap box
 * @param posY Position Y of the trap box
 */
void initialise_trap(trap_t *trap, int posX, int posY);

/**
 * @brief Initialize a list of trap boxes
 * 
 * @param list The list of trap boxes that we initialize
 */
void initialise_list_trap(list_trap_t *list);

/**
 * @brief Insert a trap square into a trap block
 * 
 * @param list The trap block in which the trap box is added
 * @param trap The trap box that is added
 */
void insert_list_trap(list_trap_t *list, trap_t *trap);
/**
 * @brief Removes a trap cell from a trap block
 * 
 * @param list The trap block in which the trap box is remove
 * @param trap The trap box that is remove
 */
void delete_list_trap(list_trap_t *list, trap_t *trap);
/**
 * @brief Destroys a trap blocks
 * 
 * @param list The trap block that you want to remove
 */
void destroy_list_trap(list_trap_t *list);

/**
 * @brief Initialize a block list
 * 
 * @param list_block The list of blocks we want to initialize
 */
void initialise_list_block_trap(list_block_trap_t *list_block);
/**
 * @brief Insert a trap block in the trap block lists
 * 
 * @param list_block The block list in which we add a trap block
 * @param list_trap The trap block that is added
 */
void insert_list_block_trap(list_block_trap_t *list_block, list_trap_t *list_trap);
/**
 * @brief Removes a trap block from a trap block list
 * 
 * @param list_block The list of blocks in which you want to delete a block of traps
 * @param list_trap The trap block that we removes
 */
void delete_list_block_trap(list_block_trap_t *list_block, list_trap_t *list_trap);
/**
 * @brief Destroys a block list of traps
 * 
 * @param list_block The block list of traps that you want to destroy
 */
void destroy_list_block_trap(list_block_trap_t *list_block);

/**
 * @brief The thread that manages the trap blocks of a level
 * 
 * @param arg The information needed for the thread
 * @return void* The result of this Thread - there is NULL
 */
void *thread_trap_level(void *arg);

#endif