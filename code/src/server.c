/**
 * @file server.c
 * @author HADID Hocine & CHEMIN Pierre
 * @brief 
 * @version 0.1
 * @date 2023-03-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

int stop = 0; 

void handler(int signum){
    int result; 

    if(signum == SIGINT){
        printf("\n[WARNING] - Stop request received !\n"); 
        stop = 1; 
    }

    // Wait for children and
    do{
        result = waitpid(-1, NULL, WNOHANG); 
    }while((result != -1) || (errno==EINTR)); 
}

int main(int argc, char *argv[]){
    int fd, sockclient, n; 
    struct sigaction action; 
    struct sockaddr_in address; 

    sigemptyset(&action.sa_mask); 
    action.sa_flags = 0; 
    action.sa_handler = handler; 

    if(sigaction(SIGCHLD, &action, NULL)==-1){
        perror("Error positioning handler");
        exit(EXIT_FAILURE);  
    }
    if(sigaction(SIGINT, &action, NULL)==-1){
        perror("Error positioning handler"); 
        exit(EXIT_FAILURE);
    }

    // Check the number of arguments 
    if(argc != 2){
        fprintf(stderr, "[ERROR] - Use %s port\n",argv[0]); 
        fprintf(stderr, "[HELP]  - Where : \n"); 
        fprintf(stderr, "\t   - port : the server port\n"); 
        exit(EXIT_FAILURE); 
    }

    // Create socket 
    if((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))== -1){
        perror("Error creating socket"); 
        exit(EXIT_FAILURE); 
    }

    // Fill server address
    memset(&address, 0, sizeof(struct sockaddr_in)); 
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = htonl(INADDR_ANY); 
    address.sin_port = htons(atoi(argv[1]));

    // Name socket
    if(bind(fd, (struct sockaddr*)&address, sizeof(struct sockaddr_in)) == -1){
        perror("Error naming socket"); 
        exit(EXIT_FAILURE); 
    }

    // Switch the socket in passive mode 
    if(listen(fd, 1) == -1){
        perror("Error switching socket in passive mode"); 
        exit(EXIT_FAILURE); 
    }

    while(stop == 0){
        // Wait for a connection of client 
        printf("[INFO] - Server : waiting for connection ...\n"); 
        if((sockclient = accept(fd, NULL, NULL)) == -1){
            if(errno != EINTR){
                perror("Error waiting connexion"); 
                exit(EXIT_FAILURE); 
            }
        }else{
            if((n=fork()) == -1){
                perror("Error creating child"); 
            }
            if(n==0){
                // Close socket
                if(close(fd) == -1){
                    perror("Error closing socket"); 
                    exit(EXIT_FAILURE); 
                }

                // Read value
                if(read(sockclient, &n, sizeof(int)) == -1){
                    perror("Error reading value"); 
                    exit(EXIT_FAILURE); 
                }
                printf("[INFO] - Server-child : value received '%d'\n",n); 

                // Send response
                n*=2; 
                if(write(sockclient, &n, sizeof(int))==-1){
                    perror("Error sending value"); 
                    exit(EXIT_FAILURE); 
                }
                printf("[INFO] - Server-child : Value sent '%d'\n", n); 

                // Close socket
                if(close(sockclient)==-1){
                    perror("Error closing socket"); 
                    exit(EXIT_FAILURE); 
                }

                printf("[INFO] - Server-child : DONE\n"); 
                exit(EXIT_SUCCESS); 
            }else{
                // Close socket 
                if(close(sockclient) == -1){
                    perror("Error closing socket"); 
                    exit(EXIT_FAILURE); 
                }
            }
        }
    }

    // Close socket
    if(close(fd)==-1){
        perror("Error closing socket"); 
        exit(EXIT_FAILURE); 
    }
    printf("[INFO] - Server done\n"); 
    return EXIT_SUCCESS;
}