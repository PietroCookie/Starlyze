#include "clients_connected.h"
#include <stdio.h>
#include <stdlib.h>


list_connected_client* init_list_connected_client(int nb_clients){
    list_connected_client* list = malloc(sizeof(list_connected_client));
    list->head = NULL;
    list->nb_clients = nb_clients;
    return list;
}


int is_empty_connected_clients(list_connected_client* list){
    if(list->head == NULL){
        return 1; // Right
    }else{
        return 0; // False
    }
}

void add_client_connected(list_connected_client* list, info_client_t* client){
    if(is_empty_connected_clients(list)==1){
        list->head = client; 
        list->head->next = NULL; 
        list->head->prev = NULL;
    }else{
        client->next = list->head; 
        if(list->head != NULL){
            list->head->prev = client; 
        }
        list->head = client; 
        client->prev = NULL;
    }
    list->nb_clients++;
}

void print_list_connected_clients(list_connected_client list){
    printf("========== Liste des clients connectés ================\n");
    info_client_t* current = list.head;
    while(current != NULL){
        printf(">> Informations sur le client n°%d\n", current->id); 
        printf("Client %d - Pseudo: %s - Adresse: %s\n", current->id, current->pseudo, current->client_address);
        printf("\n\n"); 
        current = current->next;
    }
}

info_client_t* search_client_connected(list_connected_client* list, int id){
    info_client_t* current = list->head; 
    while(current != NULL){
        if(current->id == id){
            return current; 
        }
        current = current->next; 
    }
    return NULL; 
}

void delete_client_connected(list_connected_client* list, info_client_t* client){
    if(client->prev == NULL){
        list->head = client->next;
    }else{
        client->prev->next = client->next;
    }
    if(client->next != NULL){
        client->next->prev = client->prev;
    }
    free(client);
}

void delete_list_connected(list_connected_client* list){
    info_client_t* current = list->head;
    while(current != NULL){
        info_client_t* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}

