#include <stdlib.h>

#include "sources.h"

void consume_ascendant(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = i;
    }
}

void consume_descendant(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = size - i;
    }
}

void consume_random(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = rand();
    }
}