#include <stdlib.h>

#include "mergesort.h"

void merge(int source[], int destination[], int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right) {
        if (source[i] < source[j]) {
            destination[left++] = source[i++];
        } else {
            destination[left++] = source[j++];
        }
    }

    while (i <= mid) {
        destination[left++] = source[i++];
    }

    while (j <= right) {
        destination[left++] = source[j++];
    }
}

void mergesort_recursion(int source[], int destination[], int left, int right)
{
    if (left >= right) {
        return;
    }

    int mid = (left + right) / 2;

    mergesort_recursion(destination, source, left, mid);
    mergesort_recursion(destination, source, mid + 1, right);
    merge(source, destination, left, mid, right);
}

void recursive_mergesort(int array[], int size)
{
    int *temp = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        temp[i] = array[i];
    }

    mergesort_recursion(temp, array, 0, size - 1);
    free(temp);
}