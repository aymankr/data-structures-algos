#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "assert.h"

void function_free_int(void *ptr_value)
{
    free(ptr_value);
}

void function_free_char(void *ptr_value)
{
    free(ptr_value);
}

void function_display_int(void *ptr_value)
{
    printf("%d->", *(int *)ptr_value);
}

void function_display_char(void *ptr_value)
{
    printf("%s->", (char *)ptr_value);
}

int main(void)
{
    // Afficher, libérer int
    Queue_t *f = Queue_create(function_display_int, function_free_int);

    int *v1 = malloc(sizeof(int));
    int *v2 = malloc(sizeof(int));
    int *v3 = malloc(sizeof(int));

    *v1 = 2;
    *v2 = 3;
    *v3 = 4;
    
    Queue_insert(f, v1);
    Queue_insert(f, v2);
    Queue_insert(f, v3);
    Queue_free(f);

    // Afficher char
    Queue_t *f2 = Queue_create(function_display_char, function_free_char);

    char *v4 = malloc(sizeof(char));
    char *v5 = malloc(sizeof(char));
    char *v6 = malloc(sizeof(char));

    v4 = "aa";
    v5 = "bbb";
    v6 = "cccc";

    Queue_insert(f2, v4);
    Queue_insert(f2, v5);
    Queue_insert(f2, v6);
    Queue_free(f2);

    return EXIT_SUCCESS;
}