#ifndef __INCLUDE_GAME_H__
#define __INCLUDE_GAME_H__

#include "world_info.h"
#include "move_world.h"
#include "entity.h"
#include "player.h"

world_info_t world_info;
int number_player;

entity_t *players;

entity_t **enemy; // List of enemies according to their level

#endif