#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "assert.h"

void fonction_liberer_int(void *ptr_valeur)
{
    free(ptr_valeur);
}

void fonction_liberer_char(void *ptr_valeur)
{
    free(ptr_valeur);
}

void fonction_afficher_int(void *ptr_valeur)
{
    printf("->%d", *(int *)ptr_valeur);
}

void fonction_afficher_char(void *ptr_valeur)
{
    printf("->%s", (char *)ptr_valeur);
}

int main(int argc, char **argv, char **argenv)
{
    // Afficher, libérer int
    File_t *f = File_creer(fonction_afficher_int, fonction_liberer_int);
    
    int *v1 = malloc(sizeof(int));
    int *v2 = malloc(sizeof(int));
    int *v3 = malloc(sizeof(int));

    *v1 = 2; 
    *v2 = 3;
    *v3 = 4;
    
    File_enfiler(f, v1);
    File_enfiler(f, v2);
    File_enfiler(f, v3);
    File_afficher(f);
    File_liberer(f);

    // Afficher char
    File_t *f2 = File_creer(fonction_afficher_char, fonction_liberer_char);
    
    char *v4 = malloc(sizeof(char));
    char *v5 = malloc(sizeof(char));
    char *v6 = malloc(sizeof(char));

    v4 = "a"; 
    v5 = "b";
    v6 = "c";
    
    File_enfiler(f2, v4);
    File_enfiler(f2, v5);
    File_enfiler(f2, v6);
    File_afficher(f2);
    File_liberer(f2);

    return EXIT_SUCCESS;
}