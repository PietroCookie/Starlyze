#ifndef __NETWORK_REQUEST_H__
#define __NETWORK_REQUEST_H__

#define MAX_MSG 255

// Type of request from client to server
#define FIRST_CONNEXION_SEND_PSEUDO 1

typedef union{
    char pseudo[MAX_MSG]; 
}content_request_t; 

typedef struct{
    int type_request; 
    content_request_t content; 
}request_client_udp; 

#endif  