#ifndef MERGESORT_H
#define MERGESORT_H

void recursive_mergesort(int array[], int size);
void iterative_mergesort(int array[], int size);
void parallel_mergesort(int array[], int size);
void merge(int source[], int destination[], int left, int mid, int right);
void mergesort_recursion(int source[], int destination[], int left, int right);

#endif