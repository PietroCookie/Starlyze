#include "interface_client.h"

#include "functions.h"
#include "colors.h"
#include <string.h>


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
    interface_print_menu(result); 
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

        // Number of players
        if((mouseX >= 29 && mouseX<=71) && mouseY==12){
            window_mvprintw_col(interface->win_main, 7, posX_item+2, WHITE, "<< Nombre de joueur(s) connecte(s) : 2 >>"); 
            window_refresh(interface->win_main);
            for(int x=0; x<DEFAULT_WIDTH_INTERFACE_CLIENT; x++){
                for(int y=0; y< DEFAULT_HEIGHT_INTERFACE_CLIENT; y++){
                    window_mvprintw_col(interface->win_main, y, x, WHITE, " "); 
                }
            } 
            interface_print_logo(interface); 
        }else if((mouseX >= 29 && mouseX<=64) && mouseY == 14){
            window_mvprintw_col(interface->win_main, 11, posX_item+2, WHITE, "<< Nombre de joueur(s) connecte(s) : 2 >>"); 
            window_mvprintw_col(interface->win_main, 13, posX_item+2, GREEN, "<< Creer une partie de starlyze >>"); 
            window_mvprintw_col(interface->win_main, 15, posX_item+2, WHITE, "<< Rejoindre partie en attente : 3 >>"); 
            window_mvprintw_col(interface->win_main, 17, posX_item+2, WHITE, "<< Quitter le jeu >>");            
            window_refresh(interface->win_main);
        }else if((mouseX>=29 && mouseX<=67) && mouseY==16){
            window_mvprintw_col(interface->win_main, 11, posX_item+2, WHITE, "<< Nombre de joueur(s) connecte(s) : 2 >>"); 
            window_mvprintw_col(interface->win_main, 13, posX_item+2, WHITE, "<< Creer une partie de starlyze >>"); 
            window_mvprintw_col(interface->win_main, 15, posX_item+2, GREEN, "<< Rejoindre partie en attente : 3 >>"); 
            window_mvprintw_col(interface->win_main, 17, posX_item+2, WHITE, "<< Quitter le jeu >>");            
            window_refresh(interface->win_main); 
        }else if((mouseX>=29 && mouseX<=60) && mouseY==18){
            window_mvprintw_col(interface->win_main, 11, posX_item+2, WHITE, "<< Nombre de joueur(s) connecte(s) : 2 >>"); 
            window_mvprintw_col(interface->win_main, 13, posX_item+2, WHITE, "<< Creer une partie de starlyze >>"); 
            window_mvprintw_col(interface->win_main, 15, posX_item+2, WHITE, "<< Rejoindre partie en attente : 3 >>"); 
            window_mvprintw_col(interface->win_main, 17, posX_item+2, GREEN, "<< Quitter le jeu >>");
            window_refresh(interface->win_main); 
            ncurses_stop(); 
            interface_delete_client(&interface); 
            exit(EXIT_SUCCESS); 
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
    window_mvprintw_col(result->win_main, 1, 8, GREEN, "/_/_/_/"); 
    window_mvprintw_col(result->win_main, 2, 6, GREEN, "/_/"); 
    window_mvprintw_col(result->win_main, 3, 7, GREEN, "/_/_/"); 
    window_mvprintw_col(result->win_main, 4, 10, GREEN, "/_/"); 
    window_mvprintw_col(result->win_main, 5, 5, GREEN, "/_/_/_/");
    // T
    window_mvprintw_col(result->win_main, 1, 16, GREEN, "/_/_/_/_/_/"); 
    window_mvprintw_col(result->win_main, 2, 19, GREEN, "/_/"); 
    window_mvprintw_col(result->win_main, 3, 18, GREEN, "/_/"); 
    window_mvprintw_col(result->win_main, 4, 17, GREEN, "/_/"); 
    window_mvprintw_col(result->win_main, 5, 16, GREEN, "/_/"); 
    // A
    window_mvprintw_col(result->win_main, 1, 30, GREEN, "/_/_/"); 
    window_mvprintw_col(result->win_main, 2, 27, GREEN, "/_/    /_/"); 
    window_mvprintw_col(result->win_main, 3, 26, GREEN, "/_/_/_/_/"); 
    window_mvprintw_col(result->win_main, 4, 25, GREEN, "/_/    /_/"); 
    window_mvprintw_col(result->win_main, 5, 24, GREEN, "/_/    /_/"); 
    // R
    window_mvprintw_col(result->win_main, 1, 40, GREEN, "/_/_/_/"); 
    window_mvprintw_col(result->win_main, 2, 39, GREEN, "/_/    /_/"); 
    window_mvprintw_col(result->win_main, 3, 38, GREEN, "/_/_/_/");
    window_mvprintw_col(result->win_main, 4, 37, GREEN, "/_/    /_/"); 
    window_mvprintw_col(result->win_main, 5, 36, GREEN, "/_/    /_/"); 
    // L
    window_mvprintw_col(result->win_main, 1, 52, GREEN, "/_/"); 
    window_mvprintw_col(result->win_main, 2, 51, GREEN, "/_/"); 
    window_mvprintw_col(result->win_main, 3, 50, GREEN, "/_/"); 
    window_mvprintw_col(result->win_main, 4, 49, GREEN, "/_/"); 
    window_mvprintw_col(result->win_main, 5, 48, GREEN, "/_/_/_/_/"); 
    // Y
    window_mvprintw_col(result->win_main, 1, 58, GREEN, "/_/      /_/"); 
    window_mvprintw_col(result->win_main, 2, 59, GREEN, "/_/  /_/"); 
    window_mvprintw_col(result->win_main, 3, 60, GREEN, "/_/"); 
    window_mvprintw_col(result->win_main, 4, 59, GREEN, "/_/"); 
    window_mvprintw_col(result->win_main, 5, 58, GREEN, "/_/"); 
    // Z
    window_mvprintw_col(result->win_main, 1, 71, GREEN, "/_/_/_/_/_/"); 
    window_mvprintw_col(result->win_main, 2, 75, GREEN, "/_/"); 
    window_mvprintw_col(result->win_main, 3, 73, GREEN, "/_/"); 
    window_mvprintw_col(result->win_main, 4, 71, GREEN, "/_/"); 
    window_mvprintw_col(result->win_main, 5, 68, GREEN, "/_/_/_/_/_/"); 
    // E 
    window_mvprintw_col(result->win_main, 1, 84, GREEN, "/_/_/_/_/"); 
    window_mvprintw_col(result->win_main, 2, 83, GREEN, "/_/"); 
    window_mvprintw_col(result->win_main, 3, 82, GREEN, "/_/_/_/"); 
    window_mvprintw_col(result->win_main, 4, 81, GREEN, "/_/"); 
    window_mvprintw_col(result->win_main, 5, 80, GREEN, "/_/_/_/_/");    
}


void interface_print_menu(interface_client_t* interface){
    int posX_item; 

    window_mvprintw_col(interface->win_main, 7, 0, WHITE, "=================================================================================================="); 

    posX_item = (DEFAULT_WIDTH_INTERFACE_CLIENT/2)-((int)strlen("-------------------- MENU --------------------")/2);
    window_mvprintw_col(interface->win_main, 9, posX_item, WHITE, "-------------------- MENU --------------------");  
    window_mvprintw_col(interface->win_main, 11, posX_item+2, WHITE, "<< Nombre de joueur(s) connecte(s) : 2 >>"); 
    window_mvprintw_col(interface->win_main, 13, posX_item+2, WHITE, "<< Creer une partie de starlyze >>"); 
    window_mvprintw_col(interface->win_main, 15, posX_item+2, WHITE, "<< Rejoindre partie en attente : 3 >>"); 
    window_mvprintw_col(interface->win_main, 17, posX_item+2, WHITE, "<< Quitter le jeu >>");
}