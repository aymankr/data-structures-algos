#include <stdio.h>
#include <stdlib.h>
#include "file.h"

struct Cellule_s
{
    gpointer valeur;
    struct Cellule_s *pred;
    struct Cellule_s *succ;
};

struct File_s
{
    struct Cellule_s *premier;
    struct Cellule_s *queue;
    ptr_fonction_afficher afficher;
    ptr_fonction_liberer liberer;
};

File_t *File_creer(ptr_fonction_afficher afficher, ptr_fonction_liberer liberer)
{
    File_t *f = malloc(sizeof(File_t));
    f->queue = NULL;
    f->premier = NULL;
    f->afficher = afficher;
    f->liberer = liberer;
    return f;
}

struct Cellule_s *Cellule_creer()
{
    struct Cellule_s *cellule = malloc(sizeof(struct Cellule_s));
    cellule->pred = NULL;
    cellule->succ = NULL;
    cellule->valeur = NULL;
    return cellule;
}

void Cellule_liberer(struct Cellule_s *c)
{
    c->succ = NULL;
    c->pred = NULL;
    free(c);
}

void File_enfiler(File_t *f, gpointer v)
{
    struct Cellule_s *cellule = Cellule_creer();
    cellule->valeur = v;

    if (f->premier == NULL)
    {
        f->premier = cellule;
        f->queue = cellule;
    }
    else
    {
        struct Cellule_s *derniereCellule = f->queue;
        derniereCellule->succ = cellule;
    }
    f->queue = cellule;
}

void File_afficher(const File_t *f)
{
    struct Cellule_s *current = f->premier;
    while (current != NULL)
    {
        f->afficher(current->valeur);
        current = current->succ;
    }
    printf("->NULL\n");
}

gpointer File_defiler(File_t *f)
{
    struct Cellule_s *premiereCellule = f->premier;
    gpointer v = premiereCellule->valeur;

    if (f->premier == f->queue)
    {
        f->premier = NULL;
    }
    f->premier = premiereCellule->succ;

    Cellule_liberer(premiereCellule);
    return v;
}

int File_taille(const File_t *f)
{
    int taille = 0;
    struct Cellule_s *current = f->premier;
    while (current != NULL)
    {
        ++taille;
        current = current->succ;
    }
    return taille;
}

int File_vide(const File_t *f)
{
    if (File_taille(f) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void File_liberer(File_t *f)
{
    while (File_taille(f) != 0)
    {
        gpointer tmp = File_defiler(f);
        f->liberer(tmp);
    }
    free(f);
    f = NULL;
}