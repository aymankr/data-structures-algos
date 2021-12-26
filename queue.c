#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct Addr_s
{
    gpointer value;
    struct Addr_s *prev, *next;
};

struct Queue_s
{
    struct Addr_s *head, *queue;
    unsigned int length;
    function_display display;
    function_free free;
};

/**
 * @brief Construct a queue
 *
 * @param display function display
 * @param free function free
 * @return Queue_t*
 */
Queue_t *Queue_create(function_display display, function_free free)
{
    Queue_t *f = malloc(sizeof(struct Queue_s));
    f->queue = f->head = NULL;
    f->length = 0;
    f->display = display;
    f->free = free;
    return f;
}

/**
 * @brief Construct an address
 *
 * @param g value
 * @return struct Addr_s*
 */
struct Addr_s *address_create(gpointer g)
{
    struct Addr_s *address = malloc(sizeof(struct Addr_s));
    address->prev = address->next = NULL;
    address->value = g;
    return address;
}

/**
 * @brief Insert an address in the queue
 * if the queue is not empty, insert before the head
 * else insert the first element in the head
 *
 * @param f queue
 * @param g value
 */
void Enqueue(Queue_t *f, gpointer g)
{
    struct Addr_s *c = address_create(g);
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

/**
 * @brief Display values of a queue
 *
 * @param f queue
 */
void Queue_display(const Queue_t *f)
{
    struct Addr_s *c = f->head;
    while (c != NULL)
    {
        f->display(c->value);
        c = c->next;
    }
    printf("NULL\n");
}

/**
 * @brief Remove the head address of the queue if there is at least 1 element
 * if there is only 1 address, set the head and the queue at NULL
 * else remove the head by replacing the address queue by the previous address queue
 *
 * @param f queue
 * @return gpointer
 */
gpointer Dequeue(Queue_t *f)
{
    gpointer g = f->queue->value;
    struct Addr_s *tmp = f->queue;

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
    return g;
}

/**
 * @brief Get length of a queue
 *
 * @param f queue
 * @return unsigned int
 */
unsigned int Queue_length(const Queue_t *f)
{
    return f->length;
}

/**
 * @brief Verify if a queue is empty
 *
 * @param f queue
 * @return true
 * @return false
 */
bool Queue_empty(const Queue_t *f)
{
    return f->length == 0;
}

/**
 * @brief Free pointer values of the queue, free the queue
 *
 * @param f queue
 */
void Queue_free(Queue_t *f)
{
    while (!Queue_empty(f))
    {
        gpointer g = Dequeue(f);
        f->free(g);
    }
    free(f);
    f = NULL;
}