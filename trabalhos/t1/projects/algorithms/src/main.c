#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sources.h"
#include "mergesort.h"
#include "insertionsort.h"
#include "quicksort.h"
#include "quicksert.h"

#include "high_precision_timer.h"

typedef void (*ConsumeFunction)(int *, int);
typedef void (*SortFunction)(int *, int);

ConsumeFunction resolve_source(char *source)
{
    if (strcmp(source, "ascendant") == 0)
    {
        return consume_ascendant;
    }
    else if (strcmp(source, "descendant") == 0)
    {
        return consume_descendant;
    }
    else if (strcmp(source, "random") == 0)
    {
        return consume_random;
    }
    else
    {
        printf("ERROR: Invalid source.\n");
        exit(EXIT_FAILURE);
    }
}

SortFunction resolve_algorithm(char *algorithm)
{
    if (strcmp(algorithm, "recursive_mergesort") == 0)
    {
        return recursive_mergesort;
    }
    else if (strcmp(algorithm, "iterative_mergesort") == 0)
    {
        return iterative_mergesort;
    }
    else if (strcmp(algorithm, "parallel_mergesort") == 0)
    {
        return parallel_mergesort;
    }
    else if (strcmp(algorithm, "insertionsort") == 0)
    {
        return insertionsort;
    }
    else if (strcmp(algorithm, "quicksort") == 0)
    {
        return cquicksort;
    }
    else if (strcmp(algorithm, "quicksert") == 0)
    {
        return quicksert;
    }
    else
    {
        printf("ERROR: Invalid algorithm.\n");
        exit(EXIT_FAILURE);
    }
}

void benchmark(int argc, char *argv[])
{
    if (argc != 8)
    {
        printf("Usage: %s benchmark <algorithm> <source> <start_size> <end_size> <step> <samples>\n", argv[0]);
        printf("\n");

        printf("Arguments:\n");
        printf("    algorithm       The algorithm to be used (recursive_mergesort, iterative_mergesort, parallel_mergesort, insertionsort, quicksort, quicksert)\n");
        printf("    source          The source of the array (ascendant, descendant, random)\n");
        printf("    start_size      Initial size of the array\n");
        printf("    end_size        Final size of the array\n");
        printf("    step            Increment to size\n");
        printf("    samples         Number of samples for every size\n");

        exit(EXIT_FAILURE);
    }

    char *algorithm = argv[2];
    char *source = argv[3];
    int start_size = atoi(argv[4]);
    int end_size = atoi(argv[5]);
    int step = atoi(argv[6]);
    int samples = atoi(argv[7]);

    ConsumeFunction consume = resolve_source(source);
    SortFunction sort = resolve_algorithm(algorithm);

    printf("algorithm: %s\n", algorithm);
    printf("source: %s\n", source);
    for (int size = start_size; size <= end_size; size += step)
    {
        int *array = malloc(size * sizeof(int));
        printf("%d:", size);

        for (int i = 0; i < samples; i++)
        {
            consume(array, size);

            Timer timer = start_timer();
            sort(array, size);
            stop_timer(&timer);

            printf(" %lf", get_timer_seconds(&timer) * 1e9);
        }

        printf("\n");
        free(array);
    }
}

void verify(int argc, char *argv[]){
    if (argc != 5)
    {
	printf("Usage: %s verify <algorithm> <source> <size>\n", argv[0]);
        printf("\n");

        printf("Arguments:\n");
        printf("    algorithm       The algorithm to be used (recursive_mergesort, iterative_mergesort, parallel_mergesort, insertionsort, quicksort, quicksert)\n");
        printf("    source          The source of the array (ascendant, descendant, random)\n");
        printf("    size            The size of the array\n");

	exit(EXIT_FAILURE);
    }
    char *algorithm = argv[2];
    char *source = argv[3];
    int size = atoi(argv[4]);

    ConsumeFunction consume = resolve_source(source);
    SortFunction sort = resolve_algorithm(algorithm);

    printf("algorithm: %s\n", algorithm);
    printf("source: %s\n", source);

    int *array = (int*)malloc(sizeof(int) * size);
    int *arrq = (int*)malloc(sizeof(int) * size);

    consume(array, size);
    memcpy(arrq, array, sizeof(int) * size);

    sort(array, size);
    cquicksort(arrq, size);

    int ordered = 1;

    for (int i = 0; i < size; i++)
    {
	  if (array[i] != arrq[i])
	  {
		  printf("Error on line %d (%d <> %d)\n", i, array[i], arrq[i]);
		  ordered = 0;
	  }
    }
    if (ordered) printf("\nArray ordered. No errors found.\n");
    else printf("\nErrors were found. Array was not correctly ordered.\n");

    free(array);
    free(arrq);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <command> <...arguments>\n", argv[0]);
        printf("\n");

        printf("Commands:\n");
        printf("    benchmark <algorithm> <source> <start_size> <end_size> <step> <samples>\n");
        printf("\n");

        return EXIT_FAILURE;
    }

    char *command = argv[1];

    if (strcmp(command, "benchmark") == 0)
    {
        benchmark(argc, argv);
    }
    else if (strcmp(command, "verify") == 0)
    {
	verify(argc, argv);
    }
    else
    {
        printf("ERROR: Invalid command.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
