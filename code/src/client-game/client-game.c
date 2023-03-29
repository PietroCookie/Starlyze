#include "client-game.h"

#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#include "functions.h"
#include "interface_game.h"
#include "level_display.h"
#include "request_exchange.h"


int connection_game(char* address, int port){
	int socket_client;
	struct sockaddr_in addr;

	// Create socket
    if((socket_client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    
    // Fill the address structure
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if(inet_pton(AF_INET, address, &addr.sin_addr.s_addr) != 1) {
        perror("Error converting address");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if(connect(socket_client, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("Error connecting to the server");
        exit(EXIT_FAILURE);
    }

	return socket_client;
}


void *thread_display(void *arg) {
	int quit = 0;
	int socket_client = *((client_game_infos_thread_t*)arg)->socket_client ;
	interface_game_t *interface = ((client_game_infos_thread_t*)arg)->interface;
	request_send_player_t request_receive;
	// struct timespec time_wait;


	// time_wait.tv_sec = 0;
	// time_wait.tv_nsec = 100000000;


	while (quit == 0)
	{
		// Read the server response
		if(read(socket_client, &request_receive, sizeof(request_send_player_t)) == -1) {
			perror("Error reading response");
			quit = 1;
		}
		
		refresh_win_level_game(interface, request_receive.level_display);
		refresh_win_infos(interface, request_receive.player);

		// nanosleep(&time_wait, NULL);
	}
	

	pthread_exit(NULL);
}

void *thread_send(void *arg) {
	int quit = 0;
	char ch;
	int socket_client = *((client_game_infos_thread_t*)arg)->socket_client;
	pthread_t thread_display = *((client_game_infos_thread_t*)arg)->thread_display;


	while (quit == 0)
	{
		ch = getch();
		if(ch == 'n' || ch =='N')
			quit = 1;
		else {
			if(write(socket_client, &ch, sizeof(char)) == -1) {
				perror("Error sending value");
				quit = 1;
			}
		}
	}

	if(pthread_cancel(thread_display) != 0) {
		fprintf(stderr, "Error cancel thread display");
	}

	pthread_exit(NULL);
}

