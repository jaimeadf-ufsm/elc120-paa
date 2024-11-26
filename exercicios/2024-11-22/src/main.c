#include <stdio.h>
#include <stdlib.h>

typedef struct item Item;

#define MIN(a, b) ((a) < (b) ? (a) : (b))

struct item
{
    int identifier;
    double weight;
    double value;
};

int cmp(const void *a, const void *b)
{
    Item *ia = (Item *)a;
    Item *ib = (Item *)b;

    return (double)ia->value / ia->weight < (double)ib->value / ib->weight;
}

// Análise de complexidade:
// Pior caso: O(n^2), Melhor caso: O(n log n), Caso médio: O(n log n)
double fractional_knapsack(Item *items, double *fractions, int n, double capacity)
{
    // O algoritmo ordena os itens em ordem decrescente de valor por peso.
    // Pior caso: O(n^2), Melhor caso: O(n log n), Caso médio: O(n log n)
    qsort(items, n, sizeof(Item), cmp);

    double total_value = 0;

    // O algoritmo percorre os itens ordenados e calcula a fração de cada item.
    // O(n)
    for (int i = 0; i < n; i++)
    {
        int identifier = items[i].identifier;

        fractions[identifier] = MIN(capacity / items[i].weight, 1);

        capacity -= fractions[identifier] * items[i].weight;
        total_value += fractions[identifier] * items[i].value;
    }

    return total_value;
}

int main()
{
    int n;
    double capacity;

    printf("Digite o número de itens e a capacidade da mochila: ");
    scanf("%d %lf", &n, &capacity);

    Item *items = malloc(n * sizeof(Item));
    double *fractions = malloc(n * sizeof(double));

    printf("Digite o peso e o valor de cada item:\n");

    for (int i = 0; i < n; i++)
    {
        items[i].identifier = i;

        printf("- Item %d: ", i);
        scanf("%lf %lf", &items[i].weight, &items[i].value);
    }

    double total_value = fractional_knapsack(items, fractions, n, capacity);

    printf("\n");
    printf("Valor: %lf\n", total_value);

    printf("Frações:\n");
    for (int i = 0; i < n; i++)
    {
        printf("- Item %d: ", i);
        printf("%.2lf\n", fractions[i]);
    }

    free(items);
    free(fractions);

    return 0;
}

