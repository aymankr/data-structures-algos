#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gtest/gtest.h"

extern "C"
{
#include "list.h"
#include "person.h"
}

void function_free_person(gpointer g)
{
    free_person((struct Person *)g);
}

void function_display_person(gpointer g)
{
    display_person((const struct Person *)g);
}

/**
 * @brief Compare two "Person"'s birth year
 *
 * @param g1 Person 1
 * @param g2 Person 2
 * @return int
 */
int function_compare_person(gpointer g1, gpointer g2)
{
    return compare_persons((const struct Person *)g1, (const struct Person *)g2);
}

void function_modify_person(gpointer g1, gpointer g2)
{
    modify_person((struct Person *)g1, (struct Person *)g2);
}

TEST(ListTest, init_free)
{
    List_s *l = List_create(function_display_person, function_free_person, function_compare_person,
                            function_modify_person);
    EXPECT_TRUE(l != NULL);
    List_free(l);
}

TEST(ListTest, push)
{
    List_s *l = List_create(function_display_person, function_free_person, function_compare_person,
                            function_modify_person);

    // push
    struct Person *p = create_person("name", "fname", 2000, 1, 10);
    List_insert(l, p);
    EXPECT_TRUE(!List_empty(l));

    // verify if the element was pushed
    struct Person *rem = (struct Person *)List_remove(l, p);
    EXPECT_TRUE(p != NULL);
    EXPECT_TRUE(List_empty(l));

    function_free_person(rem);
    List_free(l);
}

TEST(ListTest, pop)
{
    List_s *l = List_create(function_display_person, function_free_person, function_compare_person,
                            function_modify_person);

    // push
    struct Person *p = create_person("name", "fname", 2000, 1, 10);
    List_insert(l, p);

    // not empty
    EXPECT_TRUE(List_length(l) == 1);

    // pop an unknown element
    struct Person *p2 = create_person("namae", "fzzzzz", 2200, 3, 11);
    struct Person *rem = (struct Person *)List_remove(l, p2);
    EXPECT_TRUE(rem == NULL);

    // pop an existing element
    struct Person *rem2 = (struct Person *)List_remove(l, p);
    EXPECT_TRUE(rem2 != NULL);

    // empty
    EXPECT_TRUE(List_empty(l));

    function_free_person(p2);
    function_free_person(rem2);

    List_free(l);
}

TEST(ListTest, drop)
{
    List_s *l = List_create(function_display_person, function_free_person, function_compare_person,
                            function_modify_person);

    // push
    for (int i = 0; i < 5; i++)
    {
        struct Person *p1 = create_person("name", "fname", 2000 + i, i, i);
        List_insert(l, p1);
    }
    EXPECT_TRUE(!List_empty(l));

    struct Person *other = create_person("insert", "order", 2002, 1, 1);
    List_insert(l, other);

    for (int i = 0; i < 5; i++)
    {
        struct Person *p2 = create_person("name", "fname", 2000 + i, i, i);
        struct Person *rem = (struct Person *)List_remove(l, p2);
        EXPECT_TRUE(rem->birth.year == 2000 + i);
        EXPECT_TRUE(rem->birth.month == i);
        EXPECT_TRUE(rem->birth.day == i);
        function_free_person(p2);
        function_free_person(rem);
    }

    EXPECT_TRUE(!List_empty(l));
    struct Person *rem = (struct Person *)List_remove(l, other);
    function_free_person(rem);
    EXPECT_TRUE(List_empty(l));

    List_free(l);
}

TEST(ListTest, modify)
{
    List_s *l = List_create(function_display_person, function_free_person, function_compare_person,
                            function_modify_person);

    // create a Person
    struct Person *p1 = create_person("name", "fname", 2000, 1, 1);
    List_insert(l, p1);

    // modify p1 by p2
    struct Person *p2 = create_person("new", "n", 2015, 3, 4);
    List_modify(l, p1, p2);

    // remove p1 and verify if p1 has attributes of p2
    struct Person *newp1 = (struct Person *)List_remove(l, p1);
    ASSERT_STREQ(newp1->name, "new");
    EXPECT_TRUE(newp1->birth.year == 2015);

    function_free_person(newp1);
    function_free_person(p2);
    List_free(l);
}

TEST(ListTest, empty)
{
    List_s *l = List_create(function_display_person, function_free_person, function_compare_person,
                            function_modify_person);
    for (int i = 0; i < 5; i++)
    {
        struct Person *p1 = create_person("name", "fname", 2000 + i, i, i);
        List_insert(l, p1);
    }
    EXPECT_TRUE(!List_empty(l)); // not empty
    for (int i = 0; i < 5; i++)
    {
        struct Person *p2 = create_person("name", "fname", 2000 + i, i, i);
        struct Person *rem = (struct Person *)List_remove(l, p2);
        function_free_person(rem);
        function_free_person(p2);
    }

    EXPECT_TRUE(List_empty(l)); // empty
    List_free(l);
}

TEST(ListTest, length)
{
    List_s *l = List_create(function_display_person, function_free_person, function_compare_person,
                            function_modify_person);
    EXPECT_TRUE(List_length(l) == 0); // empty

    for (int i = 0; i < 5; i++) // push 5 times
    {
        struct Person *p = create_person("name", "fname", 2000 + i, i, i);
        List_insert(l, p);
    }
    EXPECT_TRUE(List_length(l) == 5); // length of 5

    // pop 5 times
    for (int i = 0; i < 5; i++)
    {
        struct Person *p = create_person("name", "fname", 2000 + i, i, i);
        struct Person *rem = (struct Person *)List_remove(l, p);
        function_free_person(rem);
        function_free_person(p);
    }

    EXPECT_TRUE(List_length(l) == 0); // empty
    List_free(l);
}

int main(int argc, char **argg)
{
    ::testing::InitGoogleTest(&argc, argg);
    return RUN_ALL_TESTS();
}
