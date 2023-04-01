/**
 * @file request_exchange.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that descrive different request of exchange between a game client and game server
 * @version 0.1
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __REQUEST_EXCHANGE_H__
#define __REQUEST_EXCHANGE_H__

#include "level_display.h"
#include "player.h"

typedef enum {
	REFRESH_LEVEL = 1,
	FREEZE_PLAYER = 2,
	END_GAME = 3
} type_request_send_player_enum;

/**
 * @brief The request that the server sends to the player
 * 
 */
typedef struct
{
	type_request_send_player_enum type_request;
	level_display_t level_display;
	union {
		int second_freeze;
		char message[50];
	};
	player_t player;
} request_send_player_t;

#endif