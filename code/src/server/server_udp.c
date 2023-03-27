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
#include "info_client.h"
#include "function.h"

void save_new_client(list_connected_client* connected_clients, char pseudo[MAX_MSG], char* client_address, int nb_client){    
    info_client_t* new_client = init_info_client(nb_client, pseudo, client_address);
    add_client_connected(connected_clients, new_client);
}


void add_client_at_game(list_game_t* list_game, int id_game, info_client_t* client_to_join){
    game_t* game = search_game(list_game, id_game);
    add_client(game->list_players, client_to_join);
    game->nb_participants_actual++;
    if(game->nb_participants_final == game->nb_participants_actual){
        printf("[INFO][%s] - Game is full\n", get_timestamp());
        // TODO: Send message to all clients in the game to start the game
    }
}

