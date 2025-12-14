#include "graphviz.h"
#include "listes.h"

int ecrire_noeud(FILE *f, arbre a, int *node_id)
{
    int my_id = (*node_id)++;
    fprintf(f, "   noeud%d [label=\"%s\"];\n", my_id, a->valeur);
    if (a->gauche)
    {
        int left_id = ecrire_noeud(f, a->gauche, node_id);
        fprintf(f, "   noeud%d -> noeud%d [label = \"non\"]\n", my_id, left_id);
    }
    if (a->droit)
    {
        int right_id = ecrire_noeud(f, a->droit, node_id);
        fprintf(f, "   noeud%d -> noeud%d [label = \"oui\"]\n", my_id, right_id);
    }
    return my_id;
}

void ecrire_graphviz(FILE *f, arbre a)
{
    fprintf(f, "digraph arbre {\n");
    if (a)
    {
        int node_id = 0;
        ecrire_noeud(f, a, &node_id);
    }
    fprintf(f, "}\n");
}

// int main()
// {
//     FILE *f = fopen("./tests/arbre-simple.test", "r");
//     arbre a = lire_arbre(f);
//     FILE *f2 = fopen("./affichage.dot", "w");
//     ecrire_graphviz(f2, a);
// }