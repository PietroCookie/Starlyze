#include "game.h"
#include "info_client.h"

void init_list_game(list_game_t* list, int nb_games){
    list->head = NULL;
    list->nb_games = nb_games;
}

game_t* init_game(int id, int nb_participants_final, int nb_participants_actual, char name_world[MAX_MSG]){
    game_t* game = malloc(sizeof(game_t));
    game->id = id;
    game->nb_participants_final = nb_participants_final;
    game->nb_participants_actual = nb_participants_actual;
    strcpy(game->name_world, name_world);
    list_info_client_t* list_client = malloc(sizeof(list_info_client_t)); 
    init_list_info_client_t(list_client);
    game->next = NULL; 
    game->prev = NULL;
    return game;
}

int is_empty(list_game_t* list){
    if(list->head == NULL){
        return 1; // Right
    }else{
        return 0; // False
    }
}

void add_game(list_game_t* list, game_t* game){
    if(is_empty(list)==1){
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
    printf("Liste des partie\n");
    game_t* current = list.head;
    while(current != NULL){
        printf("Partie %d - Nombre de participants: %d - Nom du monde: %s\n", current->id, current->nb_participants_final, current->name_world);
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
