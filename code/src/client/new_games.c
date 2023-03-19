#include "new_games.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"


void handler_new_games(interface_client_t *interface){
    list_world_t list_world = recovering_existing_worlds(); 
    display_list_world(interface, list_world); 
}

int filter_file(const struct dirent *entry){
    if(entry->d_type == DT_REG){
        if(strstr(entry->d_name, ".bin") != NULL){
            return 1; // File accepted
        } 
    }
    return 0; 
}

list_world_t  recovering_existing_worlds(){
    list_world_t list_world;
    char *name, *last_dot;
    // Scans the directory with the custom filter function and retrieve the number of files
    list_world.nb_world = scandir(".", &list_world.name_world, filter_file, alphasort); 

    if (list_world.name_world < 0) {
        perror("Error when browsing the directory");
        exit(EXIT_FAILURE); 
    }

    for (int i = 0; i < list_world.nb_world; i++) {
        name = list_world.name_world[i]->d_name;
        // Find the last dot in the file name
        last_dot = strrchr(name, '.'); 
        // Removes the file name extension
        if (last_dot != NULL) {
            *last_dot = '\0'; 
        }
        free(list_world.name_world[i]); 
    }
    return list_world; 
}


void display_list_world(interface_client_t *interface, list_world_t list_world){
    window_mvprintw_col(interface->win_main, 11, 4, CYAN, "############### Liste des mondes ###############"); 
    for(int i=0; i<list_world.nb_world; i++){
        if(i>=0 && i<7){
            window_mvprintw_col(interface->win_main, 12+i, 4, WHITE, "%d) %s ", i+1, list_world.name_world[i]->d_name); 
            window_refresh(interface->win_main); 
        }else if(i>=7 && i<14){
            window_mvprintw_col(interface->win_main, 5+i, 20, WHITE, "%d) %s ", i+1, list_world.name_world[i]->d_name); 
            window_refresh(interface->win_main); 
        }else if(i>=14 && i<21){
            window_mvprintw_col(interface->win_main, i-2, 35, WHITE, "%d) %s ", i+1, list_world.name_world[i]->d_name); 
            window_refresh(interface->win_main); 
        }
    }
}