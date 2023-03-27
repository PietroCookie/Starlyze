#ifndef __CREATE_GAME_H__
#define __CREATE_GAME_H__

#include <dirent.h>
#include "game.h"
#include "info_client.h"


#define MAX_MSG 255

typedef struct{
    struct dirent **name_world; 
    int nb_world; 
}list_world_t; 

typedef struct{
    char name_world[255][255]; 
    int nb_world; 
}list_world_response_t; 

int filter_file(); 
list_world_response_t recovering_existing_worlds(); 
void save_new_game(list_game_t* list_game, int nb_games, int nb_participants_final, char name_world[MAX_MSG], 
                    info_client_t* new_client);


#endif