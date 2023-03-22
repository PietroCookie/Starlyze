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
}

void print_list_connected_client(list_connected_client list, int nb_clients){
    int i;
    for(i = 1; i <= nb_clients; i++){
        if(list.list[i].id != -1){
            printf("Client %d - Pseudo: %s - Adresse: %s\n", list.list[i].id, list.list[i].pseudo, list.list[i].client_address);
        }
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