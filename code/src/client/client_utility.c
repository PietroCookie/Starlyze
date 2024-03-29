/**
 * @file client_utility.c
 * @author HADID Hocine & CHEMIN Pierre
 * @brief
 * @version 0.1
 * @date 2023-03-28
 *
 * @copyright Copyright (c) 2023
 *
 */

// INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "client_utility.h"
#include "client_udp.h"
#include "client_create_game.h"
#include "client_join_game.h"
#include "client_tcp.h"

/**
 * @brief Display the logo of the application
 *
 */
void display_logo_app()
{
    printf("##################################################################################################################\n");
    printf("#        /_/_/_/   /_/_/_/_/_/      /_/_/       /_/_/_/       /_/      /_/      /_/    /_/_/_/_/_/    /_/_/_/_/  #\n");
    printf("#     /_/             /_/        /_/   /_/     /_/   /_/     /_/        /_/  /_/            /_/      /_/         #\n");
    printf("#      /_/_/         /_/        /_/_/_/_/     /_/_/_/       /_/          /_/            /_/         /_/_/_/      #\n");
    printf("#         /_/       /_/        /_/   /_/     /_/   /_/     /_/          /_/          /_/           /_/           #\n");
    printf("#  /_/_/_/         /_/        /_/   /_/     /_/   /_/     /_/_/_/_/    /_/        /_/_/_/_/_/     /_/_/_/_/      #\n");
    printf("##################################################################################################################\n");
}

/**
 * @brief Entering the user's nickname
 *
 * @return char*
 */
char *pseudo_entry()
{
    char *pseudo;
    if ((pseudo = malloc(MAX_MSG * sizeof(char))) == NULL)
    {
        perror("[ERROR] - Memory allocation pseudo failed");
        exit(EXIT_FAILURE);
    }
    printf("\n\n============================ Et si on faisait connaissance ? ============================\n");
    printf("Veuillez saisir votre pseudo : ");
    if (scanf("%[^\n]", pseudo) == -1)
    {
        perror("[ERROR] - Error when retrieving the choice\n");
        exit(EXIT_FAILURE);
    }
    printf("=========================================================================================\n");
    return pseudo;
}

/**
 * @brief Display the menu for the client
 *
 * @param nb_players
 */
void display_menu(int nb_players)
{
    printf("\n\n=========================== M E N U =========================== \n");
    printf(" 1°) << Nombre de joueur(s) connecte(s) sur Starlyze : %d >>\n", nb_players);
    printf(" 2°) << Créer une partie de STARLYZE >>                     \n");
    printf(" 3°) << Rejoindre une partie en attente >>                  \n");
    printf(" 4°) << Quitter le jeu >>                                   \n");
    printf("==============================================================   \n\n");
}

/**
 * @brief Allows the management of the menu
 *
 * @param port
 * @param address_ip
 * @param info_client
 * @param sockfd
 */
