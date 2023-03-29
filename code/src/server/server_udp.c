/**
 * @file server_udp.c
 * @author HADID Hocine
 * @brief File that manages the UDP server
 * @version 0.1
 * @date 2023-03-29
 *
 * @copyright Copyright (c) 2023
 *
 */
// INCLUDES
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "network_request.h"
#include "server_udp.h"
#include "server_tcp.h"
#include "info_client.h"
#include "function.h"

/**
 * @brief Function to save a new client
 *
 * @param connected_clients
 * @param pseudo
 * @param client_address
 * @param nb_client
 * @param port
 */
void save_new_client(list_info_client_t *connected_clients, char pseudo[MAX_MSG], char *client_address,
                     int nb_client, int port)
{
    info_client_t *new_client = init_info_client(nb_client, pseudo, client_address, port);
    add_client(connected_clients, new_client);
}

/**
 * @brief Function to add a client to a game specified by its id
 *
 * @param list_game
 * @param id_game
 * @param client_to_join
 * @param port
 * @param sockfd
 */
void add_client_at_game(list_game_t *list_game, int id_game, info_client_t *client_to_join, int port, int sockfd)
{
    game_t *game = search_game(list_game, id_game);
    add_client(game->list_players, client_to_join);
    game->nb_participants_actual++;
    if (game->nb_participants_final == game->nb_participants_actual)
    {
        printf("[INFO][%s] - Game n°%d is full\n", get_timestamp(), id_game);
        create_socket_tcp(port, game, sockfd);
    }
}

/**
 * @brief Function to send a message with TCP Port to a client
 *
 * @param port
 * @param port_tcp
 * @param game
 * @param sockfd
 */
void send_tcp_socket(int port, int port_tcp, game_t *game, int sockfd)
{
    struct sockaddr_in address;
    response_server_udp_t response;
    char client_address_str[INET_ADDRSTRLEN];
    info_client_t *current = game->list_players->head;
    socklen_t address_length = sizeof(struct sockaddr_in);

    while (current != NULL)
    {
        // Fill server address
        memset(&address, 0, sizeof(address));
        address.sin_family = AF_INET;
        address.sin_port = htons(current->port);
        if (inet_pton(AF_INET, current->client_address, &address.sin_addr) != 1)
        {
            perror("Error converting address");
            exit(EXIT_FAILURE);
        }

        response.content.port_tcp = port_tcp;

        if (sendto(sockfd, &response, sizeof(response_server_udp_t), 0,
                   (struct sockaddr *)&address, address_length) == -1)
        {
            perror("[ERROR] - Error sending request");
            exit(EXIT_FAILURE);
        }
        else
        {
            // Display IP Adress
            inet_ntop(AF_INET, &address.sin_addr, client_address_str, INET_ADDRSTRLEN);
            printf("[INFO][REQUEST][%s] - Send TCP port to IP address %s to port %d\n", get_timestamp(),
                   client_address_str, address.sin_port);
        }
        current = current->next;
    }
}
