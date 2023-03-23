#ifndef __CLIENTS_CONNECTED_H__
#define __CLIENTS_CONNECTED_H__

#include "info_client.h"

typedef struct{
    info_client_t* head; 
    int nb_clients;
}list_connected_client; 

list_connected_client* init_list_connected_client(int nb_clients); 

int is_empty_connected_clients(list_connected_client* list); 

void add_client_connected(list_connected_client* list, info_client_t* client); 

void print_list_connected_clients(list_connected_client list); 

info_client_t* search_client_connected(list_connected_client* list, int id); 

void delete_client_connected(list_connected_client* list, info_client_t* client); 

void delete_list_connected(list_connected_client* list); 

#endif