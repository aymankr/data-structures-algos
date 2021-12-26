#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gtest/gtest.h"

extern "C"
{
#include "queue.h"
#include "person.h"
}

void function_free_person(gpointer v)
{
    free_person((struct Person *)v);
}

void function_display_person(gpointer v)
{
    display_person((const struct Person *)v);
}

TEST(QueueTest, init_free)
{
    Queue_s *f = Queue_create(function_display_person, function_free_person);
    EXPECT_FALSE(f == NULL);
    Queue_free(f);
}

TEST(QueueTest, push)
{
    Queue_s *f = Queue_create(function_display_person, function_free_person);
    for (int i = 0; i < 5; i++)
    {
        struct Person *p = create_person("name", "fname", 2000 + i, i, i);
        Enqueue(f, p);
    }

    // verifie qu'ils ont été push
    for (int i = 0; i < 5; i++)
    {
        struct Person *rem = (struct Person *)Dequeue(f);
        ASSERT_STREQ(rem->name, "name");
        ASSERT_STREQ(rem->firstname, "fname");
        EXPECT_TRUE(rem->birth.year == 2000 + i);
        EXPECT_TRUE(rem->birth.month == i);
        EXPECT_TRUE(rem->birth.day == i);
        function_free_person(rem);
    }

    Queue_free(f);
}

TEST(QueueTest, pop)
{
    Queue_s *f = Queue_create(function_display_person, function_free_person);
    for (int i = 0; i < 5; i++)
    {
        struct Person *p = create_person("name", "fname", 2000 + i, i, i);
        Enqueue(f, p);
    }

    EXPECT_TRUE(Queue_length(f) == 5);
    struct Person *rem = (struct Person *)Dequeue(f);
    EXPECT_TRUE(Queue_length(f) == 4);

    function_free_person(rem);
    Queue_free(f);
}

TEST(QueueTest, drop)
{
    Queue_s *f = Queue_create(function_display_person, function_free_person);
    for (int i = 0; i < 5; i++)
    {
        struct Person *p = create_person("name", "fname", 2000 + i, i, i);
        Enqueue(f, p);
    }
    EXPECT_TRUE(!Queue_empty(f));

    for (int i = 0; i < 5; i++)
    {
        struct Person *rem = (struct Person *)Dequeue(f);
        function_free_person(rem);
    }

    EXPECT_TRUE(Queue_empty(f));
    Queue_free(f);
}

TEST(QueueTest, empty)
{
    Queue_s *f = Queue_create(function_display_person, function_free_person);
    EXPECT_TRUE(Queue_empty(f));

    for (int i = 0; i < 5; i++)
    {
        struct Person *p = create_person("name", "fname", 2000 + i, i, i);
        Enqueue(f, p);
    }
    EXPECT_TRUE(!Queue_empty(f));

    Queue_free(f);
}

TEST(QueueTest, length)
{
    Queue_s *f = Queue_create(function_display_person, function_free_person);
    EXPECT_TRUE(Queue_length(f) == 0);

    for (int i = 0; i < 5; i++)
    {
        struct Person *p = create_person("name", "fname", 2000 + i, i, i);
        Enqueue(f, p);
    }
    EXPECT_TRUE(Queue_length(f) == 5);

    for (int i = 0; i < 5; i++)
    {
        struct Person *rem = (struct Person *)Dequeue(f);
        function_free_person(rem);
    }
    EXPECT_TRUE(Queue_length(f) == 0);
    Queue_free(f);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
