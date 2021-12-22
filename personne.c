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
        ptr_annuaire->tableau[i].naissance.jour = 0;
        ptr_annuaire->tableau[i].naissance.mois = 0;
        ptr_annuaire->tableau[i].naissance.annee = 0;
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
        // realloc se comportera comme un malloc si le pointeur tableau est NULL
        ptr_annuaire->tableau = realloc(ptr_annuaire->tableau, (ptr_annuaire->taille + n) * sizeof(struct Personne));
        ptr_annuaire->taille += n;
        for (int i = 0; i < n; i++)
        {
            ptr_annuaire->tableau[ptr_annuaire->taille - n + i].nom = copy_strdup(ptr_nouveau->nom);
            ptr_annuaire->tableau[ptr_annuaire->taille - n + i].prenom = copy_strdup(ptr_nouveau->prenom);
            ptr_annuaire->tableau[ptr_annuaire->taille - n + i].naissance.annee = ptr_nouveau->naissance.annee;
            ptr_annuaire->tableau[ptr_annuaire->taille - n + i].naissance.jour = ptr_nouveau->naissance.jour;
            ptr_annuaire->tableau[ptr_annuaire->taille - n + i].naissance.mois = ptr_nouveau->naissance.mois;
        }
    }
    return 0;
}

//bug de strdup, utilisation du code source dans la fonction copy_strdup...
char *copy_strdup(const char *s)
{
    size_t len = strlen(s) + 1;
    void *new = malloc(len);
    if (new == NULL)
        return NULL;
    return (char *)memcpy(new, s, len);
}

void free_personne(struct Personne* p)
{
    free(p->nom);
    free(p->prenom);
    free(p);
    p = NULL;
}

void display_personne(const struct Personne* p)
{
    printf("Nom : %s\n", (*p).nom);
    printf("Prenom : %s\n", p->prenom);
    printf("Date naissance : %d/%d/%d\n", p->naissance.jour,
           p->naissance.mois,
           p->naissance.annee);
}