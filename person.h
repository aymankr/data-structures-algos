#ifndef Person_H
#define Person_H

struct Date
{
    int day, month, year;
};

struct Person
{
    char *name, *firstname;
    struct Date birth;
};

void free_person(struct Person *p);
void display_person(const struct Person *p);
struct Person *create_person(const char *name, const char *fname, int year, int month, int day);
int compare_persons(const struct Person *p1, const struct Person *p2);
void modify_person(struct Person *p1, struct Person *p2);

#endif
