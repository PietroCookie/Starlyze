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
        perror("[ERROR] - Error creating socket");
        exit(EXIT_FAILURE);
    }
    
    // Fill the address structure
    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if(inet_pton(AF_INET, address, &addr.sin_addr.s_addr) != 1) {
        perror("[ERROR] - Error converting address");
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
	// char *message_receive = "";
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

		if(request_receive.type_request == FREEZE_PLAYER) {
			((client_game_infos_thread_t*)arg)->freeze = request_receive.second_freeze;
		}
		else if(request_receive.type_request == END_GAME) {
			window_printw(interface->win_message, request_receive.message);
			window_printw_col(interface->win_message, RED, "Press n to quit\n");
			window_refresh(interface->win_message);
			quit = 1;
			((client_game_infos_thread_t*)arg)->end_game = 1;
		}
		
		if(request_receive.type_request != END_GAME) {
			refresh_win_level_game(interface, request_receive.level_display);
			refresh_win_infos(interface, request_receive.player);
		}

		// nanosleep(&time_wait, NULL);
	}
	

	pthread_exit(NULL);
}
