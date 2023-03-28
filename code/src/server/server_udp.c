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
#include "server_tcp.h"
#include "info_client.h"
#include "function.h"


void save_new_client(list_info_client_t* connected_clients, char pseudo[MAX_MSG], char* client_address, 
                    int nb_client, int port){    
    info_client_t* new_client = init_info_client(nb_client, pseudo, client_address, port);
    add_client(connected_clients, new_client);
}


void add_client_at_game(list_game_t* list_game, int id_game, info_client_t* client_to_join, int port, int sockfd){
    game_t* game = search_game(list_game, id_game);
    add_client(game->list_players, client_to_join);
    game->nb_participants_actual++;
    if(game->nb_participants_final == game->nb_participants_actual){
        printf("[INFO][%s] - Game n°%d is full\n", get_timestamp(), id_game);
        create_socket_tcp(port, game, sockfd);
    }
}

void send_tcp_socket(int port, int port_tcp, game_t* game, int sockfd){
    struct sockaddr_in address; 
    response_server_udp_t response;
    char client_address_str[INET_ADDRSTRLEN];
    info_client_t* current = game->list_players->head;

    while(current != NULL){
        // Fill server address
        memset(&address, 0, sizeof(address));
        address.sin_family = AF_INET;
        address.sin_port = htons(current->port);
        if(inet_pton(AF_INET, current->client_address, &address.sin_addr) != 1) {
            perror("Error converting address");
            exit(EXIT_FAILURE);
        }

        response.content.port_tcp = port_tcp;

        if(sendto(sockfd, &response, sizeof(response_server_udp_t), 0, 
            (struct sockaddr*)&address,sizeof(struct sockaddr_in))==-1){
            perror("[ERROR] - Error sending request"); 
            exit(EXIT_FAILURE); 
        }else{
            // Display IP Adress
            inet_ntop(AF_INET, &address.sin_addr, client_address_str, INET_ADDRSTRLEN);
            printf("[INFO][%s] - Request with port TCP sent to %s with port n°%d\n", get_timestamp(), 
                    client_address_str, current->port);
        }
        current = current->next;
    }

}
