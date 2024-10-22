#include <stdlib.h>
#include <pthread.h>

#include "mergesort.h"
typedef struct
{
    int *source;
    int *destination;
    int left;
    int right;
} mergesort_args;

// define um limite para determinar quando a ordenação paralela deve ser interrompida
#define THREAD_THRESHOLD 100000

// mescla 2 subarrays em um array de destino (ordenado)
void merge(int source[], int destination[], int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right)
    {
        if (source[i] < source[j])
        {
            destination[left++] = source[i++]; // adiciona elemento do subarray esquerdo
        }
        else
        {
            destination[left++] = source[j++]; // Adiciona elemento do subarray direito
        }
    }

    // copia os elementos restantes do subarray esquerdo, se houver
    while (i <= mid)
    {
        destination[left++] = source[i++];
    }

    // copia os elementos restantes do subarray direito, se houver
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

// realiza o mergesort de forma recursiva
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

// realiza o mergesort de forma iterativa
void iterative_mergesort(int array[], int size)
{
    int *auxiliary = malloc(size * sizeof(int));

    int *source = array;
    int *destination = auxiliary;

    // itera sobre o array, mesclando subarrays de tamanho 1, 2, 4 ...
    for (int width = 1; width < size; width *= 2)
    {
        // mescla os subarrays em pares
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

        // troca os ponteiros para o proximo iteracao
        int *temp = source;

        source = destination;
        destination = temp;
    }

    // se precisar copia o array ordenado para o array original
    if (source != array)
    {
        for (int i = 0; i < size; i++)
        {
            destination[i] = source[i];
        }
    }

    free(auxiliary);
}

void *parallel_mergesort_recursion(void *args)
{
    mergesort_args *ms_args = (mergesort_args *)args;
    int left = ms_args->left;
    int right = ms_args->right;
    int *source = ms_args->source;
    int *destination = ms_args->destination;

    if (left >= right)
    {
        return NULL;
    }

    int mid = (left + right) / 2;

    if (right - left + 1 > THREAD_THRESHOLD) // se o tamanho do subarray exceder o limite, cria threads para ordenar em paralelo
    {
        pthread_t left_thread, right_thread;
        mergesort_args left_args = {destination, source, left, mid};
        mergesort_args right_args = {destination, source, mid + 1, right};

        pthread_create(&left_thread, NULL, parallel_mergesort_recursion, &left_args);
        pthread_create(&right_thread, NULL, parallel_mergesort_recursion, &right_args);

        pthread_join(left_thread, NULL);
        pthread_join(right_thread, NULL);
    }
    else
    {
        // caso contrário, realiza a ordenação de forma recursiva
        mergesort_recursion(destination, source, left, mid);
        mergesort_recursion(destination, source, mid + 1, right);
    }

    merge(source, destination, left, mid, right);

    return NULL;
}

// realiza o mergesort de forma paralela
void parallel_mergesort(int array[], int size)
{
    int *auxiliary = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        auxiliary[i] = array[i];
    }

    mergesort_args args = {auxiliary, array, 0, size - 1};
    parallel_mergesort_recursion(&args);

    free(auxiliary);
}
