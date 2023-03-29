#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>

#include <pthread.h>

#include "functions.h"
#include "interface_game.h"

#include "client-game.h"

int main(int argc, char const *argv[])
{
	int socket_client;
	pthread_t thread[2];
	client_game_infos_thread_t client_infos;
	char address[25];

	strcpy(address, argv[1]);
	
    
    // Check arguments
    if(argc != 3) {
        fprintf(stderr, "Use: %s address port\n", argv[0]);
        fprintf(stderr, "Where:\n");
        fprintf(stderr, "  address: IPv4 address of the server\n");
        fprintf(stderr, "  port   : port of the server\n");
        exit(EXIT_FAILURE);
    }

	setlocale(LC_ALL, "");
	ncurses_init();
	ncurses_init_mouse();
	ncurses_colors();
	palette();
	clear();
	refresh();

	

	socket_client = connection_game(address, atoi(argv[2]));
	client_infos.socket_client = &socket_client;
	client_infos.interface = interface_game_create();
    
	if(pthread_create(&thread[0], NULL, thread_display, &client_infos) != 0) {
		fprintf(stderr, "Error create thread display\n");
	}

	client_infos.thread_display = &thread[0];

	if(pthread_create(&thread[1], NULL, thread_send, &client_infos) != 0) {
		fprintf(stderr, "Error create thread send");
	}


	if(pthread_join(thread[0], NULL) != 0) {
		fprintf(stderr, "Error join thread display\n");
	}

	if(pthread_join(thread[1], NULL) != 0) {
		fprintf(stderr, "Error join thread send\n");
	}

    // Close the socket
    if(close(socket_client) == -1) {
        perror("Error closing socket");
        exit(EXIT_FAILURE);
    }

	ncurses_stop();
	interface_game_delete(&client_infos.interface);

	return EXIT_FAILURE;
}
