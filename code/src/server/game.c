#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


list_game_t* init_list_game(int nb_games){
    list_game_t* list = malloc(sizeof(list_game_t));
    list->head = NULL;
    list->nb_games = nb_games;
    return list;
}

game_t* init_game(int id, int nb_participants_final, int nb_participants_actual, char name_world[MAX_MSG], info_client_t* new_client){
    game_t* game = malloc(sizeof(game_t));
    game->id = id;
    game->nb_participants_final = nb_participants_final;
    game->nb_participants_actual = nb_participants_actual;
    strcpy(game->name_world, name_world);
    game->list_players = malloc(sizeof(list_info_client_t)); 
    init_list_info_client(game->list_players);
    add_client(game->list_players, new_client);
    game->next = NULL; 
    game->prev = NULL;
    return game;
}

int is_empty_game(list_game_t* list){
    if(list->head == NULL){
        return 1; // Right
    }else{
        return 0; // False
    }
}

void add_game(list_game_t* list, game_t* game){
    if(is_empty_game(list)==1){
        list->head = game; 
        list->head->next = NULL; 
        list->head->prev = NULL;
    }else{
        game->next = list->head; 
        if(list->head != NULL){
            list->head->prev = game; 
        }
        list->head = game; 
        game->prev = NULL;
    }
}

void print_list_game(list_game_t list){
    printf("========== Liste des partie ================\n");
    game_t* current = list.head;
    while(current != NULL){
        printf(">> Informations sur la partie n°%d\n", current->id); 
        printf("Partie %d - Nombre de participants: %d - Nom du monde: %s\n", current->id, current->nb_participants_final, current->name_world);
        printf(">> Joueurs inscrits :\n");
        print_list_client(*current->list_players);
        printf("\n\n"); 
        current = current->next;
    }
}

game_t* search_game(list_game_t* list, int id){
    game_t* current = list->head; 
    while(current != NULL){
        if(current->id == id){
            return current; 
        }
        current = current->next; 
    }
    return NULL; 
}

void delete_game(list_game_t* list, game_t* game){
    if(game->prev == NULL){
        list->head = game->next;
    }else{
        game->prev->next = game->next;
    }
    if(game->next != NULL){
        game->next->prev = game->prev;
    }
    free(game);
}

void delete_list_game(list_game_t* list){
    game_t* current = list->head;
    while(current != NULL){
        game_t* next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}
