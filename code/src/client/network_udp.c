#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include "network_udp.h"
#include "network_request.h"

void send_id_to_init_communication(int port, char address_ip[15], int code_request){
    int sockfd; 
    struct sockaddr_in address; 
    request_init_communication_t request_init; 

    // Create socket UDP
    if((sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1){
        perror("[ERROR] - Error creating socket");
        exit(EXIT_FAILURE); 
    }

    // File the adress structure
    memset(&address, 0, sizeof(struct sockaddr_in)); 
    address.sin_family = AF_INET; 
    address.sin_port = htons(port); 
    if(inet_pton(AF_INET, address_ip, &address.sin_addr)!=1){
        perror("[ERROR] - Error converting address"); 
        exit(EXIT_FAILURE); 
    }

    // Send request
    request_init.id_request = code_request; 
    
    if(sendto(sockfd, &request_init, sizeof(request_init_communication_t), 0, 
            (struct sockaddr*)&address, sizeof(struct sockaddr_in))==-1){
        perror("[ERROR] - Error sending request"); 
        exit(EXIT_FAILURE); 
    }

    // Close socket
    if(close(sockfd)==-1){
        perror("[ERROR] - Error closing socket"); 
        exit(EXIT_FAILURE); 
    }

}

void send_pseudo_to_server(char *pseudo, int port, char address_ip[15]){
    int sockfd; 
    struct sockaddr_in address; 
    request_first_connexion_t request; 

    // Create socket UDP
    if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        perror("[ERROR] - Error creating socket"); 
        exit(EXIT_FAILURE); 
    }

    // Fille the address structure
    memset(&address, 0, sizeof(struct sockaddr_in)); 
    address.sin_family = AF_INET; 
    address.sin_port = htons(port); 
    if(inet_pton(AF_INET, address_ip, &address.sin_addr) != 1){
        perror("[ERROR] - Error converting address"); 
        exit(EXIT_FAILURE); 
    }

    // Send request
    request.id = getpid(); 
    strcpy(request.pseudo, pseudo); 

    if(sendto(sockfd, &request, sizeof(request_first_connexion_t), 0, 
            (struct sockaddr*)&address,sizeof(struct sockaddr_in))==-1){
        perror("[ERROR] - Error sending request"); 
        exit(EXIT_FAILURE); 
    }

    if(close(sockfd) == -1){
        perror("[ERROR] - Error closing socket"); 
        exit(EXIT_FAILURE); 
    }
}
