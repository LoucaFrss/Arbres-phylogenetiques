#include "listes.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* fichier à compléter au besoin */

void init_liste_vide(liste_t *L)
{
    L->tete = NULL;
}

/*
 * Supprime toutes les cellules d'une liste L, sans faire de free sur
 * L elle-même.
 */
void liberer_liste(liste_t *L)
{
    while (L->tete)
    {
        cellule_t *c = L->tete;
        L->tete = c->suivant;
        free(c);
    }
}

int ajouter_tete(liste_t *L, string c)
{ /* retourne 0 si OK, 1 sinon  */

    cellule_t *cel = malloc(sizeof(cellule_t));
    cel->val = c;
    cel->suivant = L->tete;
    L->tete = cel;

    return 0;
}
