/**
 * @file client_tcp.h
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manages the TCP client
 * @version 0.1
 * @date 2023-03-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __CLIENT_TCP_H__
#define __CLIENT_TCP_H__

/**
 * @brief Connect to the server with TCP
 * 
 * @param port 
 * @param address_ip 
 */
void connect_to_server_with_tcp(int port, char address_ip[15]); 

#endif