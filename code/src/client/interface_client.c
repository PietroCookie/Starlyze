#include "interface_client.h"
#include "new_games.h"

#include "functions.h"
#include "colors.h"
#include <string.h>
#include <unistd.h>


void interface_dimensions_client(unsigned short width, unsigned short height) {
    if((COLS < width) || (LINES < height)) {
        ncurses_stop();
        fprintf(stderr, "Terminal size is too small: actually w=%d,h=%d instead of l=%d,h=%d\n",
                COLS, LINES, width, height);
        exit(EXIT_FAILURE);
    } 
}

interface_client_t* interface_create_client(){
    interface_client_t* result; 
    interface_dimensions_client(DEFAULT_WIDTH_INTERFACE_CLIENT+10, 27);
	
	if((result = malloc(sizeof(interface_client_t))) == NULL){
		ncurses_stop();
		perror("Error allocating structure interface_client_t");
		exit(EXIT_FAILURE);
	}

    result->win_main = window_create(0,0, DEFAULT_WIDTH_INTERFACE_CLIENT, DEFAULT_HEIGHT_INTERFACE_CLIENT, "STARLYZE", FALSE); 
    interface_print_logo(result); 
    interface_display_menu(result); 
    window_refresh(result->win_main); 

    result->win_infos = window_create(0,22,DEFAULT_WIDTH_INTERFACE_CLIENT,5, "Informations", TRUE); 
    window_printw_col(result->win_infos, RED, "Press 'Q' to exit"); 
    window_refresh(result->win_infos);

    return result;
}

void interface_actions_client(interface_client_t* interface, int c){
    int mouseX, mouseY; 
    int posX_item = (DEFAULT_WIDTH_INTERFACE_CLIENT/2)-((int)47/2);


    if((c==KEY_MOUSE) && (mouse_getpos(&mouseX, &mouseY) == OK)){
        window_printw(interface->win_infos, "\nClick (%d,%d)", mouseX, mouseY);
        window_refresh(interface->win_infos);

        if((mouseX >= 29 && mouseX<=71) && mouseY==12){ // Number of players
            interface_delete_menu(interface); 
            window_mvprintw_col(interface->win_main, 9, posX_item+2, WHITE, "<< Nombre de joueur(s) connecte(s) : 2 >>"); 
            window_mvprintw_col(interface->win_main, 19, 0, WHITE, "<- Retour"); 
            window_refresh(interface->win_main);
        }else if((mouseX >= 29 && mouseX<=64) && mouseY == 14){ // Create a game
            interface_delete_menu(interface); 
            window_mvprintw_col(interface->win_main, 9, posX_item+2, WHITE, "<< Creer une partie de starlyze >>"); 
            window_mvprintw_col(interface->win_main, 19, 0, WHITE, "<- Retour"); 
            window_refresh(interface->win_main);
            handler_new_games(interface);
        }else if((mouseX>=29 && mouseX<=67) && mouseY==16){ // Join a game
            interface_delete_menu(interface); 
            window_mvprintw_col(interface->win_main, 9, posX_item+2, WHITE, "<< Rejoindre partie en attente : 3 >>"); 
            window_mvprintw_col(interface->win_main, 19, 0, WHITE, "<- Retour"); 
            window_refresh(interface->win_main); 
        }else if((mouseX>=29 && mouseX<=60) && mouseY==18){ // Quit game
            ncurses_stop(); 
            interface_delete_client(&interface); 
            exit(EXIT_SUCCESS); 
        }else if((mouseX>=0 && mouseX<=10) && mouseY==20){
            interface_delete_menu(interface); 
            interface_display_menu(interface); 
            window_refresh(interface->win_main); 
        }
    } 
}

void interface_delete_client(interface_client_t **interface){
    window_delete(&(*interface)->win_main); 
    window_delete(&(*interface)->win_infos); 
    free(*interface); 
    interface = NULL; 
}

