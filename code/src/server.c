#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "network_request.h"

int stop=0; 

void handler(int signum){
    printf("[INFO] - Stop request received by signal\n"); 
    stop = 1; 
}

int main(int argc, char *argv[]){
    int sockfd, id_request_received; 
    struct sockaddr_in server_address, client_address; 
    socklen_t address_length = sizeof(struct sockaddr_in); 
    request_init_communication_t request_received; 
    struct sigaction action; 
    
    // Specify handler
    sigemptyset(&action.sa_mask); 
    action.sa_flags = 0; 
    action.sa_handler = handler;
    if(sigaction(SIGINT, &action, NULL)==-1){
        perror("[ERROR] - Error positionning handler"); 
        exit(EXIT_FAILURE); 
    }

    // Check arguments 
    if(argc != 2){
        fprintf(stderr, "[ERROR] - Use %s port\n",argv[0]); 
        exit(EXIT_FAILURE); 
    }

    // Create socket
    if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        perror("[ERROR] - Error creating socket\n"); 
        exit(EXIT_FAILURE); 
    }

    // Fill server address
    memset(&server_address, 0, sizeof(struct sockaddr_in)); 
    server_address.sin_family = AF_INET; 
    server_address.sin_port = htons(atoi(argv[1])); 
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); 


    // Name socket
    if(bind(sockfd, (struct sockaddr*)&server_address, sizeof(struct sockaddr_in)) == -1){
        perror("[ERROR] - Error naming socket"); 
        exit(EXIT_FAILURE); 
    }

    // Wait for client requests
    while(stop==0){
        printf("Wait for a request [CTRL + C to stop]\n"); 
        
        // Read a request received 
        if(recvfrom(sockfd, &request_received, sizeof(request_init_communication_t), 0,
                    (struct sockaddr*)&client_address, &address_length)==-1){
            if(errno!=EINTR){
                perror("[ERROR] - Error receiving message"); 
                exit(EXIT_FAILURE); 
            }
        }

        id_request_received = request_received.id_request; 
        switch(id_request_received){
            case FIRST_CONNEXION_PSEUDO :
                receive_request_first_connexion(); 
                break; 
        }
    }



    // Close socket
    if(close(sockfd) == -1){
        perror("Error closing socket"); 
        exit(EXIT_FAILURE); 
    }

    printf("[INFO] - Server : STOP\n"); 

    return EXIT_SUCCESS; 

}