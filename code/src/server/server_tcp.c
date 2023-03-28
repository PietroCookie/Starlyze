#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

#include "server_tcp.h"
#include "server_udp.h"
#include "function.h"


void create_socket_tcp(int port, game_t* game, int sockfd){
    int fd;
    struct sockaddr_in address; 
    socklen_t address_length = sizeof(struct sockaddr_in); 

    // Create socket
    if((fd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))==-1){
        perror("[ERROR] - Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Fill server address
    memset(&address, 0, sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(0); 

    // Bind socket
    if (bind(fd, (struct sockaddr*)&address, sizeof(struct sockaddr_in)) == -1) {
        perror("[ERROR] - Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Get socket name
    if(getsockname(fd, (struct sockaddr*)&address, &address_length)==-1){
        perror("[ERROR] - Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Display port
    printf("[INFO][%s] - Port TCP used: %d\n", get_timestamp(), ntohs(address.sin_port));

    if(close(fd)==-1){
        perror("[ERROR] - Error closing socket");
        exit(EXIT_FAILURE);
    }

    send_tcp_socket(port, ntohs(address.sin_port), game, sockfd);
}