#ifndef QUEUE_H
#define QUEUE_H
#include "stdbool.h"

typedef struct Queue_s Queue_t;

typedef void* gpointer;
typedef void ( *function_display ) ( gpointer data );
typedef void ( *function_free ) ( gpointer data );
void Queue_display(const Queue_t *l);
Queue_t *Queue_create(function_display display, function_free free);
void Enqueue(Queue_t *l, gpointer g);
gpointer Dequeue(Queue_t *l);
unsigned int Queue_length(const Queue_t *l);
bool Queue_empty(const Queue_t *l);
void Queue_free(Queue_t *l);

#endif
