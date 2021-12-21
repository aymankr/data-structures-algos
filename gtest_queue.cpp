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

/* ********** TEST INIT & FREE ********** */

TEST(FileTest, init_free)
{
    Queue_s *f = Queue_create(function_display_personne, function_free_personne);
    EXPECT_FALSE(f == NULL);
    Queue_free(f);
}

