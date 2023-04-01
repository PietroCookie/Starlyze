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
	pthread_t thread;
	client_game_infos_thread_t client_infos;
	char address[25];
	int quit = 0;
	char ch;

	
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

	strcpy(address, argv[1]);

	socket_client = connection_game(address, atoi(argv[2]));
	client_infos.socket_client = &socket_client;
	client_infos.interface = interface_game_create();
	client_infos.freeze = 0;
	client_infos.end_game = 0;

    
	if(pthread_create(&thread, NULL, thread_display, &client_infos) != 0) {
		fprintf(stderr, "Error create thread display\n");
	}


	while (quit == 0)
	{
		ch = getch();
		if(ch == 'n' || ch =='N')
			quit = 1;
		else {
			if(client_infos.end_game == 0) {
				if(client_infos.freeze == 0) {
					if(write(socket_client, &ch, sizeof(char)) == -1) {
						perror("Error sending value");
						quit = 1;
					}
				}
				else {
					sleep(client_infos.freeze);
					client_infos.freeze = 0;
				}
			}
		}
	}

	if(pthread_cancel(thread) != 0) {
		fprintf(stderr, "Error cancel thread display\n");
	}

	if(pthread_join(thread, NULL) != 0) {
		fprintf(stderr, "Error join thread display\n");
	}

    // Close the socket
    if(close(socket_client) == -1) {
        perror("Error closing socket");
    }

	ncurses_stop();
	interface_game_delete(&client_infos.interface);

	return EXIT_SUCCESS;
}
