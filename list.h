#ifndef List_H
#define List_H
#include "stdbool.h"

typedef struct List_s List_t;

typedef void *gpointer;
typedef void (*function_display)(gpointer g);
typedef void (*function_free)(gpointer g);
typedef int (*function_compare)(gpointer g1, gpointer g2);
typedef void (*function_modify)(gpointer g1, gpointer g2);
void List_display(const List_t *l);
List_t *List_create(function_display display, function_free free, function_compare compare,
                    function_modify modify);
void List_insert(List_t *l, gpointer g);
gpointer List_remove(List_t *l, gpointer g);
unsigned int List_length(const List_t *l);
void List_modify(List_t *l, gpointer g, gpointer new_g);
bool List_empty(const List_t *l);
void List_free(List_t *l);

#endif
