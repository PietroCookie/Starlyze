/**
 * @file client_tcp.c
 * @author HADID Hocine & CHEMIN Pierre
 * @brief Files that manages the TCP client
 * @version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */

// INCLUDES
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "client_tcp.h"
#include "function.h"

/**
 * @brief Connect to the server with TCP
 * 
 * @param port 
 * @param address_ip 
 */
void connect_to_server_with_tcp(int port, char address_ip[15]){
    printf("[INFO] - Connecting to the server with TCP\n"); 

    int socket_fd;
    struct sockaddr_in address;

    // Create socket
    if((socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1){
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

    // Connect to the server
    if(connect(socket_fd, (struct sockaddr *)&address, sizeof(address)) == -1){
        perror("[ERROR] - Error connecting to the server");
        exit(EXIT_FAILURE);
    }
}
