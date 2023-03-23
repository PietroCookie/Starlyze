#include "client_create_game.h"
#include "network_request.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

list_world_response_t receive_list_world(int port, char address_ip[15]){
    int sockfd, stop=0; 
    struct sockaddr_in address; 
    request_client_udp_t request; 
    response_server_udp_t response; 

    // Create socket UDP
    if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        perror("[ERROR] - Error creating socket"); 
        exit(EXIT_FAILURE); 
    }

    // Fill the address structure
    memset(&address, 0, sizeof(struct sockaddr_in)); 
    address.sin_family = AF_INET; 
    address.sin_port = htons(port); 
    if(inet_pton(AF_INET, address_ip, &address.sin_addr) != 1){
        perror("[ERROR] - Error converting address"); 
        exit(EXIT_FAILURE); 
    }
    // Send request
    request.type_request = CLIENT_RECOVERING_LIST_WORLDS; 

    while(stop==0){
        if(sendto(sockfd, &request, sizeof(request_client_udp_t), 0, 
            (struct sockaddr*)&address,sizeof(struct sockaddr_in))==-1){
            perror("[ERROR] - Error sending request"); 
            exit(EXIT_FAILURE); 
        }

        if(recvfrom(sockfd, &response, sizeof(response_server_udp_t), 0, NULL, 0)==-1){
            if(errno == EINTR){
                perror("[ERROR] - Error receiving message"); 
                exit(EXIT_FAILURE); 
            }
        }else{
            stop=1;
        }
    }

    if(close(sockfd) == -1){
        perror("[ERROR] - Error closing socket"); 
        exit(EXIT_FAILURE); 
    }

    return response.content.list_world; 
}


void send_settings_game(int port, char address_ip[15], int choice_world, int nb_players_game, int id_client){
    int sockfd; 
    struct sockaddr_in address; 
    request_client_udp_t request; 

    // Create socket UDP
    if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        perror("[ERROR] - Error creating socket"); 
        exit(EXIT_FAILURE); 
    }

    // Fill the address structure
    memset(&address, 0, sizeof(struct sockaddr_in)); 
    address.sin_family = AF_INET; 
    address.sin_port = htons(port); 
    if(inet_pton(AF_INET, address_ip, &address.sin_addr) != 1){
        perror("[ERROR] - Error converting address"); 
        exit(EXIT_FAILURE); 
    }
    
    request.type_request = CLIENT_START_GAMES; 
    request.content.settings_game[0] = choice_world-1;
    request.content.settings_game[1] = nb_players_game; 
    request.content.settings_game[2] = id_client; 

    if(sendto(sockfd, &request, sizeof(request_client_udp_t), 0, 
        (struct sockaddr*)&address,sizeof(struct sockaddr_in))==-1){
        perror("[ERROR] - Error sending request"); 
        exit(EXIT_FAILURE); 
    }

    if(close(sockfd) == -1){
        perror("[ERROR] - Error closing socket"); 
        exit(EXIT_FAILURE); 
    }

}


int handler_create_game(list_world_response_t list_world, int port, char address_ip[15], int id_client){
    int choice_world = 0, nb_players_game=0; 
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>> Liste des mondes <<<<<<<<<<<<<<<<<<<<<<<<<<\n"); 
    for(int i=0; i<list_world.nb_world; i++){
        printf("%d°) %s \n", i+1, list_world.name_world[i]); 
    }
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n"); 

    while(choice_world<=0){
        printf("\n[Tapez %d pour retourner au menu]\n", list_world.nb_world+1); 
        printf("Veuillez choisir un monde parmi ceux proprosés (ou option du retour vers le menu) : "); 

        if(scanf("%d", &choice_world) == -1){
            perror("[ERROR] - Error when retrieving the choice\n"); 
            exit(EXIT_FAILURE); 
        }
    }

    while(nb_players_game<=0){
        printf("\n[Tapez 9999 pour retourner au menu]\n"); 
        printf("Veuillez indiquer le nombre de joueurs allant participé à la partie : "); 

        if(scanf("%d", &nb_players_game) == -1){
            perror("[ERROR] - Error when retrieving the choice\n"); 
            exit(EXIT_FAILURE); 
        }
    }
    
    if(choice_world > list_world.nb_world+1){
        return 0;
    }else{
        send_settings_game(port, address_ip, choice_world, nb_players_game, id_client); 
        return choice_world; 
    }    
}