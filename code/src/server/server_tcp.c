/**
 * @file server_tcp.c
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manages the TCP server
 * @version 0.1
 * @date 2023-03-29
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
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

#include "server_tcp.h"
#include "server_udp.h"
#include "function.h"
#include "game_control.h"

/**
 * @brief Create a socket tcp object
 *
 * @param port
 * @param game
 * @param sockfd
 */
void create_socket_tcp(int port, game_t *game, int sockfd)
{
    int socket_game, n;
    struct sockaddr_in address;
    socklen_t size_address = sizeof(struct sockaddr_in);

	// Create socket
    if((socket_game = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        perror("[ERROR] - Error creating socket");
        exit(EXIT_FAILURE);
    }

	// Fill server address
    memset(&address, 0, sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = 0;


    // Name socket
    if(bind(socket_game, (struct sockaddr*)&address, sizeof(struct sockaddr_in)) == -1) {
        perror("[ERROR] - Error naming socket");
        exit(EXIT_FAILURE);
    }

	// Switch the socket in passive mode
    if(listen(socket_game, 1) == -1) {
        perror("[ERROR] - Error switching socket in passive mod");
        exit(EXIT_FAILURE);
    }

	size_address = sizeof(address);
	if(getsockname(socket_game, (struct sockaddr*)&address, &size_address) == -1){
		perror("[ERROR] - Error getsockname socket");
		exit(EXIT_FAILURE);
	}

	
	printf("[INFO][%s] - TCP socket created on port %d in son no. 15\n", get_timestamp(), ntohs(address.sin_port));
	send_tcp_socket(port, ntohs(address.sin_port), game, sockfd);


    if((n=fork()) == 0){
        game_control(game->nb_participants_final, socket_game, game->name_world);

		exit(EXIT_SUCCESS);
    }


}