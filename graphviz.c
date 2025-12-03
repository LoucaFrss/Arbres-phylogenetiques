#include "graphviz.h"
#include "listes.h"

void ecrire_noeud(FILE *f, arbre a)
{
    if (a->gauche)
    {
        fprintf(f, "   %s -> %s [label = \"%s\"]\n", a->valeur, a->gauche->valeur, "non");
        ecrire_noeud(f, a->gauche);
    }
    if (a->droit)
    {
        fprintf(f, "   %s -> %s [label = \"%s\"]\n", a->valeur, a->droit->valeur, "oui");
        ecrire_noeud(f, a->droit);
    }
}
void ecrire_graphviz(FILE *f, arbre a)
{
    fprintf(f, "digraph arbre {\n");
    if (a)
    {

        ecrire_noeud(f, a);
    }
    fprintf(f, "}\n");
}

int main()
{
    FILE *f = fopen("./tests/arbre-simple.test", "r");
    arbre a = lire_arbre(f);
    FILE *f2 = fopen("./affichage.dot", "w");
    ecrire_graphviz(f2, a);
}