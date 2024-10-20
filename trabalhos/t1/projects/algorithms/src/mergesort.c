#include <stdlib.h>

#include "mergesort.h"

void merge(int source[], int destination[], int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right)
    {
        if (source[i] < source[j])
        {
            destination[left++] = source[i++];
        }
        else
        {
            destination[left++] = source[j++];
        }
    }

    while (i <= mid)
    {
        destination[left++] = source[i++];
    }

    while (j <= right)
    {
        destination[left++] = source[j++];
    }
}

void mergesort_recursion(int source[], int destination[], int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int mid = (left + right) / 2;

    mergesort_recursion(destination, source, left, mid);
    mergesort_recursion(destination, source, mid + 1, right);
    merge(source, destination, left, mid, right);
}

void recursive_mergesort(int array[], int size)
{
    int *auxiliary = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        auxiliary[i] = array[i];
    }

    mergesort_recursion(auxiliary, array, 0, size - 1);
    free(auxiliary);
}

void iterative_mergesort(int array[], int size)
{
    int *auxiliary = malloc(size * sizeof(int));

    int *source = array;
    int *destination = auxiliary;

    for (int width = 1; width < size; width *= 2)
    {
        for (int i = 0; i < size; i += 2 * width)
        {
            int left = i;

            int mid = i + width - 1;
            int right = i + 2 * width - 1;

            if (mid >= size)
            {
                mid = size - 1;
            }

            if (right >= size)
            {
                right = size - 1;
            }

            merge(source, destination, left, mid, right);
        }

        int *temp = source;

        source = destination;
        destination = temp;
    }

    if (source != array)
    {
        for (int i = 0; i < size; i++)
        {
            destination[i] = source[i];
        }
    }

    free(auxiliary);
}