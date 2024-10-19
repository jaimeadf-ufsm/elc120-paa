#include <stdio.h>
#include <stdlib.h>

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

void split(int source[], int destination[], int left, int right)
{
    if (left >= right) {
        return;
    }

    int mid = (left + right) / 2;

    split(destination, source, left, mid);
    split(destination, source, mid + 1, right);
    merge(destination, source, left, mid, right);
}

void mergeSort(int array[], int size)
{
    int *temp = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        temp[i] = array[i];
    }

    split(array, temp, 0, size - 1);
    free(temp);
}

int main()
{
    int array[] = {5, 4, 3, 2, 1, 10, 20, 1};
    int size = sizeof(array) / sizeof(array[0]);

    mergeSort(array, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");

    return 0;
}