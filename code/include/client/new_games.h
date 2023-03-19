#ifndef __NEW_GAMES_H__
#define __NEW_GAMES_H__

#include <dirent.h>
#include "interface_client.h"

typedef struct{
    struct dirent **name_world; 
    int nb_world; 
}list_world_t; 

void handler_new_games(interface_client_t *interface);

int filter_file(const struct dirent *entry); 

list_world_t recovering_existing_worlds(); 

void display_list_world (interface_client_t *interface, list_world_t list_world); 


#endif