#include "info_client.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void init_list_info_client(list_info_client_t* list){
    list->head = NULL; 
    list->nb_clients = 0;
}

info_client_t* init_info_client(int id, char pseudo[MAX_MSG], char* client_address, int port){
    info_client_t* info = malloc(sizeof(info_client_t));
    info->id = id; 
    strcpy(info->pseudo, pseudo); 
    info->client_address = client_address;
    info->port = port;
    info->next = NULL; 
    info->prev = NULL; 
    return info; 
}

int is_empty_client(list_info_client_t* list){
    if(list->head == NULL){
        return 1; // Right
    }else{
        return 0; // False
    }
}

void add_client(list_info_client_t* list, info_client_t* client){
    if(is_empty_client(list)==1){
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
    // if(list->head == NULL){
    //     list->head = client; 
    // }else{
    //     client->next = list->head;
    //     list->head->prev = client;
    //     list->head = client;
    // }
}

void print_list_client(list_info_client_t list){
    if(is_empty_client(&list)==1){
        printf("Liste vide\n");
    }else{
        info_client_t* current = list.head; 
        while(current != NULL){
            printf("Client %d - Pseudo: %s - Adresse: %s - Port : %d\n", current->id, current->pseudo, current->client_address, current->port);
            current = current->next; 
        }
    }
}

info_client_t* search_client(list_info_client_t* list, int id){
    info_client_t* current = list->head; 
    while(current != NULL){
        if(current->id == id){
            return current; 
        }
        current = current->next; 
    }
    return NULL; 
}

void delete_client(list_info_client_t* list, info_client_t* client){
    if(client->prev == NULL){
        list->head = client->next; 
    }else{
        client->prev->next = client->next; 
    }
    if(client->next != NULL){
        client->next->prev = client->prev; 
    }
    free(client); 
    list->nb_clients--;
}

void delete_list(list_info_client_t* list){
    info_client_t* current = list->head; 
    while(current != NULL){
        info_client_t* next = current->next; 
        free(current); 
        current = next; 
    }
    list->head = NULL; 
}