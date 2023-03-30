/**
 * @file sprite.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manage sprite
 * @version 0.1
 * @date 2023-03-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <stdlib.h>

#include "window.h"
#include "colors.h"

#define MAX_ID_DOOR 99
#define MAX_ID_GATE_KEY 4

/**
 * @brief The enumeration of sprite types
 * 
 */
typedef enum {
	SPRITE_BLOCK = 1,
	SPRITE_LADDER = 2,
	SPRITE_TRAP = 3,
	SPRITE_GATE = 4,
	SPRITE_KEY = 5,
	SPRITE_DOOR = 6,
	SPRITE_EXIT = 7,
	SPRITE_START = 8,
	SPRITE_ROBOT = 9,
	SPRITE_PROBE = 10,
	SPRITE_LIFE = 11,
	SPRITE_BOMB = 12,
	SPRITE_PLAYER = 13
} type_sprite_enum;

/**
 * @brief The structure of a sprite
 * 
 */
typedef struct{
	type_sprite_enum type;
	int specification;
} sprite_t;

/**
 * @brief Allows to obtain the width of a sprite
 * 
 * @param type_sprite The type of sprite
 * @return int The width of the sprite
 */
int width_sprite(type_sprite_enum type_sprite);
/**
 * @brief Allows to obtain the height of a sprite
 * 
 * @param type_sprite The type of sprite
 * @return int The height of the sprite
 */
int height_sprite(type_sprite_enum type_sprite);

/**
 * @brief The size needed to save a sprite
 * 
 * @return size_t The necessary size
 */
size_t necessary_size_sprite();

/**
 * @brief Writes a sprite to a file descriptor
 * 
 * @param file_descriptor The file descriptor
 * @param sprite The sprite we want to write
 */
void write_sprite_in_file_descriptor(int file_descriptor, sprite_t sprite);
/**
 * @brief Read a sprite to a file descriptor
 * 
 * @param file_descriptor The file descriptor
 * @param sprite The sprite we want to read
 */
void read_sprite_in_file_descriptor(int file_descriptor, sprite_t* sprite);

/**
 * @brief Get the color gate key object
 * 
 * @param specification The specification of the gate or key
 * @return unsigned int Color of the gate or key
 */
unsigned int get_color_gate_key(int specification);

/**
 * @brief Draw a block
 * 
 * @param window The window in which the block is drawn
 * @param posX Position X of the block
 * @param posY Position Y of the block
 */
void paint_block(window_t* window, int posX, int posY);
/**
 * @brief Draw a ladder
 * 
 * @param window The window in which the ladder is drawn
 * @param posX Position X of the ladder
 * @param posY Position Y of the ladder
 */
void paint_ladder(window_t* window, int posX, int posY);
/**
 * @brief Draw a trap
 * 
 * @param window The window in which the trap is drawn
 * @param posX Position X of the trap
 * @param posY Position Y of the trap
 */
void paint_trap(window_t* window, int posX, int posY);
/**
 * @brief Draw a key
 * 
 * @param window The window in which the key is drawn
 * @param posX Position X of the key
 * @param posY Position Y of the key
 * @param id_key The identifier of the keys
 */
void paint_key(window_t* window, int posX, int posY, int id_key);
/**
 * @brief Draw a gate
 * 
 * @param window The window in which the gate is drawn
 * @param posX Position X of the gate
 * @param posY Position Y of the gate
 * @param id_gate The identifier of the gate
 */
void paint_gate(window_t* window, int posX, int posY, int id_gate);
/**
 * @brief Draw a door
 * 
 * @param window The window in which the door is drawn
 * @param posX Position X of the door
 * @param posY Position Y of the door
 * @param sprite The sprite of the door
 */
void paint_door(window_t* window, int posX, int posY, sprite_t sprite);
/**
 * @brief Draw a exit
 * 
 * @param window The window in which the exit is drawn
 * @param posX Position X of the exit
 * @param posY Position Y of the exit
 */
void paint_exit(window_t* window, int posX, int posY);
/**
 * @brief Draw a start
 * 
 * @param window The window in which the start is drawn
 * @param posX Position X of the start
 * @param posY Position Y of the start
 */
void paint_start(window_t* window, int posX, int posY);
/**
 * @brief Draw a robot
 * 
 * @param window The window in which the robot is drawn
 * @param posX Position X of the robot
 * @param posY Position Y of the robot
 */
void paint_robot(window_t* window, int posX, int posY);
/**
 * @brief Draw a probe
 * 
 * @param window The window in which the probe is drawn
 * @param posX Position X of the probe
 * @param posY Position Y of the probe
 */
void paint_probe(window_t* window, int posX, int posY);
/**
 * @brief Draw a heart
 * 
 * @param window The window in which the heart is drawn
 * @param posX Position X of the heart
 * @param posY Position Y of the heart
 */
void paint_heart(window_t* window, int posX, int posY);
/**
 * @brief Draw a bomb
 * 
 * @param window The window in which the bomb is drawn
 * @param posX Position X of the bomb
 * @param posY Position Y of the bomb
 */
void paint_bomb(window_t* window, int posX, int posY);
/**
 * @brief Draw a player
 * 
 * @param window The window in which the player is drawn
 * @param posX Position X of the player
 * @param posY Position Y of the player
 */
void paint_player(window_t *window, int posX, int posY, unsigned int color);

#endif