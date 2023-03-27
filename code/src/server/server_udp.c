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

void save_new_client(list_connected_client* connected_clients, char pseudo[MAX_MSG], char* client_address, int nb_client){    
    info_client_t* new_client = init_info_client(nb_client, pseudo, client_address);
    add_client_connected(connected_clients, new_client);
    print_list_connected_clients(*connected_clients);
}


void add_client_at_game(list_game_t* list_game, int id_game, int id_client){
    
}

