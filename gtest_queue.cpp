#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gtest/gtest.h"

extern "C"
{
#include "queue.h"
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

TEST(QueueTest, init_free)
{
    Queue_s *f = Queue_create(function_display_personne, function_free_personne);
    EXPECT_FALSE(f == NULL);
    Queue_free(f);
}

TEST(QueueTest, push)
{
    Queue_s *f = Queue_create(function_display_personne, function_free_personne);
    for (int i = 0; i < 5; i++)
    {
        struct Personne *p = create_personne("name", "fname", 2000 + i, i, i);
        Queue_insert(f, p);
    }

    // verifie qu'ils ont été push
    for (int i = 0; i < 5; i++)
    {
        struct Personne *rem = (struct Personne *)Queue_remove(f);
        ASSERT_STREQ(rem->nom, "name");
        ASSERT_STREQ(rem->prenom, "fname");
        EXPECT_TRUE(rem->naissance.annee == 2000 + i);
        EXPECT_TRUE(rem->naissance.mois == i);
        EXPECT_TRUE(rem->naissance.jour == i);
        function_free_personne(rem);
    }

    Queue_free(f);
}

TEST(QueueTest, pop)
{
    Queue_s *f = Queue_create(function_display_personne, function_free_personne);
    for (int i = 0; i < 5; i++)
    {
        struct Personne *p = create_personne("name", "fname", 2000 + i, i, i);
        Queue_insert(f, p);
    }

    EXPECT_TRUE(Queue_length(f) == 5);
    struct Personne *rem = (struct Personne *)Queue_remove(f);
    EXPECT_TRUE(Queue_length(f) == 4);

    function_free_personne(rem);
    Queue_free(f);
}

TEST(QueueTest, drop)
{
    Queue_s *f = Queue_create(function_display_personne, function_free_personne);
    for (int i = 0; i < 5; i++)
    {
        struct Personne *p = create_personne("name", "fname", 2000 + i, i, i);
        Queue_insert(f, p);
    }
    EXPECT_TRUE(!Queue_empty(f));

    for (int i = 0; i < 5; i++)
    {
        struct Personne *rem = (struct Personne *)Queue_remove(f);
        function_free_personne(rem);
    }

    EXPECT_TRUE(Queue_empty(f));
    Queue_free(f);
}

TEST(QueueTest, empty)
{
    Queue_s *f = Queue_create(function_display_personne, function_free_personne);
    EXPECT_TRUE(Queue_empty(f));

    for (int i = 0; i < 5; i++)
    {
        struct Personne *p = create_personne("name", "fname", 2000 + i, i, i);
        Queue_insert(f, p);
    }
    EXPECT_TRUE(!Queue_empty(f));

    Queue_free(f);
}

TEST(QueueTest, length)
{
    Queue_s *f = Queue_create(function_display_personne, function_free_personne);
    EXPECT_TRUE(Queue_length(f) == 0);

    for (int i = 0; i < 5; i++)
    {
        struct Personne *p = create_personne("name", "fname", 2000 + i, i, i);
        Queue_insert(f, p);
    }
    EXPECT_TRUE(Queue_length(f) == 5);

    for (int i = 0; i < 5; i++)
    {
        struct Personne *rem = (struct Personne *)Queue_remove(f);
        function_free_personne(rem);
    }
    EXPECT_TRUE(Queue_length(f) == 0);
    Queue_free(f);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
