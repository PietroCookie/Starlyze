#ifndef __NETWORK_REQUEST_H__
#define __NETWORK_REQUEST_H__

#define MAX_MSG 255

// Type of request for client
#define CLIENT_FIRST_CONNEXION_SEND_PSEUDO 1
#define CLIENT_NB_CLIENTS 2

// Type of response for server
#define SERVER_SEND_NB_CLIENTS 1

typedef union{
    char pseudo[MAX_MSG]; 
}content_request_client_udp_t; 

typedef struct{
    int type_request; 
    content_request_client_udp_t content; 
}request_client_udp_t; 

typedef union{
    int nb_clients; 
}content_response_server_t;

typedef struct{
    int type_request;
    content_response_server_t content; 
}response_server_udp_t; 





#endif  