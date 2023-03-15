#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

#include "interface_client.h"
#include "functions.h"
#include "colors.h"

int main(int argc, char *argv[]){
    int ch; 
    interface_client_t* interface; 
    bool quit = FALSE;

    // Check the number of arguments
    if(argc != 3){
        fprintf(stderr, "[ERROR] - Use %s address port\n",argv[0]); 
        fprintf(stderr, "[HELP]  - Where : \n"); 
        fprintf(stderr, "\t   - address : IPv4 address of the server\n"); 
        fprintf(stderr, "\t   - port : the server port\n"); 
        exit(EXIT_FAILURE);
    }

    // Ncurses initialisation
    setlocale(LC_ALL, ""); 
    ncurses_init(); 
    ncurses_init_mouse(); 
    ncurses_colors(); 
    palette(); 
    clear(); 
    refresh(); 

    interface = interface_create_client(); 

    // Main loop
    while(quit == FALSE){
        ch=getch(); 
        if((ch=='Q') || (ch=='q')){
            quit = TRUE; 
        }else{
            interface_actions_client(interface, ch); 
        }
    }

    // Stop ncurses
    ncurses_stop(); 
    interface_delete_client(&interface); 
    return EXIT_SUCCESS; 
}