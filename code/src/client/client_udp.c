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
    request_client_udp request; 

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
    request.type_request = FIRST_CONNEXION_SEND_PSEUDO; 
    strcpy(request.content.pseudo, pseudo); 

    if(sendto(sockfd, &request, sizeof(request_client_udp), 0, 
            (struct sockaddr*)&address,sizeof(struct sockaddr_in))==-1){
        perror("[ERROR] - Error sending request"); 
        exit(EXIT_FAILURE); 
    }

    if(close(sockfd) == -1){
        perror("[ERROR] - Error closing socket"); 
        exit(EXIT_FAILURE); 
    }
}
