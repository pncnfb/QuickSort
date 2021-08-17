/*
 * Pancino Fabio 1238530
 * Parallel Computing
 * Sequential implementation of QuickSort
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>
#include "include/methods.h"
#define SIZE 1000000

int main()
{
    int *unsorted_array = (int *)malloc(SIZE * sizeof(int));
    randomGenerator(unsorted_array, SIZE);


    int n = SIZE;

    clock_t begin = clock();
    quickSort(unsorted_array, 0, n - 1);
    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;


    printf("\n Time (%d samples): %2.7f sec", SIZE, time_spent);

    return 0;
}


