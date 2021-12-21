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
    struct Cell_s *head;
    struct Cell_s *List;
    unsigned int length;
    ptr_function_display display;
    ptr_function_free free;
    ptr_function_compare compare;
};

List_t *List_create(ptr_function_display display, ptr_function_free free, ptr_function_compare compare)
{
    List_t *f = malloc(sizeof(struct List_s));
    f->List = NULL;
    f->head = NULL;
    f->length = 0;
    f->display = display;
    f->free = free;
    f->compare = compare;
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

struct Cell_s *List_get_position(List_t *f, gpointer v)
{
    assert(f != NULL);
    struct Cell_s *c = f->head;

    while (c != NULL)
    {
        if (f->compare(c->value, v) > 0)
        {
            return c->prev;
        }
        c = c->next;
    }
    return f->List;
}

struct Cell_s *List_get_element(List_t *f, gpointer v)
{
    assert(f != NULL);
    struct Cell_s *c = f->head;

    while (c != NULL)
    {
        if (f->compare(c->value, v) == 0)
        {
            return c->prev;
        }
        c = c->next;
    }
    return NULL;
}

void List_insert_head(List_t *f, gpointer v)
{
    assert(f != NULL);
    assert(f->length > 0);
    struct Cell_s *c = Cell_create();
    c->value = v;
    c->next = f->head;

    if (List_length(f) != 1)
    {
        assert(f->head == NULL);
        f->head->prev = c;
    }
    else
    {
        f->List = c;
    }
    f->head = c;
    f->length++;
    List_display(f);
}

void List_insert_position(List_t *f, gpointer v)
{
    assert(f != NULL);
    assert(f->length > 0);
    struct Cell_s *c = List_get_position(f, v);

    if (List_length(f) != 1)
    {
        assert(f->head == NULL);
        f->head->prev = c;
    }
    else
    {
        f->List = c;
    }
    f->head = c;
    f->length++;
    List_display(f);
}

void List_display(const List_t *f)
{
    assert(f != NULL);
    assert(f->length > 0);
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
    assert(f != NULL);
    assert(f->length > 0);
    struct Cell_s *c = List_get_element(f, v);

    if (c == NULL)
    {
        return NULL;
    }
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
        f->List = c->prev;
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
    assert(f != NULL);
    if (f->length == 0)
    {
        assert(f->List == f->head == NULL);
    }
    return List_length(f) == 0;
}

void List_free(List_t *f)
{
    assert(f != NULL);
    struct Cell_s *c = f->head;
    while (!List_empty(f))
    {
    }
    free(f);
    f = NULL;
}