#include "arbres.h"
#include "arbresphylo.h"
#include <stdlib.h>
int main()
{
    FILE *f = fopen("./ents.test", "r");
    arbre a = lire_arbre(f);

    afficher_par_niveau(a, stdout);
}