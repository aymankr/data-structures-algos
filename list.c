#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <assert.h>
#include "personne.h"

struct Cell_s
{
    gpointer value;
    struct Cell_s *prev, *next;
};

struct List_s
{
    struct Cell_s *head, *queue;
    unsigned int length;
    ptr_function_display display;
    ptr_function_free free;
    ptr_function_compare compare;
};

List_t *List_create(ptr_function_display display, ptr_function_free free, ptr_function_compare compare)
{
    List_t *f = malloc(sizeof(struct List_s));
    f->queue = f->head = NULL;
    f->length = 0;
    f->display = display;
    f->free = free;
    f->compare = compare;
    return f;
}

struct Cell_s *Cell_create(gpointer v)
{
    struct Cell_s *Cell = malloc(sizeof(struct Cell_s));
    Cell->prev = Cell->next = NULL;
    Cell->value = v;
    return Cell;
}

struct Cell_s *List_get_position(List_t *f, gpointer v)
{
    if (!List_empty(f))
    {
        struct Cell_s *c = f->head;
        while (c != NULL)
        {
            if (f->compare(c->value, v) > 0)
                return c->prev;
            c = c->next;
        }
    }
    return NULL;
}

struct Cell_s *List_get_element(List_t *f, gpointer v)
{
    if (!List_empty(f))
    {
        struct Cell_s *c = f->head;
        while (c != NULL)
        {
            if (f->compare(c->value, v) == 0)
                return c;
            c = c->next;
        }
    }
    return NULL;
}

void List_insert_head(List_t *f, gpointer v)
{
    struct Cell_s *c = Cell_create(v);
    c->next = f->head;

    if (f->head != NULL)
    {
        f->head->prev = c;
    }
    else
    {
        f->queue = c;
    }

    f->head = c;
    f->length++;
}

void List_insert_position(List_t *f, gpointer v, struct Cell_s *previous)
{

    struct Cell_s *c = Cell_create(v);
    c->prev = previous;
    c->next = previous->next;

    if (List_length(f) == 1)
    {
        f->queue = f->head = c;
    }
    else
    {
        c->next->prev = c;
    }

    previous->next = c;
    f->length++;
}

void List_insert(List_t *f, gpointer v)
{
    struct Cell_s *c = List_get_element(f, v);
    if (c == NULL)
    {
        List_insert_head(f, v);
    }
    else
    {
        List_insert_position(f, v, c);
    }
    List_display(f);
}

void List_display(const List_t *f)
{
    struct Cell_s *c = f->head;
    while (c != NULL)
    {
        f->display(c->value);
        c = c->next;
    }
    printf("NULL\n");
}

gpointer List_remove(List_t *f, gpointer v)
{
    struct Cell_s *c = List_get_element(f, v);

    if (c != NULL)
    {
        if (c->prev != NULL)
        {
            c->prev->next = c->next;
        }
        else
        {
            f->head = c->next;
        }
        if (c->next != NULL)
        {
            c->next->prev = c->prev;
        }
        else
        {
            f->queue = c->prev;
        }
    }
    else
    {
        return NULL;
    }

    gpointer removed = c->value;
    free(c);
    f->length--;

    return removed;
}

unsigned int List_length(const List_t *f)
{
    return f->length;
}

bool List_empty(const List_t *f)
{
    return List_length(f) == 0;
}

void List_free(List_t *f)
{
    struct Cell_s *c = f->head;
    while (c != NULL)
    {
        f->free(c);
        c = c->next;
    }
    free(f);
    f = NULL;
}