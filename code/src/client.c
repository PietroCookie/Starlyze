#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "client_utility.h"
#include "client_udp.h"
#include "network_request.h"

int main(int argc, char *argv[]){
    int port; 
    char address_ip[15], *pseudo;  

    // Check the number of arguments
    if(argc != 3){
        fprintf(stderr, "[ERROR] - Use %s address port\n",argv[0]); 
        fprintf(stderr, "[HELP]  - Where : \n"); 
        fprintf(stderr, "\t   - address : IPv4 address of the server\n"); 
        fprintf(stderr, "\t   - port : the server port\n"); 
        exit(EXIT_FAILURE);
    }

    // Copy argv[1] to address_ip
    if(strcpy(address_ip, argv[1]) == 0){
        perror("[ERROR] - Error copying argv[1] to address_ip"); 
        exit(EXIT_FAILURE); 
    }
    port = atoi(argv[2]);

    display_logo_app(); 

    if((pseudo=malloc(MAX_MSG*sizeof(char)))==NULL){
        perror("[ERROR] - Memory allocation pseudo failed"); 
        exit(EXIT_FAILURE); 
    } 

    pseudo = pseudo_entry(); 
    send_pseudo_to_server(pseudo, port, address_ip); 

    display_menu(3, port, address_ip); 
    handler_menu(3, port, address_ip); 

    return EXIT_SUCCESS; 
}