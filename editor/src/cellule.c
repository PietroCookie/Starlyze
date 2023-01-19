#include "cellule.h"

#include <stddef.h>

void initialiser_cellule(cellule_t* c, element_map_t element)
{
	c->element = element;
    c->pred = NULL;
    c->succ = NULL;
}