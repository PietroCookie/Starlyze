/**
 * @file client.c
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manages the client
 * @version 0.1
 * @date 2023-03-29
 *
 * @copyright Copyright (c) 2023
 *
 */

// INCLUDES
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#include "client_utility.h"
#include "client_udp.h"
#include "network_request.h"

// Global variables
int port, sockfd;
char address_ip[15];
info_client_t info_client;

/**
 * @brief Function to handle the SIGINT signal
 *
 * @param signum
 */
void sigint_handler(int signum)
{
    printf("\n[STOP] - Client arrested !\n");
    send_request_to_client_disconnection(info_client, port, address_ip, sockfd);
    exit(0);
}

/**
 * @brief Main function
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[])
{
    char *pseudo;
    struct sigaction action;
    int id_client;

    // Specify handler
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_SIGINFO;
    action.sa_handler = sigint_handler;
    if (sigaction(SIGINT, &action, NULL) == -1)
    {
        perror("Error positionning handler");
        exit(EXIT_FAILURE);
    }


    // Check the number of arguments
    if (argc != 3)
    {
        fprintf(stderr, "[ERROR] - Use %s address port\n", argv[0]);
        fprintf(stderr, "[HELP]  - Where : \n");
        fprintf(stderr, "\t   - address : IPv4 address of the server\n");
        fprintf(stderr, "\t   - port : the server port\n");
        exit(EXIT_FAILURE);
    }

    // Create socket UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        perror("[ERROR] - Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Copy argv[1] to address_ip
    if (strcpy(address_ip, argv[1]) == 0)
    {
        perror("[ERROR] - Error copying argv[1] to address_ip");
        exit(EXIT_FAILURE);
    }
    port = atoi(argv[2]);

    display_logo_app();

    if ((pseudo = malloc(MAX_MSG * sizeof(char))) == NULL)
    {
        perror("[ERROR] - Memory allocation pseudo failed");
        exit(EXIT_FAILURE);
    }

    pseudo = pseudo_entry();
    id_client = send_pseudo_to_server(pseudo, port, address_ip, sockfd);

    info_client.id = id_client;
    strcpy(info_client.pseudo, pseudo);

    int nb_clients = receive_response_nb_clients(port, address_ip, sockfd);

    display_menu(nb_clients);
    handler_menu(port, address_ip, info_client, sockfd);

    if(close(sockfd) == -1)
    {
        perror("[ERROR] - Error closing socket");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}