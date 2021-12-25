#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gtest/gtest.h"

extern "C"
{
#include "list.h"
#include "personne.h"
}

void function_free_personne(gpointer v)
{
    free_personne((struct Personne *)v);
}

void function_display_personne(gpointer v)
{
    display_personne((const struct Personne *)v);
}

/**
 * @brief Compare two "personne"'s birth year
 *
 * @param v1 personne 1
 * @param v2 personne 2
 * @return int
 */
int function_compare_personne(gpointer v1, gpointer v2)
{
    struct Personne *p1 = (struct Personne *)v1;
    struct Personne *p2 = (struct Personne *)v2;

    if (p1->naissance.annee > p2->naissance.annee)
    {
        return 1;
    }
    else if (p1->naissance.annee < p2->naissance.annee)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

TEST(ListTest, init_free)
{
    List_s *f = List_create(function_display_personne, function_free_personne, function_compare_personne);
    EXPECT_TRUE(f != NULL);
    List_free(f);
}

TEST(ListTest, push)
{
    List_s *f = List_create(function_display_personne, function_free_personne, function_compare_personne);

    // push
    struct Personne *p = create_personne("name", "fname", 2000, 1, 10);
    List_insert(f, p);
    EXPECT_TRUE(!List_empty(f));

    // verify if the element was pushed
    struct Personne *rem = (struct Personne *)List_remove(f, p);
    EXPECT_TRUE(p != NULL);
    EXPECT_TRUE(List_empty(f));

    function_free_personne(rem);
    List_free(f);
}

TEST(ListTest, pop)
{
    List_s *f = List_create(function_display_personne, function_free_personne, function_compare_personne);

    // push
    struct Personne *p = create_personne("name", "fname", 2000, 1, 10);
    List_insert(f, p);

    // not empty
    EXPECT_TRUE(List_length(f) == 1);

    // pop an unknown element
    struct Personne *p2 = create_personne("namae", "fzzzzz", 2200, 3, 11);
    struct Personne *rem = (struct Personne *)List_remove(f, p2);
    EXPECT_TRUE(rem == NULL);

    // pop an existing element
    struct Personne *rem2 = (struct Personne *)List_remove(f, p);
    EXPECT_TRUE(rem2 != NULL);

    // empty
    EXPECT_TRUE(List_empty(f));

    function_free_personne(p2);
    function_free_personne(rem2);

    List_free(f);
}

TEST(ListTest, drop)
{
    List_s *f = List_create(function_display_personne, function_free_personne, function_compare_personne);

    // push
    for (int i = 0; i < 5; i++)
    {
        struct Personne *p = create_personne("name", "fname", 2000 + i, i, i);
        List_insert(f, p);
    }
    EXPECT_TRUE(!List_empty(f));

    struct Personne *other = create_personne("insert", "order", 2002, 1, 1);
    List_insert(f, other);

    for (int i = 0; i < 5; i++)
    {
        struct Personne *p = create_personne("name", "fname", 2000 + i, i, i);
        struct Personne *rem = (struct Personne *)List_remove(f, p);
        EXPECT_TRUE(rem->naissance.annee == 2000 + i);
        EXPECT_TRUE(rem->naissance.mois == i);
        EXPECT_TRUE(rem->naissance.jour == i);
        function_free_personne(p);
        function_free_personne(rem);
    }

    EXPECT_TRUE(!List_empty(f));
    struct Personne *rem = (struct Personne *)List_remove(f, other);
    function_free_personne(rem);
    EXPECT_TRUE(List_empty(f));

    List_free(f);
}

TEST(ListTest, empty)
{
    List_s *f = List_create(function_display_personne, function_free_personne, function_compare_personne);
    for (int i = 0; i < 5; i++)
    {
        struct Personne *p1 = create_personne("name", "fname", 2000 + i, i, i);
        List_insert(f, p1);
    }
    EXPECT_TRUE(!List_empty(f)); // not empty
    for (int i = 0; i < 5; i++)
    {
        struct Personne *p2 = create_personne("name", "fname", 2000 + i, i, i);
        struct Personne *rem = (struct Personne *)List_remove(f, p2);
        function_free_personne(rem);
        function_free_personne(p2);
    }

    EXPECT_TRUE(List_empty(f)); // empty
    List_free(f);
}

TEST(ListTest, length)
{
    List_s *f = List_create(function_display_personne, function_free_personne, function_compare_personne);
    EXPECT_TRUE(List_length(f) == 0); // empty

    for (int i = 0; i < 5; i++) // push 5 times
    {
        struct Personne *p = create_personne("name", "fname", 2000 + i, i, i);
        List_insert(f, p);
    }
    EXPECT_TRUE(List_length(f) == 5); // length of 5

    // pop 5 times
    for (int i = 0; i < 5; i++)
    {
        struct Personne *p = create_personne("name", "fname", 2000 + i, i, i);
        struct Personne *rem = (struct Personne *)List_remove(f, p);
        function_free_personne(rem);
        function_free_personne(p);
    }

    EXPECT_TRUE(List_length(f) == 0); // empty
    List_free(f);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
