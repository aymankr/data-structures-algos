#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "assert.h"
#include <string.h>

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

int function_compare_int(void *ptr_value1, void *ptr_value2)
{
    int v1 = *(int *)ptr_value1;
    int v2 = *(int *)ptr_value2;

    if (v1 > v2)
    {
        return 1;
    }
    else if (v1 < v2)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int function_compare_char(void *ptr_value1, void *ptr_value2)
{
    char *v1 = (char *)ptr_value1;
    char *v2 = (char *)ptr_value2;

    if (strlen(v1) > strlen(v2))
    {
        return 1;
    }
    else if (strlen(v1) < strlen(v2))
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int main(void)
{
    // Afficher, libérer int
    List_t *f = List_create(function_display_int, function_free_int, function_compare_int);

    int *v1 = malloc(sizeof(int));
    int *v2 = malloc(sizeof(int));
    int *v3 = malloc(sizeof(int));

    *v1 = 2;
    *v2 = 3;
    *v3 = 4;

    List_insert(f, v1);
    List_insert(f, v2);
    List_insert(f, v3);
    List_free(f);

    // Afficher char
    List_t *f2 = List_create(function_display_char, function_free_char, function_compare_char);

    char *v4 = malloc(sizeof(char));
    char *v5 = malloc(sizeof(char));
    char *v6 = malloc(sizeof(char));

    v4 = "aa";
    v5 = "bbb";
    v6 = "cc";

    List_insert(f2, v4);
    List_insert(f2, v5);
    List_insert(f2, v6);
    List_free(f2);

    return EXIT_SUCCESS;
}