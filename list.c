#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct Addr
{
    gpointer value;
    struct Addr *prev, *next;
};

struct List_s
{
    struct Addr *head, *queue;
    unsigned int length;
    function_display display;
    function_free free;
    function_compare compare;
    function_modify modify;
};

/**
 * @brief Construct a file
 *
 * @param display function display
 * @param lree function free
 * @param compare function compare
 * @return List_t*
 */
List_t *List_create(function_display display, function_free free, function_compare compare,
                    function_modify modify)
{
    List_t *l = malloc(sizeof(struct List_s));
    l->queue = l->head = NULL;
    l->length = 0;
    l->display = display;
    l->free = free;
    l->compare = compare;
    l->modify = modify;
    return l;
}

/**
 * @brief Construct an address
 *
 * @param g value
 * @return struct Addr*
 */
struct Addr *address_create(gpointer g)
{
    struct Addr *address = malloc(sizeof(struct Addr));
    address->prev = address->next = NULL;
    address->value = g;
    return address;
}

/**
 * @brief Get the last address of the list (not the head)
 *
 * @param l
 * @return struct Addr*
 */
struct Addr *List_get_last(List_t *l)
{
    struct Addr *a = l->head;
    while (a->next != NULL)
    {
        a = a->next;
    }
    return a;
}

/**
 * @brief Get position of an address in the ordered list, depending of the value
 * return the previous address of the value that will be inserted
 *
 * @param l list
 * @param g value
 * @return struct Addr*
 */
struct Addr *List_get_address_inferior(List_t *l, gpointer g)
{
    if (!List_empty(l))
    {
        struct Addr *a = l->head;
        while (a != NULL)
        {
            if (l->compare(g, a->value) > 0)
            {
                return a->prev;
            }
            a = a->next;
        }
        return List_get_last(l); // case where we insert an element after the last
    }
    return NULL;
}

/**
 * @brief Get the first address position of the same value
 *
 * @param l list
 * @param g value
 * @return struct Addr*
 */
struct Addr *List_get_addr_same(List_t *l, gpointer g)
{
    if (!List_empty(l))
    {
        struct Addr *a = l->head;
        while (a != NULL)
        {
            if (l->compare(a->value, g) == 0)
                return a;
            a = a->next;
        }
    }
    return NULL;
}

/**
 * @brief Modify value of an address by a new value
 *
 * @param l list
 * @param g current value
 * @param new_value new value
 */
void List_modify(List_t *l, gpointer g, gpointer new_value)
{
    struct Addr *a = List_get_addr_same(l, g);
    l->modify(a->value, new_value);
}
/**
 * @brief Insert value in the head of the list
 * if the list has at least 1 element, insert the address before the head
 * else the address queue equals to the address value
 *
 * @param l list
 * @param g value
 */
void List_insert_head(List_t *l, gpointer g)
{
    struct Addr *a = address_create(g);
    a->next = l->head;

    if (l->length++ > 0)
    {
        l->head->prev = a;
    }
    else
    {
        l->queue = a;
    }

    l->head = a;
}

/**
 * @brief Insert value after the previous address
 * if there is 1 element, insert in the head
 * else set the previous of the next address being a
 * set the next of the previous at a
 *
 * @param l list
 * @param g value
 * @param previous previous address
 */
void List_insert_after(List_t *l, gpointer g, struct Addr *previous)
{
    struct Addr *a = address_create(g);
    a->next = previous->next;
    a->prev = previous;

    if (l->length++ == 1)
    {
        l->queue = l->head = a;
    }
    else if (previous->next != NULL)
    {
        a->next->prev = a;
    }

    previous->next = a;
}

/**
 * @brief Insert value
 * in the good position if the address exists, else insert in the head
 *
 * @param l list
 * @param g value
 */
void List_insert(List_t *l, gpointer g)
{
    struct Addr *a = List_get_address_inferior(l, g);
    if (a != NULL)
    {
        List_insert_after(l, g, a);
    }
    else
    {
        List_insert_head(l, g);
    }
    printf("\n--- INSERT ---\n");
    List_display(l);
}

/**
 * @brief Display values of a list
 *
 * @param l list
 */
void List_display(const List_t *l)
{
    struct Addr *a = l->head;
    while (a != NULL)
    {
        l->display(a->value);
        a = a->next;
    }
    printf("--------------\n");
}

/**
 * @brief Remove the head of the list
 *
 * @param l list
 * @return gpointer
 */
gpointer List_remove_head(List_t *l)
{
    struct Addr *a = l->head;
    l->head = a->next;
    gpointer removed = a->value;
    free(a);
    l->length--;
    return removed;
}

/**
 * @brief Remove an address positionned after the "previous"
 *
 * @param l list
 * @param previous previous address
 * @return gpointer
 */
gpointer List_remove_after(List_t *l, struct Addr *previous)
{
    struct Addr *a = previous->next; // address value to remove
    if (a->prev != NULL)
    {
        a->prev->next = a->next;
    }
    if (a->next != NULL)
    {
        a->next->prev = a->prev;
    }
    else
    {
        l->queue = a->prev;
    }
    gpointer removed = a->value;
    l->length--;
    free(a);
    return removed;
}

/**
 * @brief Remove a value in the list
 * Get the address from the value
 * if this value doesn't correspond to the head remove address positionned after his previous
 * else remove the head
 *
 * @param l
 * @param g
 * @return gpointer
 */
gpointer List_remove(List_t *l, gpointer g)
{
    gpointer removed = NULL;
    struct Addr *a = List_get_addr_same(l, g);

    if (a != NULL)
    {
        if (a != l->head)
        {
            removed = List_remove_after(l, a->prev);
        }
        else
        {
            removed = List_remove_head(l);
        }
    }
    printf("\n--- REMOVE ---\n");
    List_display(l);
    return removed;
}

/**
 * @brief Get the length of the list
 *
 * @param l list
 * @return unsigned int
 */
unsigned int List_length(const List_t *l)
{
    return l->length;
}

/**
 * @brief Verify if the list is empty
 *
 * @param l list
 * @return true
 * @return false
 */
bool List_empty(const List_t *l)
{
    return List_length(l) == 0;
}

/**
 * @brief Memory free of all the addresss of a list, and free the list
 *
 * @param l list
 */
void List_free(List_t *l)
{
    struct Addr *a = l->head;
    while (a != NULL)
    {
        l->free(a->value);
        struct Addr *tmp = a->next;
        free(a);
        a = tmp;
    }
    free(l);
    l = NULL;
}