#ifndef __CLIENT_UTILITY_H__
#define __CLIENT_UTILITY_H__

#include <dirent.h>

#define MAX_MSG 255

typedef struct{
    struct dirent **name_world; 
    int nb_world; 
}list_world_t; 

void display_logo_app(); 
char* pseudo_entry(); 
void display_menu(int, int, char[15]); 
void handler_menu(int, int, char[15]);

int filter_file(const struct dirent *entry); 
list_world_t recovering_existing_worlds(); 

int handler_list_world(list_world_t list_world); 


#endif