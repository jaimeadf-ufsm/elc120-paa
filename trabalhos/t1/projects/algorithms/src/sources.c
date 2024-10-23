#include <stdlib.h>

#include "sources.h"

void consume_ascending(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = i;
    }
}

void consume_descending(int *array, int size)
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