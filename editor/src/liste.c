#include "liste.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void initialiser_liste(liste_t* l)
{
    l->tete = NULL;
}

int liste_vide(liste_t l)
{
    return l.tete == NULL;
}

void inserer_liste(liste_t* l, cellule_t* c)
{
    c->succ = l->tete;
    if(l->tete != NULL)
    {
        l->tete->pred = c;
    }
    l->tete = c;
    c->pred = NULL;
}

void supprimer_liste(liste_t* l, cellule_t* c)
{
    if(c->pred != NULL)
    {
        c->pred->succ = c->succ;
    }
    else
    {
        l->tete = c->succ;
    }

    if(c->succ != NULL)
    {
        c->succ->pred = c->pred;
    }

	free(c);
}

void detruire_liste(liste_t* l)
{
	cellule_t* temp;
    cellule_t* c = l->tete;
    while(c != NULL)
    {
		temp = c->succ;
        supprimer_liste(l, c);
        c = temp;
    }

    l = NULL;

    printf("La liste est détruite !\n");
}