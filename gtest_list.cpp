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
    //comparer_personne((const struct Personne *)v);
    return 0;
}

/* ********** TEST INIT & FREE ********** */

TEST(FileTest, init_free)
{
    List_s *f = List_create(function_display_personne, function_free_personne, function_compare_personne);
    EXPECT_FALSE(f == NULL);
    List_free(f);
}

TEST(FileTest, push)
{
    List_s *f = List_create(function_display_personne, function_free_personne, 0);
    for (int i = 0 ; i < 5;i++) {
        struct Personne* p =create_personne("name", "fname", 2000+i, 2000%30, 2000%12);
        List_insert(f, p);
    }

    struct Personne* unknown = create_personne("unknown", "name", 2012, 30, 3);
}

    

int main(int argc, char **argv)
{
    /* run google tests */
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
