#ifndef __CELLULE_H__
#define __CELLULE_H__

#include "element_map.h"

struct SCellule
{
    element_map_t element;
    struct SCellule* pred; /* Sommet précédant dans la liste */
    struct SCellule* succ; /* Sommet suivant dans la liste */
};

typedef struct SCellule cellule_t;

/**
 * @brief Permet d'initialiser une cellule avec la valeur donnée
 * 
 * @param c La cellule a initialisé
 * @param sommet La valeur du sommet
 */
void initialiser_cellule(cellule_t* c, element_map_t element);

#endif