void interface_print_logo(interface_client_t* result){
    // S
    window_mvprintw_col(result->win_main, 1, 8, WHITE, "/_/_/_/"); 
    window_mvprintw_col(result->win_main, 2, 6, WHITE, "/_/"); 
    window_mvprintw_col(result->win_main, 3, 7, WHITE, "/_/_/"); 
    window_mvprintw_col(result->win_main, 4, 10, WHITE, "/_/"); 
    window_mvprintw_col(result->win_main, 5, 5, WHITE, "/_/_/_/");
    // T
    window_mvprintw_col(result->win_main, 1, 16, WHITE, "/_/_/_/_/_/"); 
    window_mvprintw_col(result->win_main, 2, 19, WHITE, "/_/"); 
    window_mvprintw_col(result->win_main, 3, 18, WHITE, "/_/"); 
    window_mvprintw_col(result->win_main, 4, 17, WHITE, "/_/"); 
    window_mvprintw_col(result->win_main, 5, 16, WHITE, "/_/"); 
    // A
    window_mvprintw_col(result->win_main, 1, 30, WHITE, "/_/_/"); 
    window_mvprintw_col(result->win_main, 2, 27, WHITE, "/_/    /_/"); 
    window_mvprintw_col(result->win_main, 3, 26, WHITE, "/_/_/_/_/"); 
    window_mvprintw_col(result->win_main, 4, 25, WHITE, "/_/    /_/"); 
    window_mvprintw_col(result->win_main, 5, 24, WHITE, "/_/    /_/"); 
    // R
    window_mvprintw_col(result->win_main, 1, 40, WHITE, "/_/_/_/"); 
    window_mvprintw_col(result->win_main, 2, 39, WHITE, "/_/    /_/"); 
    window_mvprintw_col(result->win_main, 3, 38, WHITE, "/_/_/_/");
    window_mvprintw_col(result->win_main, 4, 37, WHITE, "/_/    /_/"); 
    window_mvprintw_col(result->win_main, 5, 36, WHITE, "/_/    /_/"); 
    // L
    window_mvprintw_col(result->win_main, 1, 52, WHITE, "/_/"); 
    window_mvprintw_col(result->win_main, 2, 51, WHITE, "/_/"); 
    window_mvprintw_col(result->win_main, 3, 50, WHITE, "/_/"); 
    window_mvprintw_col(result->win_main, 4, 49, WHITE, "/_/"); 
    window_mvprintw_col(result->win_main, 5, 48, WHITE, "/_/_/_/_/"); 
    // Y
    window_mvprintw_col(result->win_main, 1, 58, WHITE, "/_/      /_/"); 
    window_mvprintw_col(result->win_main, 2, 59, WHITE, "/_/  /_/"); 
    window_mvprintw_col(result->win_main, 3, 60, WHITE, "/_/"); 
    window_mvprintw_col(result->win_main, 4, 59, WHITE, "/_/"); 
    window_mvprintw_col(result->win_main, 5, 58, WHITE, "/_/"); 
    // Z
    window_mvprintw_col(result->win_main, 1, 71, WHITE, "/_/_/_/_/_/"); 
    window_mvprintw_col(result->win_main, 2, 75, WHITE, "/_/"); 
    window_mvprintw_col(result->win_main, 3, 73, WHITE, "/_/"); 
    window_mvprintw_col(result->win_main, 4, 71, WHITE, "/_/"); 
    window_mvprintw_col(result->win_main, 5, 68, WHITE, "/_/_/_/_/_/"); 
    // E 
    window_mvprintw_col(result->win_main, 1, 84, WHITE, "/_/_/_/_/"); 
    window_mvprintw_col(result->win_main, 2, 83, WHITE, "/_/"); 
    window_mvprintw_col(result->win_main, 3, 82, WHITE, "/_/_/_/"); 
    window_mvprintw_col(result->win_main, 4, 81, WHITE, "/_/"); 
    window_mvprintw_col(result->win_main, 5, 80, WHITE, "/_/_/_/_/");    
}


void interface_display_menu(interface_client_t* interface){
    int posX_item; 

    window_mvprintw_col(interface->win_main, 7, 0, WHITE, "=================================================================================================="); 

    posX_item = (DEFAULT_WIDTH_INTERFACE_CLIENT/2)-((int)strlen("-------------------- MENU --------------------")/2);
    window_mvprintw_col(interface->win_main, 9, posX_item, WHITE, "-------------------- MENU --------------------");  
    window_mvprintw_col(interface->win_main, 11, posX_item+2, WHITE, "<< Nombre de joueur(s) connecte(s) : 2 >>"); 
    window_mvprintw_col(interface->win_main, 13, posX_item+2, WHITE, "<< Creer une partie de starlyze >>"); 
    window_mvprintw_col(interface->win_main, 15, posX_item+2, WHITE, "<< Rejoindre partie en attente : 3 >>"); 
    window_mvprintw_col(interface->win_main, 17, posX_item+2, WHITE, "<< Quitter le jeu >>");
}

void interface_delete_menu(interface_client_t* interface){
    for(int x=0; x<DEFAULT_WIDTH_INTERFACE_CLIENT; x++){
        for(int y=8; y< DEFAULT_HEIGHT_INTERFACE_CLIENT; y++){
            window_mvprintw_col(interface->win_main, y, x, WHITE, " "); 
        }
    }
} 
