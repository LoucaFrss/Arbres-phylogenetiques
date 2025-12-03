#include "arbresphylo.h"
#include "arbres.h"
#include "listes.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analyse_arbre(arbre racine, int *nb_esp, int *nb_carac)
{

       if (!racine)
              return;

       if (racine->gauche || racine->droit) // Si la racine a des sous-noeuds, c'est un caractère.
       {
              (*nb_carac)++;
              // On explore recursivement les sous-noeuds.
              analyse_arbre(racine->gauche, nb_esp, nb_carac);
              analyse_arbre(racine->droit, nb_esp, nb_carac);
       }
       else // Si la racine n'a pas de sous-noeud, c'est une espèce.
              (*nb_esp)++;
}

int est_caractere(arbre racine)
{
       return !((racine->gauche == NULL) && (racine->droit == NULL));
}
int est_espece(arbre racine)
{
       return (racine->gauche == NULL) && (racine->droit == NULL);
}

/* ACTE II */
/* Recherche l'espece dans l'arbre. Modifie la liste passée en paramètre pour y
 * mettre les caractéristiques. Retourne 0 si l'espèce a été retrouvée, 1 sinon.
 */
int rechercher_espece(arbre racine, char *espece, liste_t *seq)
{
       if (!racine)
              return 1;

       if (est_espece(racine) && (strcmp(racine->valeur, espece) == 0))
              return 0;

       if (rechercher_espece(racine->gauche, espece, seq) == 0)
              return 0;
       if (rechercher_espece(racine->droit, espece, seq) == 0)
       {
              ajouter_tete(seq, racine->valeur);
              return 0;
       }

       return 1;
}

/* Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un
 * message d'erreur.
 */
int ajouter_espece(arbre *a, char *espece, cellule_t *seq)
{

       return 1;
}

/* Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 */
void afficher_par_niveau(arbre racine, FILE *fout)
{
       printf("<<<<< À faire: fonction afficher_par_niveau fichier " __FILE__ " >>>>>\n");
}

// Acte 4

int ajouter_carac(arbre *a, char *carac, cellule_t *seq)
{
       printf("<<<<< À faire: fonction ajouter_carac fichier " __FILE__ " >>>>>\n");
       return 0;
}
