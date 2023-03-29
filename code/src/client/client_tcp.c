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
#include <locale.h>
#include <pthread.h>


#include "client_tcp.h"
#include "functions.h"
#include "client-game.h"
#include "interface_game.h"


/**
 * @brief Connect to the server with TCP
 * 
 * @param port 
 * @param address_ip 
 */
void connect_to_server_with_tcp(int port, char address_ip[15]){
    printf("[INFO] - Connecting to the server with TCP\n"); 

    int socket_fd;
	pthread_t thread;
	client_game_infos_thread_t client_infos;
	int quit = 0;
	char ch;


	socket_fd = connection_game(address_ip, port);


	setlocale(LC_ALL, "");
	ncurses_init();
	ncurses_init_mouse();
	ncurses_colors();
	palette();
	clear();
	refresh();

	client_infos.socket_client = &socket_fd;
	client_infos.interface = interface_game_create();
    
	if(pthread_create(&thread, NULL, thread_display, &client_infos) != 0) {
		fprintf(stderr, "Error create thread display\n");
	}


	while (quit == 0)
	{
		ch = getch();
		if(ch == 'n' || ch =='N')
			quit = 1;
		else {
			if(write(socket_fd, &ch, sizeof(char)) == -1) {
				perror("Error sending value");
				quit = 1;
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
    if(close(socket_fd) == -1) {
        perror("Error closing socket");
    }

	ncurses_stop();
	interface_game_delete(&client_infos.interface);

}
