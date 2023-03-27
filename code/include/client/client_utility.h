#ifndef __CLIENT_UTILITY_H__
#define __CLIENT_UTILITY_H__

#include <dirent.h>
#include "create_game.h"
#include "info_client.h"

#define MAX_MSG 255

void display_logo_app(); 
char* pseudo_entry(); 
void display_menu(int, int, char[15]); 
void handler_menu(int, char[15],info_client_t);

#endif