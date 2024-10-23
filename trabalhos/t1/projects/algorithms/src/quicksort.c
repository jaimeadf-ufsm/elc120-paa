
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void quicksort(int *array, int n)
{
    qsort(array, n, sizeof(int), compare);
}