#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "assert.h"

struct Cell_s
{
    gpointer value;
    struct Cell_s *prev, *next;
};

struct Queue_s
{
    struct Cell_s *head, *queue;
    unsigned int length;
    ptr_function_display display;
    ptr_function_free free;
};

Queue_t *Queue_create(ptr_function_display display, ptr_function_free free)
{
    Queue_t *f = malloc(sizeof(struct Queue_s));
    f->queue = f->head = NULL;
    f->length = 0;
    f->display = display;
    f->free = free;
    return f;
}

struct Cell_s *Cell_create(gpointer v)
{
    struct Cell_s *Cell = malloc(sizeof(struct Cell_s));
    Cell->prev = Cell->next = NULL;
    Cell->value = v;
    return Cell;
}

void Queue_insert(Queue_t *f, gpointer v)
{
    struct Cell_s *c = Cell_create(v);
    c->next = f->head;

    if (Queue_length(f) > 0)
    {
        f->head->prev = c;
    }
    else
    {
        f->queue = c;
    }
    f->head = c;
    f->length++;
    Queue_display(f);
}

void Queue_display(const Queue_t *f)
{
    struct Cell_s *c = f->head;
    while (c != NULL)
    {
        f->display(c->value);
        c = c->next;
    }
    printf("NULL\n");
}

gpointer Queue_remove(Queue_t *f)
{
    assert(Queue_length(f) > 0);
    gpointer v = f->queue->value;
    struct Cell_s *tmp = f->queue;

    if (Queue_length(f) == 1)
    {
        f->head = f->queue = NULL;
    }
    else
    {
        f->queue = tmp->prev;
    }
    free(tmp);
    tmp = NULL;
    f->length--;
    return v;
}

unsigned int Queue_length(const Queue_t *f)
{
    return f->length;
}

bool Queue_empty(const Queue_t *f)
{
    return f->length == 0;
}

void Queue_free(Queue_t *f)
{
    while (!Queue_empty(f))
    {
        gpointer v = Queue_remove(f);
        f->free(v);
    }
    free(f);
    f = NULL;
}