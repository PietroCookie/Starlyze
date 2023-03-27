#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "network_request.h"
#include "server_udp.h"
#include "create_game.h"
#include "info_client.h"
#include "clients_connected.h"

int stop=0; 

void handler(int signum){
    printf("[INFO] - Stop request received by signal\n"); 
    stop = 1; 
}

int main(int argc, char *argv[]){
    int sockfd, type_request_received, nb_client=0, nb_games=0; 
    char client_address_str[INET_ADDRSTRLEN];
    struct sockaddr_in server_address, client_address; 
    socklen_t address_length = sizeof(struct sockaddr_in); 
    request_client_udp_t request_received; 
    response_server_udp_t response; 
    struct sigaction action; 
    list_connected_client* connected_clients; 
    list_world_response_t list_world; 
    info_client_t* actual_user;
    list_game_t* list_game; 

    // Initialise the list of clients and list of games
    list_game = init_list_game(nb_games); 
    connected_clients = init_list_connected_client(nb_client);

    // Specify handler
    sigemptyset(&action.sa_mask); 
    action.sa_flags = 0; 
    action.sa_handler = handler;
    if(sigaction(SIGINT, &action, NULL)==-1){
        perror("[ERROR] - Error positionning handler"); 
        exit(EXIT_FAILURE); 
    }

    // Check arguments 
    if(argc != 2){
        fprintf(stderr, "[ERROR] - Use %s port\n",argv[0]); 
        exit(EXIT_FAILURE); 
    }

    // Create socket
    if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        perror("[ERROR] - Error creating socket\n"); 
        exit(EXIT_FAILURE); 
    }

    // Fill server address
    memset(&server_address, 0, sizeof(struct sockaddr_in)); 
    server_address.sin_family = AF_INET; 
    server_address.sin_port = htons(atoi(argv[1])); 
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); 


    // Name socket
    if(bind(sockfd, (struct sockaddr*)&server_address, sizeof(struct sockaddr_in)) == -1){
        perror("[ERROR] - Error naming socket"); 
        exit(EXIT_FAILURE); 
    }

    // Wait for client requests
    printf("Wait for a request [CTRL + C to stop]\n"); 

    while(stop==0){
        
        // Read a request received 
        if(recvfrom(sockfd, &request_received, sizeof(request_client_udp_t), 0,
                    (struct sockaddr*)&client_address, &address_length)==-1){
            if(errno!=EINTR){
                perror("[ERROR] - Error receiving message"); 
                exit(EXIT_FAILURE); 
            }
        }

        type_request_received = request_received.type_request; 

        switch(type_request_received){
            case CLIENT_FIRST_CONNEXION_SEND_PSEUDO :
                nb_client++; 
                response.type_request = SERVER_SEND_ID_CLIENTS; 
                response.content.id_clients = nb_client; 
                inet_ntop(AF_INET, &(client_address.sin_addr), client_address_str, INET_ADDRSTRLEN);

                save_new_client(connected_clients, request_received.content.pseudo, client_address_str, nb_client); 
                
                if(sendto(sockfd, &response, sizeof(response_server_udp_t), 0, 
                        (struct sockaddr*)&client_address, address_length)==-1){
                    perror("[ERROR][SERVER] - Error sending response ici");
                    exit(EXIT_FAILURE);
                }
                break; 

            case CLIENT_NB_CLIENTS:
                response.type_request = SERVER_SEND_NB_CLIENTS; 
                response.content.nb_clients = nb_client;
                if(sendto(sockfd, &response, sizeof(response_server_udp_t), 0,
                        (struct sockaddr*)&client_address, address_length) == -1) {
                    perror("[ERROR][SERVER] - Error sending response");
                    exit(EXIT_FAILURE);
                }
                break;
            
            case CLIENT_DISCONNECTION: 
                printf("Type de requete reçu : %d | ", request_received.type_request);
                printf("ID Client a deconnecté : %d\n", request_received.content.id_client); 
                break; 

            case CLIENT_RECOVERING_LIST_WORLDS: 
                list_world = recovering_existing_worlds();
                response.content.list_world.nb_world = list_world.nb_world;
                for(int i=0; i<list_world.nb_world; i++){
                    strcpy(response.content.list_world.name_world[i], list_world.name_world[i]); 
                }
                if(sendto(sockfd, &response, sizeof(response_server_udp_t), 0,
                        (struct sockaddr*)&client_address, address_length) == -1) {
                    perror("[ERROR][SERVER] - Error sending response");
                    exit(EXIT_FAILURE);
                }else{
                    printf("Reponse liste des mondes envoyés !\n"); 
                }
                break;
 
            case CLIENT_START_GAMES: 
                nb_games++; 
                printf("[INFO] - Request received : START GAMES\n"); 

                int id = request_received.content.settings_game[2];
                char pseudo[255], client_address_start_games[255]; 
                info_client_t* client_search =  search_client_connected(connected_clients, request_received.content.settings_game[2]);  
                strcpy(pseudo, client_search->pseudo);
                strcpy(client_address_start_games, client_search->client_address);

                // Initialisation de l'utilisateur
                actual_user = init_info_client(id, pseudo, client_address_start_games);
                save_new_game(list_game, nb_games, request_received.content.settings_game[1], 
                                list_world.name_world[request_received.content.settings_game[0]], actual_user);
                break; 

            case CLIENT_SEND_LIST_GAME: 
                if(list_game->nb_games == 0){
                    response.type_request = SERVER_SEND_NO_GAMES; 
                    if(sendto(sockfd, &response, sizeof(response_server_udp_t), 0,
                        (struct sockaddr*)&client_address, address_length) == -1) {
                        perror("[ERROR][SERVER] - Error sending response");
                        exit(EXIT_FAILURE);
                    }
                }else{
                    response.type_request = SERVER_SEND_LIST_GAMES;
                    response.content.list_game = convert_struct_game_to_game_without_players(list_game);
                    if(sendto(sockfd, &response, sizeof(response_server_udp_t), 0,
                            (struct sockaddr*)&client_address, address_length) == -1) {
                        perror("[ERROR][SERVER] - Error sending response");
                        exit(EXIT_FAILURE);
                    }else{
                        printf("Requete envoyé avec succès\n");
                    }
                }
                break;

            case CLIENT_JOIN_GAME: 
                printf("Type de requete reçu : %d | ", request_received.type_request);
                printf("Client n°%d a rejoins le jeu n°%d\n", request_received.content.choice_game[1], request_received.content.choice_game[0]); 
                
                break;
        }
    }

    // Close socket
    if(close(sockfd) == -1){
        perror("Error closing socket"); 
        exit(EXIT_FAILURE); 
    }

    printf("[INFO] - Server : STOP\n"); 

    return EXIT_SUCCESS; 

}