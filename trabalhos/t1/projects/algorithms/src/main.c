#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mergesort.h"

void read_source(char *source, int *array, int size)
{
    if (strcmp(source, "stdin") == 0) {
        for (int i = 0; i < size; i++) {
            scanf("%d", &array[i]);
        }
    } else {
        printf("ERROR: Invalid source.\n");
        exit(EXIT_FAILURE);
    }
}

void sort_array(char *algorithm, int *array, int size)
{
    if (strcmp(algorithm, "recursive_mergesort") == 0) {
        recursive_mergesort(array, size);
    } else if (strcmp(algorithm, "iterative_mergesort") == 0) {
        recursive_mergesort(array, size);
    } else {
        printf("ERROR: Invalid algorithm.\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("Usage: %s <algorithm> <source> <size>\n", argv[0]);
        printf("\n");
        printf("Arguments:\n");
        printf("  algorithm        The algorithm to be used (\"iterative_mergesort\", \"recursive_mergesort\")\n");
        printf("  source           The source for the array (\"stdin\")\n");
        printf("  size             The size of the array\n");

        return 1;
    }

    char *algorithm = argv[1];
    char *source = argv[2];
    int size = atoi(argv[3]);

    int *array = malloc(size * sizeof(int));

    read_source(source, array, size);
    sort_array(algorithm, array, size);

    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");

    return 0;
}