#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#include "game_control.h"

int main(int argc, char const *argv[])
{
	int socket_game;
	pid_t game_pid;
	struct sockaddr_in address;
	socklen_t size_address;
	char name_address[INET_ADDRSTRLEN];


	// Create socket
    if((socket_game = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

	// Fill server address
    memset(&address, 0, sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = 0;


    // Name socket
    if(bind(socket_game, (struct sockaddr*)&address, sizeof(struct sockaddr_in)) == -1) {
        perror("Error naming socket");
        exit(EXIT_FAILURE);
    }

	// Switch the socket in passive mode
    if(listen(socket_game, 1) == -1) {
        perror("Error switching socket in passive mode");
        exit(EXIT_FAILURE);
    }

	size_address = sizeof(address);
	if(getsockname(socket_game, (struct sockaddr*)&address, &size_address) == -1){
		perror("Error getsockname");
		exit(EXIT_FAILURE);
	}
	printf("Server address : %s port : %d\n", inet_ntop(AF_INET, &address.sin_addr.s_addr, name_address, INET_ADDRSTRLEN), ntohs(address.sin_port));



	if((game_pid = fork()) == -1){
		perror("Error creating child process");
		exit(EXIT_FAILURE);
	}

	if(game_pid > 0) {
		if(wait(NULL) == -1) {
			perror("Error waiting child process");
			exit(EXIT_FAILURE);
		}

		// Close socket
		if(close(socket_game) == -1) {
			perror("Error closing socket");
			exit(EXIT_FAILURE);
		}

		printf("Server done.\n");
	}
	else {
		game_control(1, socket_game, "test");
	}

	return EXIT_SUCCESS;
}
