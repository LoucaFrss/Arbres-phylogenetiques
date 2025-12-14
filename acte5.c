#include "arbresphylo.h"
#include "graphviz.h"
int main()
{
    FILE *f = fopen("./tableau_test.tab", "r");

    arbre a = tableau_vers_arbre(f);
    fclose(f);

    FILE *fout = fopen("./arbre_tableau.dot", "w");
    ecrire_graphviz(fout, a);
    fclose(fout);
    afficher_par_niveau(a, stdout);
}