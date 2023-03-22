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

list_connected_client* init_list_connected_client(int nb_clients){
    list_connected_client* connected_clients; 
    if((connected_clients = (list_connected_client*) malloc(sizeof(list_connected_client))) == NULL){
        perror("[ERROR] - Memory allocation connected_clients failed"); 
        exit(EXIT_FAILURE); 
    }
    if((connected_clients->list = (info_client_t*) malloc(nb_clients * sizeof(info_client_t)))==NULL){
        perror("[ERROR] - Memory allocation connected_clients->list failed"); 
        exit(EXIT_FAILURE); 
    }
    return connected_clients; 
}

void save_new_client(list_connected_client* connected_clients, char pseudo[MAX_MSG], char* client_address, int nb_client){
    if((connected_clients->list = (info_client_t*) realloc(connected_clients->list, (nb_client+1) * sizeof(info_client_t)))==NULL){
        perror("[ERROR] - Memory reallocation connected_clients->list failed"); 
        exit(EXIT_FAILURE); 
    }
    
    connected_clients->list[nb_client].id = nb_client; 
    strcpy(connected_clients->list[nb_client].pseudo, pseudo); 

    connected_clients->list[nb_client].client_address = malloc((INET_ADDRSTRLEN + 1) * sizeof(char));
    if(connected_clients->list[nb_client].client_address == NULL){
        perror("[ERROR] - Memory allocation client_address failed"); 
        exit(EXIT_FAILURE); 
    }
    strcpy(connected_clients->list[nb_client].client_address, client_address);
}

void print_list_connected_client(list_connected_client list, int nb_clients){
    int i;
    for(i = 1; i <= nb_clients; i++){
        if(list.list[i].id != -1){
            printf("Client %d - Pseudo: %s - Adresse: %s\n", list.list[i].id, list.list[i].pseudo, list.list[i].client_address);
        }
    }
}

// void send_nb_client(int nb_clients, int port){
//     int sockfd; 
//     struct sockaddr_in address; 
//     response_server_udp_t response; 

//     // Create socket
//     if((sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1){
//         perror("[ERROR] - Error creating socket"); 
//         exit(EXIT_FAILURE);
//     }

//     // Fill the address structure
//     memset(&address, 0, sizeof(struct sockaddr_in)); 
//     address.sin_family = AF_INET; 
//     address.sin_port = htons(port); 
//     if(inet_pton(AF_INET, port, &address.sin_addr) != 1){
//         perror("[ERROR] - Error converting address"); 
//         exit(EXIT_FAILURE); 
//     }

//     response.type_request = SERVER_SEND_NB_CLIENTS; 
//     response.content.nb_clients = nb_clients; 

//     if(sendto(sockfd, &response, sizeof(response_server_udp_t), 0, 
//             (struct sockaddr*)&address, sizeof(struct sockaddr_in))==-1){
//         perror("[ERROR] - Error sending request"); 
//         exit(EXIT_FAILURE); 
//     }

//     if(close(sockfd)==-1){
//         perror("[ERROR] - Error closing socket"); 
//     }
// }