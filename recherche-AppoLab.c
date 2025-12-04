#include "arbres.h"
#include "arbresphylo.h"
#include <stdlib.h>
int main()
{
    FILE *f = fopen("./tests/recherche-AppoLab.test", "r");
    arbre a = lire_arbre(f);
    liste_t *l = malloc(sizeof(liste_t));
    init_liste_vide(l);
    int s = rechercher_espece(a, "AppoLab", l);
    if (s == 1)
    {
        printf("Appolab introuvable\n");
    }
    while (l->tete)
    {
        printf("%s ", (char *)l->tete->val);
        cellule_t *cel = l->tete;
        l->tete = l->tete->suivant;
        free(cel);
    }
    printf("AppoLab\n");
}