#include "arbresphylo.h"
#include "graphviz.h"
#include "arbres.h"
#include "listes.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analyse_arbre2(arbre racine, int *nb_esp, int *nb_carac)
{

       if (!racine)
              return;

       if (racine->gauche || racine->droit) // Si la racine a des sous-noeuds, c'est un caractère.
       {
              (*nb_carac)++;
              // On explore recursivement les sous-noeuds.
              analyse_arbre2(racine->gauche, nb_esp, nb_carac);
              analyse_arbre2(racine->droit, nb_esp, nb_carac);
       }
       else // Si la racine n'a pas de sous-noeud, c'est une espèce.
              (*nb_esp)++;
}
void analyse_arbre(arbre racine, int *nb_esp, int *nb_carac)
{
       *nb_carac = 0;
       *nb_esp = 0;
       analyse_arbre2(racine, nb_esp, nb_carac);
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
       if (!(*a))
       {
              *a = nouveau_noeud();
              if (!seq)
              {
                     (*a)->valeur = espece;
                     return 0;
              }

              (*a)->valeur = seq->val;
              return ajouter_espece(&(*a)->droit, espece, seq->suivant);
       }
       if (!seq)
       {
              if (est_espece(*a))
              {
                     printf("Ne peut ajouter %s: possède les mêmes caractères que %s.\n", espece, (*a)->valeur);
                     return 1;
              }
              return ajouter_espece(&(*a)->gauche, espece, NULL);
       }
       if (est_espece(*a))
       {
              (*a)->gauche = nouveau_noeud();
              (*a)->gauche->valeur = (*a)->valeur;
              (*a)->valeur = seq->val;
              return ajouter_espece(&(*a)->droit, espece, seq->suivant);
       }
       if (strcmp((*a)->valeur, seq->val) == 0)
       {
              if (!(*a)->droit)
              {
                     (*a)->droit = nouveau_noeud();
                     (*a)->droit->valeur = seq->val;
              }
              return ajouter_espece(&(*a)->droit, espece, seq->suivant);
       }
       return ajouter_espece(&(*a)->gauche, espece, seq);
}

/* Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 */
void afficher_par_niveau(arbre racine, FILE *fout)
{
       if (!racine)
              return;

       liste_t *l = malloc(sizeof(liste_t));
       init_liste_vide(l);
       liste_t *l2 = malloc(sizeof(liste_t));
       init_liste_vide(l2);
       ajouter_tete(l, racine);
       while (l->tete || l2->tete)
       {
              while (l->tete)
              {
                     // printf("test\n");
                     arbre a = retirer_tete(l);
                     if (est_caractere(a))
                     {
                            fprintf(fout, "%s ", a->valeur);
                            if (a->gauche)
                                   ajouter_queue(l2, a->gauche);

                            if (a->droit)
                                   ajouter_queue(l2, a->droit);
                     }
              }
              fprintf(fout, "\n");

              liste_t *l_tmp = l;
              l = l2;
              l2 = l_tmp;
       }
}

// Acte 4

int contient_liste(liste_t *l, char *v)
{
       for (cellule_t *c = l->tete; c != NULL; c = c->suivant)
       {
              if (strcmp(c->val, v) == 0)
                     return 1;
       }
       return 0;
}

void collecter_especes(arbre a, liste_t *especes)
{
       if (!a)
              return;
       if (est_espece(a))
       {
              ajouter_queue(especes, a->valeur);
       }
       else
       {
              collecter_especes(a->gauche, especes);
              collecter_especes(a->droit, especes);
       }
}

int verifier_et_compter(arbre a, liste_t *l, int *compte)
{
       if (!a)
              return 1;
       if (est_espece(a))
       {
              if (contient_liste(l, a->valeur))
              {
                     (*compte)++;
                     return 1;
              }
              else
              {
                     return 0;
              }
       }
       else
       {
              int gauche_ok = verifier_et_compter(a->gauche, l, compte);
              int droit_ok = verifier_et_compter(a->droit, l, compte);
              return gauche_ok && droit_ok;
       }
}

int est_clade(arbre a, liste_t *l)
{
       int compte = 0;
       int tous_presents = verifier_et_compter(a, l, &compte);
       if (!tous_presents)
              return 0;

       // Compter la longueur de la liste
       int longueur_l = 0;
       cellule_t *c = l->tete;
       while (c)
       {
              longueur_l++;
              c = c->suivant;
       }

       return compte == longueur_l;
}

arbre *trouve_clade(arbre *a, liste_t *l)
{
       if (!*a)
              return NULL;
       if (est_clade(*a, l))
              return a;
       arbre *gauche = trouve_clade(&((*a)->gauche), l);
       if (gauche)
              return gauche;
       arbre *droit = trouve_clade(&((*a)->droit), l);
       if (droit)
              return droit;
       return NULL;
}

int ajouter_carac(arbre *a, char *carac, cellule_t *seq)
{
       if (!(*a))
       {
              return 1;
       }
       liste_t especes;
       especes.tete = seq;
       especes.queue = NULL;

       arbre *a2 = trouve_clade(a, &especes);
       if (!a2)
              return 0;

       // Ajouter un nouveau noeud
       arbre n = nouveau_noeud();
       n->droit = *a2;
       *a2 = n;
       n->valeur = carac;

       return 1;
}
