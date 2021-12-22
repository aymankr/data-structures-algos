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
    EXPECT_FALSE(f == NULL);
    List_free(f);
}

TEST(ListTest, push)
{
    List_s *f = List_create(function_display_personne, function_free_personne, function_compare_personne);
    struct Personne *p = create_personne("name", "fname", 2000, 1, 10);
    List_insert(f, p);

    struct Personne *rem = (struct Personne *)List_remove(f, p);
    EXPECT_TRUE(p != NULL);

    List_free(f);
}

TEST(ListTest, pop)
{
    List_s *f = List_create(function_display_personne, function_free_personne, function_compare_personne);
    struct Personne *p = create_personne("name", "fname", 2000, 1, 10);
    List_insert(f, p);

    EXPECT_TRUE(List_length(f) == 1);

    struct Personne *p2 = create_personne("name", "fzzzzz", 2200, 1, 10);
    struct Personne *rem = (struct Personne *)List_remove(f, p2);
    EXPECT_TRUE(rem == NULL);
    EXPECT_TRUE(!List_empty(f));

    struct Personne *rem2 = (struct Personne *)List_remove(f, p);
    EXPECT_TRUE(rem2 != NULL);
    EXPECT_TRUE(List_empty(f));

    List_free(f);
}

TEST(ListTest, drop)
{
    List_s *f = List_create(function_display_personne, function_free_personne, function_compare_personne);
    for (int i = 0; i < 5; i++)
    {
        struct Personne *p = create_personne("name", "fname", 2000 + i, i, i);
        List_insert(f, p);
    }
    EXPECT_TRUE(!List_empty(f));

    for (int i = 0; i < 5; i++)
    {
        struct Personne *p = create_personne("name", "fname", 2000 + i, i, i);
        struct Personne *tmp = (struct Personne *)List_remove(f, p);
        ASSERT_STREQ(tmp->nom, "name");
        function_free_personne(p);
    }
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
    EXPECT_TRUE(!List_empty(f));

    for (int i = 0; i < 5; i++)
    {
        struct Personne *p2 = create_personne("name", "fname", 2000 + i, i, i);
        struct Personne *tmp = (struct Personne *)List_remove(f, p2);
        function_free_personne(p2);
    }

    EXPECT_TRUE(List_empty(f));
    List_free(f);
}

TEST(ListTest, length)
{
    List_s *f = List_create(function_display_personne, function_free_personne, function_compare_personne);
    EXPECT_TRUE(List_length(f) == 0);
    for (int i = 0; i < 5; i++)
    {
        struct Personne *p = create_personne("name", "fname", 2000 + i, i, i);
        List_insert(f, p);
    }
    EXPECT_TRUE(List_length(f) == 5);

    for (int i = 0; i < 5; i++)
    {
        struct Personne *p = create_personne("name", "fname", 2000 + i, i, i);
        struct Personne *tmp = (struct Personne *)List_remove(f, p);
        function_free_personne(p);
    }

    EXPECT_TRUE(List_length(f) == 0);
    List_free(f);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
