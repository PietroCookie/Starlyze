#ifndef __REQUEST_EXCHANGE_H__
#define __REQUEST_EXCHANGE_H__

#include "level_display.h"
#include "player.h"

typedef struct
{
	level_display_t level_display;
	player_t player;
} request_send_player_t;


#endif