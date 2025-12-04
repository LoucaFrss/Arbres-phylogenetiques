#include "listes.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* fichier à compléter au besoin */

void init_liste_vide(liste_t *L)
{
    L->tete = NULL;
    L->queue = NULL;
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

int ajouter_tete(liste_t *L, void *c)
{ /* retourne 0 si OK, 1 sinon  */

    cellule_t *cel = malloc(sizeof(cellule_t));
    cel->val = c;
    cel->suivant = L->tete;
    L->tete = cel;
    if (!L->queue)
        L->queue = cel;

    return 0;
}

void *retirer_tete(liste_t *L)
{
    cellule_t *cel = L->tete;
    if (!cel)
        return NULL;

    L->tete = cel->suivant;

    if (L->tete == NULL)
        L->queue = NULL;
    void *val = cel->val;
    free(cel);
    return val;
}
int ajouter_queue(liste_t *L, void *c)
{

    cellule_t *cel = malloc(sizeof(cellule_t));
    cel->val = c;
    cel->suivant = NULL;
    if (!L->tete)
    {

        L->tete = cel;
        L->queue = cel;
        return 0;
    }
    L->queue->suivant = cel;
    L->queue = cel;

    return 0;
}