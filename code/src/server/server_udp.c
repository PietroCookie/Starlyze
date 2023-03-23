#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "network_request.h"
#include "server_udp.h"

list_connected_client* init_list_connected_client(int nb_clients){
    list_connected_client* connected_clients; 
    if((connected_clients = (list_connected_client*) malloc(sizeof(list_connected_client))) == NULL){
        perror("[ERROR] - Memory allocation connected_clients failed"); 
        exit(EXIT_FAILURE); 
    }
    if((connected_clients->list = (info_client_t*) malloc(nb_clients * sizeof(info_client_t)))==NULL){
        perror("[ERROR] - Memory allocation connected_clients->list failed"); 
        exit(EXIT_FAILURE); 
    }
    return connected_clients; 
}

void save_new_client(list_connected_client* connected_clients, char pseudo[MAX_MSG], char* client_address, int nb_client){
    if((connected_clients->list = (info_client_t*) realloc(connected_clients->list, (nb_client+1) * sizeof(info_client_t)))==NULL){
        perror("[ERROR] - Memory reallocation connected_clients->list failed"); 
        exit(EXIT_FAILURE); 
    }
    
    connected_clients->list[nb_client].id = nb_client; 
    strcpy(connected_clients->list[nb_client].pseudo, pseudo); 

    connected_clients->list[nb_client].client_address = malloc((INET_ADDRSTRLEN + 1) * sizeof(char));
    if(connected_clients->list[nb_client].client_address == NULL){
        perror("[ERROR] - Memory allocation client_address failed"); 
        exit(EXIT_FAILURE); 
    }
    strcpy(connected_clients->list[nb_client].client_address, client_address);
    connected_clients->list->prev = NULL; 
    connected_clients->list->next = NULL;
}

void print_list_connected_client(list_connected_client list, int nb_clients){
    int i;
    for(i = 1; i <= nb_clients; i++){
        if(list.list[i].id != -1){
            printf("Client %d - Pseudo: %s - Adresse: %s\n", list.list[i].id, list.list[i].pseudo, list.list[i].client_address);
        }
    }
}

list_game_t* init_list_games(int nb_games){
    list_game_t* list;
    if((list = (list_game_t*) malloc(sizeof(list_game_t)))==NULL){
        perror("[ERROR] - Memory allocation list_game failed"); 
        exit(EXIT_FAILURE); 
    }
    list->nb_games = nb_games; 

    if((list->game=(game_t*) malloc(sizeof(game_t)*nb_games))==NULL){
        perror("[ERROR] - Memory allocation list_game->game_t failed"); 
        exit(EXIT_FAILURE); 
    }

    return list; 
}

void save_new_game(list_game_t* list_game, int nb_games, int nb_participants_final, char name_world[MAX_MSG], 
                    info_client_t* new_client){
    list_game->nb_games = nb_games; 
    if((list_game->game = (game_t*) realloc(list_game->game, sizeof(game_t)*nb_games+1))==NULL){
        perror("[ERROR] - Memory reallocation list_game->list failed"); 
        exit(EXIT_FAILURE); 
    }
    printf("{DEBUG} - save_new_game - nb_games: %d", nb_games); 
    list_game->game[nb_games].id = nb_games; 
    strcpy(list_game->game[nb_games].name_world, name_world);
    list_game->game[nb_games].nb_participants_actual = 1; 
    list_game->game[nb_games].nb_participants_final = nb_participants_final;
    list_info_client_t* list = malloc(sizeof(list_info_client_t)); 
    init_list_info_client_t(list);
    add_client(list, new_client);
    print_list_client(*list); 
}

void print_list_game(list_game_t list_game){
    int i;
    for(i = 1; i <= list_game.nb_games; i++){
        printf("Game %d - Name world: %s - Nb participants actual: %d - Nb participants final: %d\n", 
                list_game.game[i].id, list_game.game[i].name_world, list_game.game[i].nb_participants_actual, 
                list_game.game[i].nb_participants_final);
        printf("List participants: \n");
    }
}

void delete_client_disconnection(list_connected_client* list, int id_client, int nb_clients){
    // if (id_client < 0) {
    //     printf("L'indice %d est invalide.\n", id_client);
    //     return;
    // }
    // // Libérer la mémoire allouée pour l'adresse client
    // free(list->list[id_client].client_address);
    
    // // Déplacer les éléments suivants vers la gauche
    // for (int i = id_client; i < list->num_clients - 1; i++) {
    //     list->list[i] = list->list[i+1];
    // }
    printf("Delete client disconnection\n"); 
}