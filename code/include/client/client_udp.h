#ifndef __NETWORK_UDP_H__
#define __NETWORK_UDP_H__

#define MAX_MSG 255
#include "server_udp.h"

int send_pseudo_to_server(char *pseudo, int port, char address_ip[15]); 
int receive_response_nb_clients(int port, char address[15]); 
void send_request_to_client_disconnection(info_client_t info_client, int port, char address_ip[15]); 
void receive_port_tcp_of_server(int port, char ip_server[15]); 

#endif