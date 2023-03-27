#include "client_join_game.h"
#include "network_request.h"
#include "client_utility.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

list_game_without_pointers_t receive_list_games_on_hold(int port, char ip_server[15]){
    int sockfd, stop=0; 
    struct sockaddr_in address; 
    request_client_udp_t request;
    response_server_udp_t response;

    // Create socket UDP
    if((sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1){
        perror("[ERROR] - Error creating socket"); 
        exit(EXIT_FAILURE); 
    }

    // Fill the address structure
    memset(&address, 0, sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if(inet_pton(AF_INET, ip_server, &address.sin_addr)!=1){
        perror("[ERROR] - Error converting address"); 
        exit(EXIT_FAILURE); 
    }

    // Send request to server
    request.type_request = CLIENT_SEND_LIST_GAME;

    while(stop==0){
        if(sendto(sockfd, &request, sizeof(request_client_udp_t), 0, 
            (struct sockaddr*)&address, sizeof(struct sockaddr_in))==-1){
            perror("[ERROR] - Error sending request");
            exit(EXIT_FAILURE);
        }

        if(recvfrom(sockfd, &response, sizeof(response_server_udp_t), 0, NULL, 0)==-1){
            perror("[ERROR] - Error receiving response");
            exit(EXIT_FAILURE);
        }else{
            stop=1; 
        }
    }

    if(close(sockfd)==-1){
        perror("[ERROR] - Error closing socket"); 
        exit(EXIT_FAILURE); 
    }


    return response.content.list_game;
}

void join_game(int port, char ip_server[15], int choice_game, int id_client){
    int sockfd; 
    struct sockaddr_in address; 
    request_client_udp_t request;

    // Create socket UDP
    if((sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1){
        perror("[ERROR] - Error creating socket"); 
        exit(EXIT_FAILURE); 
    }

    // Fill the address structure
    memset(&address, 0, sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if(inet_pton(AF_INET, ip_server, &address.sin_addr)!=1){
        perror("[ERROR] - Error converting address"); 
        exit(EXIT_FAILURE); 
    }

    // Send request to server
    request.type_request = CLIENT_JOIN_GAME;
    request.content.choice_game[0] = choice_game;
    request.content.choice_game[1] = id_client;

    if(sendto(sockfd, &request, sizeof(request_client_udp_t), 0, 
        (struct sockaddr*)&address, sizeof(struct sockaddr_in))==-1){
        perror("[ERROR] - Error sending request");
        exit(EXIT_FAILURE);
    }

    if(close(sockfd)==-1){
        perror("[ERROR] - Error closing socket"); 
        exit(EXIT_FAILURE); 
    }
}