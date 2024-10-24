#include <stdlib.h>
#include <pthread.h>

#include "mergesort.h"

typedef struct mergesort_thread_args MergesortThreadArgs;

struct mergesort_thread_args
{
    int *source;
    int *destination;
    int left;
    int right;
};

// Define um limiar para determinar quando a ordenação paralela deve ser
// interrompida.
#define MERGESORT_PARALLEL_THRESHOLD 100000

// Junta os subvetores ordenados em source[left..mid] e em source[mid+1..right]
// para destination[left..right].
void merge(int source[], int destination[], int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;

    int k = left;

    // Percorre os subvetores esquerdo e direito simultaneamente,
    // mesclando os elementos em ordem crescente.
    while (i <= mid && j <= right)
    {
        if (source[i] < source[j])
        {
            // Copia o elemento do subvetor esquerdo,
            // quando ele for menor que o do subvetor direito.
            destination[k++] = source[i++];
        }
        else
        {
            // Copia o elemento do subvetor direito,
            // quando ele for menor que o do subvetor esquerdo ou igual.
            destination[k++] = source[j++];
        }
    }

    // Copia os elementos restantes do subvetor esquerdo, se houver.
    while (i <= mid)
    {
        destination[k++] = source[i++];
    }

    // Copia os elementos restantes do subvetor direito, se houver.
    while (j <= right)
    {
        destination[k++] = source[j++];
    }
}

// Aplica o Merge Sort recursivamente no subvetor source[left..right] e
// armazena o resultado em destination[left..right].
//
// Isso é realizado em duas etapas:
// 1. Divisão: divide o vetor em dois subvetores de tamanhos iguais.
// 2. Conquista: mescla os subvetores, ordenando-os.
//
// A cada chamada recursiva, os vetores source e destination são trocados
// com o objetivo de evitar cópias desnecessárias.
//
// OBS: Inicialmente, os vetores soruce e destination devem estar preenchidos
// com os mesmos valores.
void mergesort_recursion(int source[], int destination[], int left, int right)
{
    // Caso base:
    // Se o subvetor tiver tamanho 0 ou 1, ele já está ordenado.
    if (left >= right)
    {
        return;
    }

    // Divisão:
    // Subdivide o vetor em dois subvetores de tamanhos iguais:
    // - Subvetor esquerdo: destination[left..mid]
    // - Subvetor direito: destination[mid+1..right]
    //
    // Em seguida, aplica o Merge Sort recursivamente em cada subvetor,
    // escrevendo o resultado em source[left..right].
    int mid = (left + right) / 2;

    mergesort_recursion(destination, source, left, mid);
    mergesort_recursion(destination, source, mid + 1, right);

    // Conquista:
    // Mescla os subvetores ordenados em source[left..mid] e em
    // source[mid+1..right] para destination[left..right].
    merge(source, destination, left, mid, right);
}

// Executa o Merge Sort de forma recursiva.
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

// Executa o Merge Sort de forma iterativa.
void iterative_mergesort(int array[], int size)
{
    int *auxiliary = malloc(size * sizeof(int));

    int *source = array;
    int *destination = auxiliary;

    // Itera sobre o vetor, dividindo-o em subvetores de tamanhos crescentes.
    for (int width = 1; width < size; width *= 2)
    {
        // Mescla os subvetores de tamanho width em pares.
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

        // Troca os vetores source e destination para evitar cópias
        // desnecessárias.
        int *temp = source;

        source = destination;
        destination = temp;
    }

    // Caso o vetor original já não seja o vetor de destino, copia o vetor
    // ordenado para o vetor original.
    //
    // Note que o vetor source é o destino da última iteração, visto que a troca
    // ocorre no final do laço de repetição.
    if (source != array)
    {
        for (int i = 0; i < size; i++)
        {
            destination[i] = source[i];
        }
    }

    free(auxiliary);
}

// Aplica o Merge Sort recursivamente, assim como na função de recursão
// original, criando threads para realizar a ordenação de forma paralela.
void *parallel_mergesort_recursion(void *args)
{
    MergesortThreadArgs *mergesort_args = (MergesortThreadArgs *)args;

    int left = mergesort_args->left;
    int right = mergesort_args->right;
    int *source = mergesort_args->source;
    int *destination = mergesort_args->destination;

    if (left >= right)
    {
        return NULL;
    }

    int n = right - left + 1;
    int mid = (left + right) / 2;

    // Se o tamanho do subvetor exceder o limiar predefinido,
    // cria threads para realizar a ordenação em paralelo.
    if (n > MERGESORT_PARALLEL_THRESHOLD) 
    {
        pthread_t left_thread, right_thread;
        MergesortThreadArgs left_args = {destination, source, left, mid};
        MergesortThreadArgs right_args = {destination, source, mid + 1, right};

        pthread_create(&left_thread, NULL, parallel_mergesort_recursion, &left_args);
        pthread_create(&right_thread, NULL, parallel_mergesort_recursion, &right_args);

        pthread_join(left_thread, NULL);
        pthread_join(right_thread, NULL);
    }
    else
    {
        // Caso contrário, realiza a ordenação de forma recursiva.
        mergesort_recursion(destination, source, left, mid);
        mergesort_recursion(destination, source, mid + 1, right);
    }

    merge(source, destination, left, mid, right);

    return NULL;
}

// Executa o Merge Sort de forma paralela.
void parallel_mergesort(int array[], int size)
{
    int *auxiliary = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        auxiliary[i] = array[i];
    }

    MergesortThreadArgs args = {auxiliary, array, 0, size - 1};
    parallel_mergesort_recursion(&args);

    free(auxiliary);
}
