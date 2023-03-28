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
#include "function.h"

int stop=0; 


void handler(int signum){
    printf("\n[INFO][SIGNAL][%s]  - Stop request received by signal\n", get_timestamp()); 
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
    list_info_client_t* connected_clients; 
    list_world_response_t list_world; 
    // info_client_t* actual_user;
    list_game_t* list_game; 

    // Initialise the list of clients and list of games
    list_game = init_list_game(nb_games); 
    connected_clients = malloc(sizeof(list_info_client_t));
    init_list_info_client(connected_clients);

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
        fprintf(stderr, "[ERROR][%s] - Use %s port\n",get_timestamp(), argv[0]); 
        exit(EXIT_FAILURE); 
    }

    // Create socket
    if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1){
        perror("[ERROR]- Error creating socket\n"); 
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

    // Get socket name
    if(getsockname(sockfd, (struct sockaddr*)&server_address, &address_length)==-1){
        perror("[ERROR] - Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Display adress IP and port
    printf("------------------ I N F O R M A T I O N S ------------------\n"); 
    printf("Server IP address : %s\n", inet_ntoa(server_address.sin_addr));
    printf("Server started on port %s\n", argv[1]);
    printf("-------------------------------------------------------------\n\n");

    // Wait for client requests
    printf("================================ L O G S ================================ \n"); 
    printf("[INFO][START][%s]    - Wait for a request [CTRL + C to stop]\n", get_timestamp()); 

    while(stop==0){
        
        // Read a request received 
        if(recvfrom(sockfd, &request_received, sizeof(request_client_udp_t), 0,
                    (struct sockaddr*)&client_address, &address_length)==-1){
            if(errno!=EINTR){
                perror("[ERROR]- Error receiving message"); 
                exit(EXIT_FAILURE); 
            }
        }

        type_request_received = request_received.type_request; 

        switch(type_request_received){
            case CLIENT_FIRST_CONNEXION_SEND_PSEUDO :
                printf("[INFO][REQUEST][%s]  - New client connected with pseudo \"%s\"\n", get_timestamp(), request_received.content.pseudo);
                int port_client = ntohs(client_address.sin_port);
                nb_client++; 
                
                response.type_request = SERVER_SEND_ID_CLIENTS; 
                response.content.id_clients = nb_client; 
                inet_ntop(AF_INET, &(client_address.sin_addr), client_address_str, INET_ADDRSTRLEN);

                save_new_client(connected_clients, request_received.content.pseudo, client_address_str, 
                                nb_client, port_client); 
                
                if(sendto(sockfd, &response, sizeof(response_server_udp_t), 0, 
                        (struct sockaddr*)&client_address, address_length)==-1){
                    perror("[ERROR] - Error sending response");
                    exit(EXIT_FAILURE);
                }else{
                    printf("[INFO][RESPONSE][%s] - Response id client sent to client n°%d\n", get_timestamp(), nb_client);
                }
                break; 

            case CLIENT_NB_CLIENTS:
                printf("[INFO][REQUEST][%s]  - Client ask for number of clients connected\n", get_timestamp());
                response.type_request = SERVER_SEND_NB_CLIENTS; 
                response.content.nb_clients = connected_clients->nb_clients;
                if(sendto(sockfd, &response, sizeof(response_server_udp_t), 0,
                        (struct sockaddr*)&client_address, address_length) == -1) {
                    perror("[ERROR] - Error sending response");
                    exit(EXIT_FAILURE);
                }else{
                    printf("[INFO][RESPONSE][%s] - Number of client sent to client\n", get_timestamp());
                }
                break;
            
            case CLIENT_DISCONNECTION: 
                printf("[INFO][REQUEST][%s]  - Client n°%d disconnected\n", get_timestamp(), request_received.content.id_client);
                info_client_t* client_to_delete = search_client(connected_clients, request_received.content.id_client);
                delete_client(connected_clients, client_to_delete);
                break; 

            case CLIENT_RECOVERING_LIST_WORLDS: 
                printf("[INFO][REQUEST][%s]  - Client ask for list of worlds\n", get_timestamp());
                list_world = recovering_existing_worlds();
                response.content.list_world.nb_world = list_world.nb_world;
                for(int i=0; i<list_world.nb_world; i++){
                    strcpy(response.content.list_world.name_world[i], list_world.name_world[i]); 
                }
                if(sendto(sockfd, &response, sizeof(response_server_udp_t), 0,
                        (struct sockaddr*)&client_address, address_length) == -1) {
                    perror("[ERROR]- Error sending response");
                    exit(EXIT_FAILURE);
                }else{
                    printf("[INFO][RESPONSE][%s] - List of worlds sent to client\n", get_timestamp());
                }
                break;
 
            case CLIENT_START_GAMES: 
                printf("[INFO][REQUEST][%s]  - Client n°%d start a new game with world \"%s\" and with %d max players\n", 
                        get_timestamp(), request_received.content.settings_game[2], list_world.name_world[request_received.content.settings_game[0]],
                        request_received.content.settings_game[1]);
                nb_games++; 
                int id = request_received.content.settings_game[2];
                char pseudo[255], client_address_start_games[255]; 
                info_client_t* client_search =  search_client(connected_clients, id);  
                printf("Port du client : %d\n", client_search->port);
                strcpy(pseudo, client_search->pseudo);
                strcpy(client_address_start_games, client_search->client_address);

                // actual_user = init_info_client(id, pseudo, client_address_start_games, ntohs(client_address.sin_port));
                save_new_game(list_game, nb_games, request_received.content.settings_game[1], 
                                list_world.name_world[request_received.content.settings_game[0]], client_search);
                printf("[INFO][MAIN][%s] - Game n°%d started\n", get_timestamp(), nb_games);
                break; 

            case CLIENT_SEND_LIST_GAME: 
                printf("[INFO][REQUEST][%s]  - Client ask for list of games\n", get_timestamp());
                if(list_game->nb_games == 0){
                    response.type_request = SERVER_SEND_NO_GAMES; 
                    if(sendto(sockfd, &response, sizeof(response_server_udp_t), 0,
                        (struct sockaddr*)&client_address, address_length) == -1) {
                        perror("[ERROR] - Error sending response");
                        exit(EXIT_FAILURE);
                    }else{
                        printf("[INFO][RESPONSE][%s] - No games available\n", get_timestamp());
                    }
                }else{
                    response.type_request = SERVER_SEND_LIST_GAMES;
                    response.content.list_game = convert_struct_game_to_game_without_players(list_game);
                    if(sendto(sockfd, &response, sizeof(response_server_udp_t), 0,
                            (struct sockaddr*)&client_address, address_length) == -1) {
                        perror("[ERROR] - Error sending response");
                        exit(EXIT_FAILURE);
                    }else{
                        printf("[INFO][RESPONSE][%s] - List of games sent to client\n", get_timestamp());
                    }
                }
                break;

            case CLIENT_JOIN_GAME: 
                printf("[INFO][REQUEST][%s]  - Client n°%d join game n°%d\n", get_timestamp(), request_received.content.choice_game[1], request_received.content.choice_game[0]); 
                info_client_t* client_search_join = search_client(connected_clients, request_received.content.choice_game[1]);
                add_client_at_game(list_game, request_received.content.choice_game[0], client_search_join, atoi(argv[1]), sockfd);
                break;
        }
    }

    // Close socket
    if(close(sockfd) == -1){
        perror("[ERROR] - Error closing socket"); 
        exit(EXIT_FAILURE); 
    }

    delete_list(connected_clients);
    delete_list_game(list_game);

    printf("[INFO][%s] - Server : Down\n", get_timestamp()); 
    printf("========================================================================= \n"); 

    return EXIT_SUCCESS; 

}