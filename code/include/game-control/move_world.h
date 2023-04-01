/**
 * @file move_world.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manage move_world
 * @version 0.1
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __MOVE_WORLD_H__
#define __MOVE_WORLD_H__

#include "game_control.h"
#include "world_info.h"
#include "level_info.h"
#include "entity.h"
#include "sprite.h"

/**
 * @brief Possible directions of travel
 * 
 */
typedef enum {
	LEFT = 1,
	RIGHT = 2,
	UP = 3,
	DOWN = 4
} direction_enum;

/**
 * @brief Information for the thread waiting for an item to reappear
 * 
 */
typedef struct
{
	int infos[3];
	level_info_t *level;
} infos_wait_item_t;

/**
 * @brief Information for the thread of a bomb explosion
 * 
 */
typedef struct 
{
	int position[2];
	int number_players;
	int number_enemy;
	int delay_explosion;
	int id_level;
	world_info_t *world_info;
	entity_t *enemy_level;
	entity_t *players;
	type_sprite_enum last_sprite;
} infos_bomb_explose_t;

/**
 * @brief The thread managing the reappearance of an item after a random time
 * 
 * @param arg The necessary thread information
 * @return void* The result of this Thread - there is NULL
 */
void *thread_wait_item(void *arg);

/**
 * @brief The thread that manages the explosion of a bomb
 * 
 * @param arg The information needed for the thread
 * @return void* The result of this Thread - there is NULL
 */
void *thread_explose_bomb(void *arg);

/**
 * @brief Move an entity within a level or between levels
 * 
 * @param game_control_info The game manager
 * @param id_level The identifier of the level in which the entity we are moving is
 * @param entity_move The entity that is moved
 * @param direction Direction of the entity
 * @return int If the trip went wells
 */
int move_level(game_control_t *game_control_info, int id_level, entity_t *entity_move, direction_enum direction);

/**
 * @brief Resets a player to the beginning of the world by emptying his inventory
 * 
 * @param world_info Information from a world
 * @param player The player whose position and inventory are reset in the world
 */
void reset_player(world_info_t world_info, entity_t *player);

/**
 * @brief Checks if a player has won the game
 * 
 * @param game_control_info The game manager
 * @param player The player who we want to know if he won
 */
void check_victory(game_control_t *game_control_info, entity_t player);

/**
 * @brief Checks the validity of a move
 * 
 * @param level The level in which we move
 * @param posX_dest Position X of displacement
 * @param posY_dest Position Y of displacement
 * @param posX_width Position X of displacement considering the width of the entity
 * @param posY_height Position Y of displacement considering the height of the entity
 * @param entity_move The entity whose displacement is being checked
 * @return int If the move is validated or not
 */
int check_validation_move(level_info_t *level, int posX_dest, int posY_dest, int posX_width, int posY_height, entity_t *entity_move);

/**
 * @brief Checks the validity of a move of enemy
 * 
 * @param level The level in which we move
 * @param posX_dest Position X of displacement
 * @param posY_dest Position Y of displacement
 * @param posX_width Position X of displacement considering the width of the enemy
 * @param posY_height Position Y of displacement considering the height of the enemy
 * @param entity_move The enemy whose displacement is being checked
 * @return int If the move is validated or not
 */
int check_validation_move_enemy(level_info_t *level, int posX_dest, int posY_dest, int posX_width, int posY_height, entity_t *entity_move);

/**
 * @brief Checks the validity of a move of player
 * 
 * @param level The level in which we move
 * @param posX_dest Position X of displacement
 * @param posY_dest Position Y of displacement
 * @param posX_width Position X of displacement considering the width of the player
 * @param posY_height Position Y of displacement considering the height of the player
 * @param entity_move The player whose displacement is being checked
 * @return int If the move is validated or not
 */
int check_validation_move_player(level_info_t *level, int posX_dest, int posY_dest, int posX_width, int posY_height, entity_t *entity_move);

/**
 * @brief Checks for collisions of an entity on a level
 * 
 * @param collision The entity whose collisions we want to check
 * @param collider Table of colliding entities
 * @param number_collider The number of entities that can collide
 * @param level The identifier of the level in which the collisions are checked
 * @return entity_t* The entity with which we collided or NULL if there is none
 */
entity_t* check_collision(entity_t *collision, entity_t *collider, int number_collider, int level);

/**
 * @brief Allows to check if a player is on the position of an item and to recover it if necessarys
 * 
 * @param level The level at which the item potential is checked and recovered
 * @param player The player who will retrieve the item
 * @param posX_dest Position X of the player
 * @param posY_dest Position Y of the player
 * @param posX_width Position X of the player considering the width of the player
 * @param posY_height Position Y of the player considering the height of the player
 */
void take_item(level_info_t *level, player_t *player, int posX_dest, int posY_dest, int posX_width, int posY_height);

/**
 * @brief Allows to pass a door and to change level
 * 
 * @param world_info The informations of the world
 * @param player The player who borrows a doors
 */
void enter_door(world_info_t *world_info, entity_t *player);

/**
 * @brief Allows a player to place a bomb
 * 
 * @param game_control The game manager
 * @param player The player who places a bombs
 */
void drop_bomb(game_control_t *game_control, entity_t *player);

#endif