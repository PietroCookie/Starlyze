#ifndef __SERVER_UDP_H__
#define __SERVER_UDP_H__

#define MAX_MSG 255


typedef struct{
    int id; 
    char pseudo[MAX_MSG]; 
    char* client_address; 
}info_client_t; 

typedef struct{
    info_client_t* list; 
    int nb_clients;
}list_connected_client; 

list_connected_client* init_list_connected_client(int nb_clients); 
void save_new_client(list_connected_client* connected_clients, char pseudo[MAX_MSG], char* client_adress, int nb_client); 
void print_list_connected_client(list_connected_client list, int nb_clients);
void send_nb_client(int nb_clients, int port); 
void delete_client_disconnection(list_connected_client* list, int id_client, int nb_clients); 

#endif