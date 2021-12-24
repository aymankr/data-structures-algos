#ifndef List_H
#define List_H
#include "stdbool.h"

typedef struct List_s List_t;

typedef void * gpointer;
typedef void ( *ptr_function_display ) ( gpointer data );
typedef void ( *ptr_function_free ) ( gpointer data );
typedef int ( *ptr_function_compare ) ( gpointer data1, gpointer data2 );
void List_display(const List_t *f);
List_t *List_create(ptr_function_display display, ptr_function_free free, ptr_function_compare compare);
void List_insert(List_t *f, gpointer v);
gpointer List_remove(List_t *f, int index);
unsigned int List_length(const List_t *f);
bool List_empty(const List_t *f);
void List_free(List_t *f);

#endif
