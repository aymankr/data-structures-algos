#ifndef PERSONNE_H
#define PERSONNE_H

struct Date
{
    int jour, mois, annee;
};

struct Personne
{
    char *nom, *prenom;
    struct Date naissance;
};

struct Annuaire
{
    int taille;
    struct Personne *tableau;
};

void afficher_annuaire(const struct Annuaire *ptr_annuaire);
void detruire_annuaire(struct Annuaire *ptr_annuaire);
char *copy_strdup(const char* s);
int ajouter_personnes(struct Annuaire *ptr_annuaire, const struct Personne *ptr_nouveau, int n);
void liberer_personne(struct Personne *ptr);
void free_personne(struct Personne* p);
void display_personne(const struct Personne* p);
struct Personne* create_personne(const char* name, const char* fname, int year, int month, int day);

#endif
