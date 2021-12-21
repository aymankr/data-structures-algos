#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <assert.h>

struct Cell_s
{
    gpointer value;
    struct Cell_s *prev;
    struct Cell_s *next;
};

struct List_s
{
    struct Cell_s *first;
    struct Cell_s *List;
    unsigned int length;
    ptr_function_display display;
    ptr_function_free free;
};

List_t *List_create(ptr_function_display display, ptr_function_free free)
{
    List_t *f = malloc(sizeof(struct List_s));
    f->List = NULL;
    f->first = NULL;
    f->length = 0;
    f->display = display;
    f->free = free;
    return f;
}

struct Cell_s *Cell_create()
{
    struct Cell_s *Cell = malloc(sizeof(struct Cell_s));
    Cell->prev = NULL;
    Cell->next = NULL;
    Cell->value = NULL;
    return Cell;
}

void List_insert(List_t *f, gpointer v)
{

}

void List_display(const List_t *f)
{

}

gpointer List_remove(List_t *f)
{

}

unsigned int List_length(const List_t *f)
{

}

bool List_empty(const List_t *f)
{

}

void List_free(List_t *f)
{

}