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

void save_new_client(list_connected_client* connected_clients, char pseudo[MAX_MSG], char* client_address, int nb_client){    
    info_client_t* new_client = init_info_client(nb_client, pseudo, client_address);
    add_client_connected(connected_clients, new_client);
    print_list_connected_clients(*connected_clients);
}

void save_new_game(list_game_t* list_game, int nb_games, int nb_participants_final, char name_world[MAX_MSG], 
                    info_client_t* new_client){
    game_t* new_game = init_game(nb_games, nb_participants_final, 1, name_world, new_client);
    add_game(list_game, new_game);
    print_list_game(*list_game);
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