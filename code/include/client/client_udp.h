/**
 * @file client_udp.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manages the UDP client
 * @version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __CLIENT_UDP_H__
#define __CLIENT_UDP_H__

#include "server_udp.h"

// Constants
#define MAX_MSG 255

/**
 * @brief Send the pseudo of the client to the server
 *
 * @param pseudo
 * @param port
 * @param address_ip
 * @param sockfd
 * @return int
 */
int send_pseudo_to_server(char *pseudo, int port, char address_ip[15], int sockfd);

/**
 * @brief Receive the number of clients connected to the server
 *
 * @param port
 * @param address
 * @param sockfd
 * @return int
 */
int receive_response_nb_clients(int port, char address[15], int sockfd);

/**
 * @brief Send the request for disconnection to the server
 *
 * @param info_client
 * @param port
 * @param address_ip
 * @param sockfd
 */
void send_request_to_client_disconnection(info_client_t info_client, int port, char address_ip[15], int sockfd);

/**
 * @brief Receive the port of the socket TCP server
 *
 * @param port
 * @param ip_server
 * @param sockfd
 */
void receive_port_tcp_of_server(int port, char ip_server[15], int sockfd);

#endif