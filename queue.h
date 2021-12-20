#ifndef QUEUE_H
#define QUEUE_H
#include "stdbool.h"

typedef struct Queue_s Queue_t;

typedef void * gpointer;
typedef void ( *ptr_function_display ) ( gpointer data );
typedef void ( *ptr_function_free ) ( gpointer data );
void Queue_display(const Queue_t *f);
Queue_t *Queue_create(ptr_function_display display, ptr_function_free free);
void Queue_insert(Queue_t *f, gpointer v);
gpointer Queue_remove(Queue_t *f);
unsigned int Queue_length(const Queue_t *f);
bool Queue_empty(const Queue_t *f);
void Queue_free(Queue_t *f);

#endif
