#ifndef __GAME_H__
#define __GAME_H__

#define MAX_MSG 255
#include "info_client.h"


struct game_t{
    int id; 
    int nb_participants_final; 
    int nb_participants_actual;
    char name_world[MAX_MSG]; 
    list_info_client_t* list_players; 
    struct game_t* next; 
    struct game_t* prev; 
}; 
typedef struct game_t game_t;

typedef struct{
    game_t* head; 
    int nb_games;
}list_game_t; 

list_game_t* init_list_game(int nb_games);

game_t* init_game(int id, int nb_participants_final, int nb_participants_actual, char name_world[MAX_MSG], info_client_t* new_client); 

int is_empty_game(list_game_t* list);

void add_game(list_game_t* list, game_t* game);

void print_list_game(list_game_t list);

game_t* search_game(list_game_t* list, int id);

void delete_game(list_game_t* list, game_t* game);

void delete_list_game(list_game_t* list);


#endif