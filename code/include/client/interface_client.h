#ifndef __INTERFACE_CLIENT__
#define __INTERFACE_CLIENT__


#include "window.h"

#define DEFAULT_WIDTH_INTERFACE_CLIENT 100
#define DEFAULT_HEIGHT_INTERFACE_CLIENT 22

typedef struct{
    window_t* win_main; 
    window_t* win_infos; 
}interface_client_t; 


/**
 * Check terminal dimensions.
 */
void interface_dimensions_client(unsigned short width, unsigned short height);

/**
 * @brief Create interface
 * 
 * @return interface_t* created interface
 */
interface_client_t* interface_create_client();

/**
 * @brief Delete interface
 * 
 * @param interface interface to delete
 */
void interface_delete_client(interface_client_t** interface);

/**
 * @brief Manage actions of the user.
 * 
 * @param interface the interface
 * @param c the pressed key
 */
void interface_actions_client(interface_client_t* interface, int c);

/**
 * @brief Show the letter S in the logo
 * @param result the interface
 */
void interface_print_logo(interface_client_t* result); 

void interface_print_menu(interface_client_t* result); 

void interface_delete_menu(interface_client_t* interface); 

#endif