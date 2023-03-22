#ifndef __CREATE_GAME_H__
#define __CREATE_GAME_H__

#include <dirent.h>

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


#endif