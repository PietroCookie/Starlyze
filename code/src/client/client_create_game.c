#include "client_create_game.h"
#include "network_request.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

list_world_response_t receive_list_world(int port, char address_ip[15]){
    int sockfd, stop=0; 
    struct sockaddr_in address; 
    request_client_udp_t request; 
    response_server_udp_t response; 

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
    request.type_request = CLIENT_RECOVERING_LIST_WORLDS; 

    while(stop==0){
        if(sendto(sockfd, &request, sizeof(request_client_udp_t), 0, 
            (struct sockaddr*)&address,sizeof(struct sockaddr_in))==-1){
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

    if(close(sockfd) == -1){
        perror("[ERROR] - Error closing socket"); 
        exit(EXIT_FAILURE); 
    }

    return response.content.list_world; 
}
