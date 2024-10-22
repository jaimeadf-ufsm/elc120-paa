#include "insertionsort.h"

void insertionsort(int *array, int n)
{
    int i;

    for (i = 1; i < n; i++)
    {
        int j = i;
        int temporary = array[i];

        while (j > 0 && array[j - 1] > temporary)
        {
            array[j] = array[j - 1];
            j--;
        }

        array[j] = temporary;
    }
}
