#ifndef __LISTE_H__
#define __LISTE_H__

#include "cellule.h"
#include "element_map.h"

typedef struct
{
    cellule_t* tete; /* La tête de la liste */
} liste_t;

/**
 * @brief Permet d'initialiser une liste (définit la tête à NULL)
 * 
 * @param l La liste a initialisé
 */
void initialiser_liste(liste_t* l);
/**
 * @brief Permet de savoir si une liste est vide
 * 
 * @param l La liste a testé
 * @return int Si la liste est vide ou non
 */
int liste_vide(liste_t l);
/**
 * @brief Permet d'insérer une cellule dans la liste (insére à la tête)
 * 
 * @param l La liste dans laquelle il faut insérer
 * @param c La cellule a inséré dans la liste
 */
void inserer_liste(liste_t* l, cellule_t* c);
/**
 * @brief Permet de supprimer une cellule de la liste
 * 
 * @param l La liste dans laquelle on supprimer la cellule
 * @param c La cellule a supprimé
 */
void supprimer_liste(liste_t* l, cellule_t* c);
/**
 * @brief Permet de détruire une liste et de gérer la libération mémoire
 * 
 * @param l La liste a supprimé
 */
void detruire_liste(liste_t* l);

#endif