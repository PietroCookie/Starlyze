#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include "client_udp.h"
#include "network_request.h"

void send_pseudo_to_server(char *pseudo, int port, char address_ip[15]){
    int sockfd; 
    struct sockaddr_in address; 
    request_client_udp_t request; 

    // Create socket UDP
    if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        perror("[ERROR] - Error creating socket"); 
        exit(EXIT_FAILURE); 
    }

    // Fill the address structure
    memset(&address, 0, sizeof(struct sockaddr_in)); 
    address.sin_family = AF_INET; 
    address.sin_port = htons(port); 
    if(inet_pton(AF_INET, address_ip, &address.sin_addr) != 1){
        perror("[ERROR] - Error converting address"); 
        exit(EXIT_FAILURE); 
    }

    // Send request
    request.type_request = CLIENT_FIRST_CONNEXION_SEND_PSEUDO; 
    strcpy(request.content.pseudo, pseudo); 

    if(sendto(sockfd, &request, sizeof(request_client_udp_t), 0, 
            (struct sockaddr*)&address,sizeof(struct sockaddr_in))==-1){
        perror("[ERROR] - Error sending request"); 
        exit(EXIT_FAILURE); 
    }



    if(close(sockfd) == -1){
        perror("[ERROR] - Error closing socket"); 
        exit(EXIT_FAILURE); 
    }
}


int receive_nb_clients(int port, char address_ip[15]){
    int sockfd, stop=0; 
    struct sockaddr_in address; 
    request_client_udp_t request; 
    response_server_udp_t response; 

    // Create socket
    if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Fill the address structure
    memset(&address, 0, sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if(inet_pton(AF_INET, address_ip, &address.sin_addr) != 1) {
        perror("Error converting address");
        exit(EXIT_FAILURE);
    }

    request.type_request = CLIENT_NB_CLIENTS; 

    while(stop==0){
        if(sendto(sockfd, &request, sizeof(request_client_udp_t), 0, 
                (struct sockaddr*)&address, sizeof(struct sockaddr_in))==-1){
            perror("[ERROR] - Error sending request"); 
            exit(EXIT_FAILURE); 
        }
        if(recvfrom(sockfd, &response, sizeof(response_server_udp_t), 0, NULL, 0)==-1){
            if(errno == EINTR){
                perror("[ERROR] - Error receiving message"); 
                exit(EXIT_FAILURE); 
            }
        }else{
            stop=1;
        }
    }

    if(close(sockfd)==-1){
        perror("[ERROR] - Error closing socket"); 
    }
    
    return response.content.nb_clients; 
}