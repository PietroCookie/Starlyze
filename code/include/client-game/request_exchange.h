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

/**
 * @brief The request for display game in client
 * 
 */
typedef struct
{
	level_display_t level_display;
	player_t player;
} request_send_player_t;


#endif