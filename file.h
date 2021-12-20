#ifndef FILE_H
#define FILE_H

typedef struct File_s File_t;

typedef void * gpointer;
typedef void ( *ptr_fonction_afficher ) ( gpointer data );
typedef void ( *ptr_fonction_liberer ) ( gpointer data );
void File_afficher(const File_t *f);
File_t *File_creer(ptr_fonction_afficher afficher, ptr_fonction_liberer liberer);
void File_enfiler(File_t *f, gpointer v);
gpointer File_defiler(File_t *f);
int File_taille(const File_t *f);
int File_vide(const File_t *f); // bool = 1 ou 0
void File_liberer(File_t *f);

#endif
