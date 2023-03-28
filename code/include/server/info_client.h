/**
 * @file info_client.h
 * @author HADID Hocine
 * @brief File that manages the information of the clients with data structures
 * @version 0.1
 * @date 2023-03-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __INFO_CLIENT_H__
#define __INFO_CLIENT_H__

// Constants
#define MAX_MSG 255

/**
 * @brief Structure that contains the information of a client
 *
 */
struct info_client_t
{
    int id;
    char pseudo[MAX_MSG];
    char *client_address;
    int port;
    struct info_client_t *next;
    struct info_client_t *prev;
};
typedef struct info_client_t info_client_t;

/**
 * @brief Structure that contains the list of clients
 *
 */
typedef struct
{
    info_client_t *head;
    int nb_clients;
} list_info_client_t;

/**
 * @brief Function to initialize the list of clients
 *
 * @param list
 */
void init_list_info_client(list_info_client_t *list);

/**
 * @brief Function to initialize the information of a client
 *
 * @param id
 * @param pseudo
 * @param client_address
 * @param port
 * @return info_client_t*
 */
info_client_t *init_info_client(int id, char pseudo[MAX_MSG], char *client_address, int port);

/**
 * @brief Function to check if the list of clients is empty
 *
 * @param list
 * @return int
 */
int is_empty_client(list_info_client_t *list);

/**
 * @brief Function to add a client to the list of clients
 *
 * @param list
 * @param client
 */
void add_client(list_info_client_t *list, info_client_t *client);

/**
 * @brief Function to print the list of clients
 *
 * @param list
 */
void print_list_client(list_info_client_t list);

/**
 * @brief Function to search a client in the list of clients
 *
 * @param list
 * @param id
 * @return info_client_t*
 */
info_client_t *search_client(list_info_client_t *list, int id);

/**
 * @brief Function to delete a client from the list of clients
 *
 * @param list
 * @param client
 */
void delete_client(list_info_client_t *list, info_client_t *client);

/**
 * @brief Function to delete the list of clients
 *
 * @param list
 */
void delete_list(list_info_client_t *list);

#endif