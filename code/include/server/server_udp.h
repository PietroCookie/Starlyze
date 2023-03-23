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

typedef struct{
    int id; 
    int nb_participants_final; 
    int nb_participants_actual;
    char name_world[255]; 
    info_client_t* list_players; 
}game_t; 

typedef struct{
    game_t* game; 
    int nb_games;
}list_game_t; 

list_connected_client* init_list_connected_client(int nb_clients); 

void save_new_client(list_connected_client* connected_clients, char pseudo[MAX_MSG], char* client_adress, int nb_client); 

void print_list_connected_client(list_connected_client list, int nb_clients);

void send_nb_client(int nb_clients, int port); 

void delete_client_disconnection(list_connected_client* list, int id_client, int nb_clients); 

list_game_t* init_list_games(int nb_games); 

void save_new_game(list_game_t* list_game, int nb_games, int nb_participants_final, char name_world[255], info_client_t new_client); 

void print_list_game(list_game_t list_game); 


#endif