void handler_menu(int port, char address_ip[15], info_client_t info_client, int sockfd)
{
    int choice = 0, nb_clients, choice_world, choice_nb_players = 0, choice_game = 0, choice_quit = 0;
    list_world_response_t list_world;
    list_game_without_pointers_t list_game;

    while (choice <= 0)
    {
        printf("Quel est votre choix ? ");
        if (scanf("%d", &choice) == -1)
        {
            perror("[ERROR] - Error when retrieving the choice\n");
            exit(EXIT_FAILURE);
        }
    }
    switch (choice)
    {
    case 1:
        printf("\n\n====================== Nombre de joueur(s) connecte(s) ======================\n");
        nb_clients = receive_response_nb_clients(port, address_ip, sockfd);
        if (nb_clients == 1)
        {
            printf("Il y a actuellemnt %d joueur qui est connecté sur STARLYZE\n\n", nb_clients);
        }
        else
        {
            printf("Il y a actuellemnt %d joueurs qui sont connectés sur STARLYZE\n\n", nb_clients);
        }
        printf("1°) Retour au menu\n");
        printf("2°) Quitter le jeu\n\n");
        while (choice_nb_players <= 0)
        {
            printf("Quel est votre choix ? ");
            if (scanf("%d", &choice_nb_players) == -1)
            {
                perror("[ERROR] - Error when retrieving the choice\n");
                exit(EXIT_FAILURE);
            }
        }
        switch (choice_nb_players)
        {
        case 1:
            nb_clients = receive_response_nb_clients(port, address_ip, sockfd);
            display_menu(nb_clients);
            handler_menu(port, address_ip, info_client, sockfd);
            break;
        case 2:
            send_request_to_client_disconnection(info_client, port, address_ip, sockfd);
            printf("\n\n<<<<<<< Jeu en arrêt ... >>>>>>>\n");
            exit(EXIT_FAILURE);
            break;
        default:
            printf("Votre choix n'est pas parmi les choix proposés\n");
            exit(EXIT_FAILURE);
            break;
        }
        break;
    case 2:
        printf("\n\n====================== Créer une partie de STARLYZE ======================\n");
        list_world = receive_list_world(port, address_ip, sockfd);
        choice_world = handler_create_game(list_world, port, address_ip, info_client.id, sockfd);
        if (choice_world == 0)
        {
            nb_clients = receive_response_nb_clients(port, address_ip, sockfd);
            display_menu(nb_clients);
            handler_menu(port, address_ip, info_client, sockfd);
        }
        else
        {
            receive_port_tcp_of_server(port, address_ip, sockfd);
        }
        break;
    case 3:
        printf("\n\n====================== Rejoindre une partie en attente ======================\n");
        list_game = receive_list_games_on_hold(port, address_ip, sockfd);
        if (list_game.nb_games == 0)
        {
            printf("Il n'y a aucune partie en attente pour le moment\n");
            while (choice_quit <= 0)
            {
                printf("1°) Retour au menu\n");
                printf("2°) Quitter le jeu\n\n");
                printf("Quel est votre choix ? ");
                if (scanf("%d", &choice_quit) == -1)
                {
                    perror("[ERROR] - Error when retrieving the choice\n");
                    exit(EXIT_FAILURE);
                }
            }
            if (choice_quit == 1)
            {
                nb_clients = receive_response_nb_clients(port, address_ip, sockfd);
                display_menu(nb_clients);
                handler_menu(port, address_ip, info_client, sockfd);
            }
            else
            {
                send_request_to_client_disconnection(info_client, port, address_ip, sockfd);
                printf("\n\n<<<<<<< Jeu en arrêt ... >>>>>>>\n");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            printf("Nombre de parties actuel : %d\n", list_game.nb_games);

            // Display the list of pending games
            for (int i = 0; i < list_game.nb_games; i++)
            {
                if (strlen(list_game.game[i].name_world) != 0)
                {
                    printf("%d°) Id game : %d | Monde : %s | Nombre de joueurs actuel : %d | Nombre de joueurs max : %d\n",
                           i + 1, list_game.game[i].id, list_game.game[i].name_world,
                           list_game.game[i].nb_participants_actual, list_game.game[i].nb_participants_final);
                }
            }

            while (choice_game == 0 || choice_game > list_game.nb_games)
            {
                if (choice_game > list_game.nb_games)
                {
                    printf("Votre choix n'est pas parmi les choix proposés\n");
                }
                printf("\n[Taper -1 pour quitter le jeu]\nQuel est votre choix ?");
                if (scanf("%d", &choice_game) == -1)
                {
                    perror("[ERROR] - Error when retrieving the choice\n");
                    exit(EXIT_FAILURE);
                }
            }
            if (choice_game < 0)
            {
                send_request_to_client_disconnection(info_client, port, address_ip, sockfd);
                printf("\n\n<<<<<<< Jeu en arrêt ... >>>>>>>\n");
                exit(EXIT_FAILURE);
            }
            else
            {
                printf("Vous avez choisi la partie n° : %d\n", choice_game);
                join_game(port, address_ip, choice_game, info_client.id);
                receive_port_tcp_of_server(port, address_ip, sockfd);
            }
        }

        break;
    case 4:
        send_request_to_client_disconnection(info_client, port, address_ip, sockfd);
        printf("\n\n<<<<<<< Jeu en arrêt ... >>>>>>>\n");
        exit(EXIT_FAILURE);
        break;
    default:
        fprintf(stderr, "\n[ERROR] - Erreur lors de la sélection dans le menu\n");
        fprintf(stderr, "[HELP]  - Veuillez sélectionner un chiffre entre 1 et 4 \n");
        printf("[INFO] - Vous avez été déconnecté du serveur\n");
        send_request_to_client_disconnection(info_client, port, address_ip, sockfd);
        exit(EXIT_FAILURE);
        break;
    }
}
