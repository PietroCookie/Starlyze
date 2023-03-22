#ifndef __NETWORK_UDP_H__
#define __NETWORK_UDP_H__

void send_pseudo_to_server(char *pseudo, int port, char address_ip[15]); 

int receive_nb_clients(int port, char address[15]); 
#endif