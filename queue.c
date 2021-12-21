#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <assert.h>

struct Cell_s
{
    gpointer value;
    struct Cell_s *prev;
    struct Cell_s *next;
};

struct Queue_s
{
    struct Cell_s *head;
    struct Cell_s *queue;
    unsigned int length;
    ptr_function_display display;
    ptr_function_free free;
};

Queue_t *Queue_create(ptr_function_display display, ptr_function_free free)
{
    Queue_t *f = malloc(sizeof(struct Queue_s));
    f->queue = NULL;
    f->head = NULL;
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

void Cell_free(struct Cell_s *c)
{
    free(c);
}

void Queue_insert(Queue_t *f, gpointer v)
{
    assert(f != NULL);
    struct Cell_s *c = Cell_create();
    c->value = v;
    c->next = f->head;

    if (f->head != NULL)
    {
        assert(f->head->prev == NULL);
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
    assert(f != NULL);
    struct Cell_s *current = f->head;
    while (current != NULL)
    {
        f->display(current->value);
        current = current->next;
    }
    printf("NULL\n");
}

gpointer Queue_remove(Queue_t *f)
{
    assert(f != NULL);
    assert(f->length > 0);

    gpointer v = f->queue->value;

    if (f->queue->prev == NULL)
    {
        assert(f->length == 1);
        free(f->queue);
        f->head = f->queue = NULL;
    }
    else
    {
        f->queue = f->queue->prev;
        free(f->queue->next);
        f->queue->next = NULL;
    }
    f->length--;
    return v;
}

unsigned int Queue_length(const Queue_t *f)
{
    assert(f != NULL);
    return f->length;
}

bool Queue_empty(const Queue_t *f)
{
    assert(f != NULL);
    if (f->length == 0)
    {
        assert(f->queue == NULL);
        assert(f->head == NULL);
    }
    return f->length == 0;
}

void Queue_free(Queue_t *f)
{
    assert(f != NULL);
    while (!Queue_empty(f))
    {
        gpointer tmp = Queue_remove(f);
        f->free(tmp);
    }
    free(f);
    f = NULL;
}