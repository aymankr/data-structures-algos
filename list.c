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
    ptr_function_modify modify;
};

/**
 * @brief Construct a file
 *
 * @param display function display
 * @param free function free
 * @param compare function compare
 * @return List_t*
 */
List_t *List_create(ptr_function_display display, ptr_function_free free, ptr_function_compare compare,
                    ptr_function_modify modify)
{
    List_t *f = malloc(sizeof(struct List_s));
    f->queue = f->head = NULL;
    f->length = 0;
    f->display = display;
    f->free = free;
    f->compare = compare;
    f->modify = modify;
    return f;
}

/**
 * @brief Construct a cell
 *
 * @param v value
 * @return struct Cell_s*
 */
struct Cell_s *Cell_create(gpointer v)
{
    struct Cell_s *Cell = malloc(sizeof(struct Cell_s));
    Cell->prev = Cell->next = NULL;
    Cell->value = v;
    return Cell;
}

/**
 * @brief Get position of a cell in the ordered list, depending of the value
 * return the previous cell of the value that will be inserted
 *
 * @param f list
 * @param v value
 * @return struct Cell_s*
 */
struct Cell_s *List_get_cell_inferior(List_t *f, gpointer v)
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

/**
 * @brief Get the first cell position of the same value
 *
 * @param f list
 * @param v value
 * @return struct Cell_s*
 */
struct Cell_s *List_get_cell_same(List_t *f, gpointer v)
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

/**
 * @brief Modify value of a cell by a new value
 *
 * @param f list
 * @param value current value
 * @param new_value new value
 */
void List_modify(List_t *f, gpointer value, gpointer new_value)
{
    struct Cell_s *c = List_get_cell_same(f, value);
    f->modify(c->value, new_value);
}
/**
 * @brief Insert value in the head of the list
 * if the list has at least 1 element, insert the cell before the head
 * else the cell queue equals to the cell value
 *
 * @param f list
 * @param v value
 */
void List_insert_head(List_t *f, gpointer v)
{
    struct Cell_s *c = Cell_create(v);
    c->next = f->head;

    if (List_length(f) > 0)
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

/**
 * @brief Insert value after the previous cell
 * if there is 1 element, insert in the head
 * else set the previous of the next cell being c
 * set the next of the previous at c
 *
 * @param f list
 * @param v value
 * @param previous previous cell
 */
void List_insert_after(List_t *f, gpointer v, struct Cell_s *previous)
{
    struct Cell_s *c = Cell_create(v);
    c->next = previous->next;
    c->prev = previous;

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

/**
 * @brief Insert value in the head if the cell doesn't exist, else insert
 * in the good position
 *
 * @param f list
 * @param v value
 */
void List_insert(List_t *f, gpointer v)
{
    struct Cell_s *previous = List_get_cell_inferior(f, v);
    if (previous == NULL)
    {
        List_insert_head(f, v);
    }
    else
    {
        List_insert_after(f, v, previous);
    }
    printf("\n--- INSERT ---\n");
    List_display(f);
}

/**
 * @brief Display values of a list
 *
 * @param f list
 */
void List_display(const List_t *f)
{
    struct Cell_s *c = f->head;
    while (c != NULL)
    {
        f->display(c->value);
        c = c->next;
    }
    printf("--------------\n");
}

/**
 * @brief Remove the head of the list
 *
 * @param f list
 * @return gpointer
 */
gpointer List_remove_head(List_t *f)
{
    struct Cell_s *c = f->head;
    f->head = c->next;
    gpointer removed = c->value;
    free(c);
    f->length--;
    return removed;
}

/**
 * @brief Remove a cell positionned after the "previous"
 *
 * @param f list
 * @param previous previous cell
 * @return gpointer
 */
gpointer List_remove_after(List_t *f, struct Cell_s *previous)
{
    struct Cell_s *c = previous->next; // cell to remove
    c->prev->next = c->next;
    gpointer removed = c->value;
    f->length--;
    free(c);
    return removed;
}

/**
 * @brief Remove a cell in the list
 * Get the cell from the value
 * if this value correspond to the head remove the head
 * else remove cell positionned after his previous
 *
 * @param f
 * @param v
 * @return gpointer
 */
gpointer List_remove(List_t *f, gpointer v)
{
    gpointer removed = NULL;
    struct Cell_s *c = List_get_cell_same(f, v);

    if (c != NULL && c == f->head)
    {
        removed = List_remove_head(f);
    }
    else if (c != NULL)
    {
        removed = List_remove_after(f, c->prev);
    }
    printf("\n--- REMOVE ---\n");
    List_display(f);
    return removed;
}

/**
 * @brief Get the length of the list
 *
 * @param f list
 * @return unsigned int
 */
unsigned int List_length(const List_t *f)
{
    return f->length;
}

/**
 * @brief Verify if the list is empty
 *
 * @param f list
 * @return true
 * @return false
 */
bool List_empty(const List_t *f)
{
    return List_length(f) == 0;
}

/**
 * @brief Memory free of all the cells of a list, and free the list
 *
 * @param f list
 */
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