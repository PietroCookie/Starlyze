/**
 * @file info_client.c
 * @author HADID Hocine & CHEMIN Pierre
 * @brief File that manages the data structures of the clients
 * @version 0.1
 * @date 2023-03-29
 *
 * @copyright Copyright (c) 2023
 *
 */
// INCLUDES
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "info_client.h"

/**
 * @brief Function to initialize the list of clients
 *
 * @param list
 */
void init_list_info_client(list_info_client_t *list)
{
    list->head = NULL;
    list->nb_clients = 0;
}

/**
 * @brief Function to initialize the information of a client
 *
 * @param id
 * @param pseudo
 * @param client_address
 * @param port
 * @return info_client_t*
 */
info_client_t *init_info_client(int id, char pseudo[MAX_MSG], char *client_address, int port)
{
    info_client_t *info = malloc(sizeof(info_client_t));
    info->id = id;
    strcpy(info->pseudo, pseudo);
    info->client_address = client_address;
    info->port = port;
    info->next = NULL;
    info->prev = NULL;
    return info;
}

/**
 * @brief Function to check if the list of clients is empty
 *
 * @param list
 * @return int
 */
int is_empty_client(list_info_client_t *list)
{
    if (list->head == NULL)
    {
        return 1; // Right
    }
    else
    {
        return 0; // False
    }
}

/**
 * @brief Function to add a client to the list of clients
 *
 * @param list
 * @param client
 */
void add_client(list_info_client_t *list, info_client_t *client)
{
    if (is_empty_client(list) == 1)
    {
        list->head = client;
        list->head->next = NULL;
        list->head->prev = NULL;
    }
    else
    {
        client->next = list->head;
        if (list->head != NULL)
        {
            list->head->prev = client;
        }
        list->head = client;
        client->prev = NULL;
    }
    list->nb_clients++;
}

/**
 * @brief Function to print the list of clients
 *
 * @param list
 */
void print_list_client(list_info_client_t list)
{
    if (is_empty_client(&list) == 1)
    {
        printf("Liste vide\n");
    }
    else
    {
        info_client_t *current = list.head;
        while (current != NULL)
        {
            printf("Client %d - Pseudo: %s - Adresse: %s - Port : %d\n", current->id, current->pseudo, current->client_address, current->port);
            current = current->next;
        }
    }
}

/**
 * @brief Function to search a client in the list of clients
 *
 * @param list
 * @param id
 * @return info_client_t*
 */
info_client_t *search_client(list_info_client_t *list, int id)
{
    info_client_t *current = list->head;
    while (current != NULL)
    {
        if (current->id == id)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * @brief Function to delete a client from the list of clients
 *
 * @param list
 * @param client
 */
void delete_client(list_info_client_t *list, info_client_t *client)
{
    if (client->prev == NULL)
    {
        list->head = client->next;
    }
    else
    {
        client->prev->next = client->next;
    }
    if (client->next != NULL)
    {
        client->next->prev = client->prev;
    }
    free(client);
    list->nb_clients--;
}

/**
 * @brief Function to delete the list of clients
 *
 * @param list
 */
void delete_list(list_info_client_t *list)
{
    info_client_t *current = list->head;
    while (current != NULL)
    {
        info_client_t *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}