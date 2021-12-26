#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personne.h"

void afficher_annuaire(const struct Annuaire *ptr_annuaire)
{
    printf("\nAffichage de l'annuaire - taille : %d\n", ptr_annuaire->taille);
    for (int i = 0; i < ptr_annuaire->taille; i++)
    {
        struct Personne p = ptr_annuaire->tableau[i];
        printf("%d : %s:%s\n", (i + 1), p.nom, p.prenom);
    }
    printf("\n");
}

void detruire_annuaire(struct Annuaire *ptr_annuaire)
{
    for (int i = 0; i < ptr_annuaire->taille; i++)
    {
        free(ptr_annuaire->tableau[i].nom);
        free(ptr_annuaire->tableau[i].prenom);
        ptr_annuaire->tableau[i].nom = NULL;
        ptr_annuaire->tableau[i].prenom = NULL;
    }
    free(ptr_annuaire->tableau);
    ptr_annuaire->tableau = NULL;
    ptr_annuaire->taille = 0;
    printf("%s\n", "Destruction de l'annuaire.");
}

int ajouter_personnes(struct Annuaire *ptr_annuaire, const struct Personne *ptr_nouveau, int n)
{
    if (n > 0)
    {
        // realloc = malloc if tableau is NULL
        ptr_annuaire->tableau = realloc(ptr_annuaire->tableau, (ptr_annuaire->taille + n) * sizeof(struct Personne));
        ptr_annuaire->taille += n;
        for (int i = 0; i < n; i++)
        {
            ptr_annuaire->tableau[ptr_annuaire->taille - n + i].nom = strdup(ptr_nouveau->nom);
            ptr_annuaire->tableau[ptr_annuaire->taille - n + i].prenom = strdup(ptr_nouveau->prenom);
            ptr_annuaire->tableau[ptr_annuaire->taille - n + i].naissance.annee = ptr_nouveau->naissance.annee;
            ptr_annuaire->tableau[ptr_annuaire->taille - n + i].naissance.jour = ptr_nouveau->naissance.jour;
            ptr_annuaire->tableau[ptr_annuaire->taille - n + i].naissance.mois = ptr_nouveau->naissance.mois;
        }
    }
    return 0;
}

void free_personne(struct Personne *p)
{
    free(p->nom);
    free(p->prenom);
    p->nom = NULL;
    p->prenom = NULL;
    free(p);
    p = NULL;
}

void display_personne(const struct Personne *p)
{
    printf("%s %s %d %d %d\n", p->nom, p->prenom, p->naissance.annee, p->naissance.mois,
           p->naissance.jour);
}

struct Personne *create_personne(const char *name, const char *fname, int year, int month, int day)
{
    struct Personne *p = (struct Personne *)malloc(sizeof(struct Personne));
    p->naissance.annee = year;
    p->naissance.jour = month;
    p->naissance.mois = day;
    p->nom = strdup(name);
    p->prenom = strdup(fname);
    return p;
}

int compare_personnes(const struct Personne *p1, const struct Personne *p2)
{
    if (p2->naissance.annee > p1->naissance.annee)
    {
        return 1;
    }
    else if (p2->naissance.annee < p1->naissance.annee)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void modify_personne(struct Personne *p1, struct Personne *p2)
{
    p1->naissance.annee = p2->naissance.annee;
    p1->naissance.jour = p2->naissance.jour;
    p1->naissance.mois = p2->naissance.mois;
    free(p1->nom);
    free(p1->prenom);
    p1->nom = strdup(p2->nom);
    p1->prenom = strdup(p2->prenom);
}