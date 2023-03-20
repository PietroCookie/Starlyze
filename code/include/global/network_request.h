#ifndef __NETWORK_REQUEST_H__
#define __NETWORK_REQUEST_H__

#define MAX_MSG 255

// Type of request from client to server
#define FIRST_CONNEXION_PSEUDO 1

typedef struct{
    int id_request; 
}request_init_communication_t; 

typedef struct{
    int id;
    char pseudo[MAX_MSG]; 
}request_first_connexion_t; 

#endif  