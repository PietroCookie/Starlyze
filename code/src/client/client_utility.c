#include "client_utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void display_logo_app(){
    printf("##################################################################################################################\n"); 
    printf("#        /_/_/_/   /_/_/_/_/_/      /_/_/       /_/_/_/       /_/      /_/      /_/    /_/_/_/_/_/    /_/_/_/_/  #\n");
    printf("#     /_/             /_/        /_/   /_/     /_/   /_/     /_/        /_/  /_/            /_/      /_/         #\n"); 
    printf("#      /_/_/         /_/        /_/_/_/_/     /_/_/_/       /_/          /_/            /_/         /_/_/_/      #\n"); 
    printf("#         /_/       /_/        /_/   /_/     /_/   /_/     /_/          /_/          /_/           /_/           #\n"); 
    printf("#  /_/_/_/         /_/        /_/   /_/     /_/   /_/     /_/_/_/_/    /_/        /_/_/_/_/_/     /_/_/_/_/      #\n"); 
    printf("##################################################################################################################\n");
}

char* pseudo_entry(){
    char* pseudo; 
    if((pseudo=malloc(MAX_MSG*sizeof(char)))==NULL){
        perror("[ERROR] - Memory allocation pseudo failed"); 
        exit(EXIT_FAILURE); 
    } 
    printf("\n\n============================ I N F O S ============================\n"); 
    printf("Veuillez saisir votre pseudo : "); 
    if(scanf("%[^\n]", pseudo) == -1){
        perror("[ERROR] - Error when retrieving the choice\n"); 
        exit(EXIT_FAILURE);        
    }
    printf("===================================================================\n"); 
    return pseudo; 
}

void display_menu(int nb_players, int port, char address_ip[15]){
    printf("\n\n======================== M E N U ========================      ||  ======= I N F O R M A T I O N S ======\n"); 
    printf(" 1°) << Nombre de joueur(s) connecte(s) sur Starlyze : %d >>    ||    Adresse IP : %s                     \n", nb_players, address_ip); 
    printf(" 2°) << Créer une partie de STARLYZE >>                        ||    Port n° : %d                        \n", port); 
    printf(" 3°) << Rejoindre une partie en attente >>                     ||                                        \n"); 
    printf(" 4°) << Quitter le jeu >>                                      ||                                        \n"); 
    printf("=========================================================      ||  ======================================\n\n"); 
}

void handler_menu(int nb_players, int port, char address_ip[15]){
    int choice=0, choice_world; 
    list_world_t list_world; 
    while(choice<=0){
        printf("Quel est votre choix ? "); 
        if(scanf("%d", &choice) == -1){
            perror("[ERROR] - Error when retrieving the choice\n"); 
            exit(EXIT_FAILURE); 
        }
    }
    switch(choice){
        case 1 : 
            printf("\n\n====================== Nombre de joueur(s) connecte(s) ======================\n"); 
            break; 
        case 2 : 
            printf("\n\n====================== Créer une partie de STARLYZE ======================\n"); 
            list_world = recovering_existing_worlds(); 
            choice_world = handler_list_world(list_world); 
            if(choice_world == list_world.nb_world+1){
                display_menu(3, port, address_ip); 
                handler_menu(3, port, address_ip); 
            }
            break; 
        case 3 :  
            printf("\n\n====================== Rejoindre une partie en attente ======================\n"); 
            break; 
        case 4 : 
            printf("\n\n<<<<<<< Jeu en arrêt ... >>>>>>>\n"); 
            exit(EXIT_FAILURE); 
            break; 
        default : 
            fprintf(stderr, "\n[ERROR] - Error when selecting the menu\n"); 
            fprintf(stderr, "[HELP]  - Select a number between 1 and 4\n"); 
            break;
    }
}

int filter_file(const struct dirent *entry){
    if(entry->d_type == DT_REG){
        if(strstr(entry->d_name, ".bin") != NULL){
            return 1; 
        }
    }
    return 0; 
}

list_world_t recovering_existing_worlds(){
    list_world_t list_world;
    char *name, *last_dot;
    // Scans the directory with the custom filter function and retrieve the number of files
    list_world.nb_world = scandir(".", &list_world.name_world, filter_file, alphasort); 

    if (list_world.name_world < 0) {
        perror("[ERROR] - Error when browsing the directory");
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

int handler_list_world(list_world_t list_world){
    int choice = 0; 
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>> Liste des mondes <<<<<<<<<<<<<<<<<<<<<<<<<<\n"); 
    for(int i=0; i<list_world.nb_world; i++){
        printf("%d°) %s \n", i+1, list_world.name_world[i]->d_name); 
    }
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n"); 

    while(choice<=0){
        printf("\n[Tapez %d pour retourner au menu]\n", list_world.nb_world+1); 
        printf("Veuillez choisir un monde parmi ceux proprosés (ou option du retour vers le menu) : "); 

        if(scanf("%d", &choice) == -1){
            perror("[ERROR] - Error when retrieving the choice\n"); 
            exit(EXIT_FAILURE); 
        }
    }
    if(choice > list_world.nb_world+1){
        return 0;
    }else{
        return choice; 
    }    
}