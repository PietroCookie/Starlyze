/**
 * @file client_udp.c
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manages the UDP client
 * @version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */

// INCLUDES
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include "client_udp.h"
#include "network_request.h"

/**
 * @brief Send the pseudo to the server
 *
 * @param pseudo
 * @param port
 * @param address_ip
 * @return int
 */
int send_pseudo_to_server(char *pseudo, int port, char address_ip[15])
{
    int sockfd, stop = 0;
    struct sockaddr_in address;
    request_client_udp_t request;
    response_server_udp_t response;

    // Create socket UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        perror("[ERROR] - Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Fill the address structure
    memset(&address, 0, sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if (inet_pton(AF_INET, address_ip, &address.sin_addr) != 1)
    {
        perror("[ERROR] - Error converting address");
        exit(EXIT_FAILURE);
    }

    // Send request
    request.type_request = CLIENT_FIRST_CONNEXION_SEND_PSEUDO;
    strcpy(request.content.pseudo, pseudo);

    while (stop == 0)
    {
        if (sendto(sockfd, &request, sizeof(request_client_udp_t), 0,
                   (struct sockaddr *)&address, sizeof(struct sockaddr_in)) == -1)
        {
            perror("[ERROR] - Error sending request");
            exit(EXIT_FAILURE);
        }

        if (recvfrom(sockfd, &response, sizeof(response_server_udp_t), 0, NULL, 0) == -1)
        {
            if (errno == EINTR)
            {
                perror("[ERROR] - Error receiving message");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            stop = 1;
        }
    }

    if (close(sockfd) == -1)
    {
        perror("[ERROR] - Error closing socket");
        exit(EXIT_FAILURE);
    }

    if (response.type_request == SERVER_SEND_ID_CLIENTS)
    {
        return response.content.id_clients;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief Send the request for disconnection to the server
 *
 * @param port
 * @param address_ip
 * @return int
 */
int receive_response_nb_clients(int port, char address_ip[15])
{
    int sockfd, stop = 0;
    struct sockaddr_in address;
    request_client_udp_t request;
    response_server_udp_t response;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Fill the address structure
    memset(&address, 0, sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if (inet_pton(AF_INET, address_ip, &address.sin_addr) != 1)
    {
        perror("Error converting address");
        exit(EXIT_FAILURE);
    }

    request.type_request = CLIENT_NB_CLIENTS;

    while (stop == 0)
    {
        if (sendto(sockfd, &request, sizeof(request_client_udp_t), 0,
                   (struct sockaddr *)&address, sizeof(struct sockaddr_in)) == -1)
        {
            perror("[ERROR] - Error sending request");
            exit(EXIT_FAILURE);
        }
        if (recvfrom(sockfd, &response, sizeof(response_server_udp_t), 0, NULL, 0) == -1)
        {
            if (errno == EINTR)
            {
                perror("[ERROR] - Error receiving message");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            stop = 1;
        }
    }

    if (close(sockfd) == -1)
    {
        perror("[ERROR] - Error closing socket");
    }

    return response.content.nb_clients;
}

/**
 * @brief Send the request for disconnection to the server
 *
 * @param info_client
 * @param port
 * @param address_ip
 */
void send_request_to_client_disconnection(info_client_t info_client, int port, char address_ip[15])
{
    int sockfd;
    struct sockaddr_in address;
    request_client_udp_t request;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Fill the address structure
    memset(&address, 0, sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if (inet_pton(AF_INET, address_ip, &address.sin_addr) != 1)
    {
        perror("Error converting address");
        exit(EXIT_FAILURE);
    }

    request.type_request = CLIENT_DISCONNECTION;
    request.content.id_client = info_client.id;

    // Send request
    if (sendto(sockfd, &request, sizeof(request_client_udp_t), 0,
               (struct sockaddr *)&address, sizeof(struct sockaddr_in)) == -1)
    {
        perror("[ERROR] - Error sending request");
        exit(EXIT_FAILURE);
    }

    if (close(sockfd) == -1)
    {
        perror("[ERROR] - Error closing socket");
    }
}

/**
 * @brief Receive the port of the socket TCP server
 *
 * @param port
 * @param ip_server
 */
void receive_port_tcp_of_server(int port, char ip_server[15])
{
    int sockfd;
    struct sockaddr_in address;
    response_server_udp_t response;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Fill the address structure
    memset(&address, 0, sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) != 1)
    {
        perror("Error converting address");
        exit(EXIT_FAILURE);
    }

    // Display address
    printf("[INFO] - Adresse IP du serveur : %s\n", inet_ntoa(address.sin_addr));
    printf("[INFO] - Port UDP du serveur : %d\n", ntohs(address.sin_port));

    printf("[INFO] - En attente de connexion du début de la partie ...\n");

    if (recvfrom(sockfd, &response, sizeof(response_server_udp_t), 0, NULL, 0) == -1)
    {
        if (errno == EINTR)
        {
            perror("[ERROR] - Error receiving message");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        // stop=1;
        printf("Requete reçu !\n");
    }

    printf("[INFO] - Port TCP : %d ", response.content.port_tcp);

    if (close(sockfd) == -1)
    {
        perror("[ERROR] - Error closing socket");
    }
}