#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define SWAP(a, b) { int64_t tmp = a; a = b; b = tmp; }

#define SOURCE_ASCENDING 0
#define SOURCE_DESCENDING 1
#define SOURCE_RANDOM 2

#define PIVOTING_METHOD_FIRST 0
#define PIVOTING_METHOD_MIDDLE 1
#define PIVOTING_METHOD_LAST 2

void fill_array_ascending(int64_t array[], int64_t size)
{
    for (int64_t i = 0; i < size; i++)
    {
        array[i] = i;
    }
}

void fill_array_descending(int64_t array[], int64_t size)
{
    for (int64_t i = 0; i < size; i++)
    {
        array[i] = size - i;
    }
}

void fill_array_random(int64_t array[], int64_t size)
{
    for (int64_t i = 0; i < size; i++)
    {
        array[i] = rand();
    }
}

void fill_array(int64_t array[], int64_t size, int64_t source)
{
    switch (source)
    {
        case SOURCE_ASCENDING:
            fill_array_ascending(array, size);
            break;
        case SOURCE_DESCENDING:
            fill_array_descending(array, size);
            break;
        case SOURCE_RANDOM:
            fill_array_random(array, size);
            break;
        default:
            printf("ERROR: Invalid source.\n");
            exit(EXIT_FAILURE);
    }
}

int64_t partition(int64_t array[], int64_t method, int64_t low, int64_t high, int64_t *comparisons)
{
    int64_t i = low - 1;
    int64_t j = high + 1;

    switch (method)
    {
        case PIVOTING_METHOD_FIRST:
            break;
        case PIVOTING_METHOD_MIDDLE:
            SWAP(array[low], array[(low + high) / 2]);
            break;
        case PIVOTING_METHOD_LAST:
            SWAP(array[low], array[high]);
            break;
        default:
            printf("ERROR: Invalid method.\n");
            exit(EXIT_FAILURE);
    }

    int64_t pivot = array[low];

    while (true)
    {
        do
        {
            i++;
            *comparisons = *comparisons + 1;
        } while (array[i] < pivot);

        do
        {
            j--;
            *comparisons = *comparisons + 1;
        } while (array[j] > pivot);


        if (i >= j)
        {
            return j;
        }

        SWAP(array[i], array[j]);
    }
}

int64_t quicksort(int64_t array[], int64_t method, int64_t low, int64_t high)
{
    int64_t comparisons = 0;
    
    if (low < high)
    {   
        int64_t p = partition(array, method, low, high, &comparisons);

        comparisons += quicksort(array, method, low, p);
        comparisons += quicksort(array, method, p + 1, high);
    }

    return comparisons;
}

int main(int argc, char *argv[])
{
    if (argc < 6)
    {
        printf("Usage: %s <method> <source> <start_size> <end_size> <step>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int64_t method = atoi(argv[1]);
    int64_t source = atoi(argv[2]);
    int64_t start_size = atoi(argv[3]);
    int64_t end_size = atoi(argv[4]);
    int64_t step = atoi(argv[5]);

    int64_t *array = (int64_t*)malloc(end_size * sizeof(int64_t));

    printf("%lld %lld\n", method, source);

    for (int64_t size = start_size; size <= end_size; size += step)
    {
        fill_array(array, size, source);
        int64_t comparisons = quicksort(array, method, 0, size - 1);

        printf("%lld: %lld\n", size, comparisons);
    }

    return EXIT_SUCCESS;
}