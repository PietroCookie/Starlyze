#ifndef __NETWORK_UDP_H__
#define __NETWORK_UDP_H__

void send_pseudo_to_server(char *pseudo, int port, char address_ip[15]); 

void send_id_to_init_communication(int port, char address_ip[15], int code_request); 

#endif