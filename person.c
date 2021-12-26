#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "person.h"

void free_person(struct Person *p)
{
    free(p->name);
    free(p->firstname);
    p->name = p->firstname = NULL;
    free(p);
    p = NULL;
}

void display_person(const struct Person *p)
{
    printf("%s %s %d %d %d\n", p->name, p->firstname, p->birth.year, p->birth.month,
           p->birth.day);
}

struct Person *create_person(const char *name, const char *fname, int year, int month, int day)
{
    struct Person *p = (struct Person *)malloc(sizeof(struct Person));
    p->birth.year = year;
    p->birth.day = day;
    p->birth.month = month;
    p->name = strdup(name);
    p->firstname = strdup(fname);
    return p;
}

int compare_persons(const struct Person *p1, const struct Person *p2)
{
    if (p2->birth.year > p1->birth.year)
    {
        return 1;
    }
    else if (p2->birth.year < p1->birth.year)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void modify_person(struct Person *p1, struct Person *p2)
{
    p1->birth.year = p2->birth.year;
    p1->birth.day = p2->birth.day;
    p1->birth.month = p2->birth.month;
    free(p1->name);
    free(p1->firstname);
    p1->name = strdup(p2->name);
    p1->firstname = strdup(p2->firstname);
}