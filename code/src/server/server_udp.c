#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "network_request.h"
#include "network_udp.h"

void receive_request_first_connexion(int port){
    int sockfd; 
    struct sockaddr_in server_address, client_address; 
    socklen_t address_length = sizeof(struct sockaddr_in); 
    receive_request_first_connexion request_received; 
    struct sigaction action; 

    // Create socket UDP
    if((sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))==-1){
        perror("[ERROR] - Error creating socket\n"); 
        exit(EXIT_FAILURE); 
    }

    // Fill server address
    memset(&server_address, 0, sizeof(struct sockaddr_in)); 
    server_address.sin_family = AF_INET; 
    server_address.sin_port = htons(port); 
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); 

    // Name socket
    if(bind(sockfd, (struct sockaddr*)&server_address, sizeof(struct sockaddr_in))==-1){
        
    }
}