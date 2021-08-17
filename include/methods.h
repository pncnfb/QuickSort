/*
 * Pancino Fabio 1238530
 * Parallel Computing
 * Support methods
*/
#include <stdbool.h>
#include "math.h"

#ifndef QUICKSORT_PROJECT_METHODS_H
#define QUICKSORT_PROJECT_METHODS_H

// Swap two elements
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*
 * This function takes last element as pivot, places
 * the pivot element at its correct position in sorted
 * array, and places all smaller (smaller than pivot)
 * to left of pivot and all greater elements to right
 * of pivot
 */
int partition( int *a, int low, int high ) {
    bool flag = false;
    int first = low;        /// Left indice
    int last = high + 1;    /// Right indice
    int pivot = a[low];   /// Partitioning item

    while (!flag) {
        while (a[++first] < pivot) {   /// Scan left and move
            if (first == high) flag = true;
        }
        while (a[--last] > pivot) {    /// Scan right and move
            if (last == low) flag = true;
        }

        if (first >= last) {
            flag = true;
        } else {
            swap(&a[first], &a[last]);
        }
    }

    swap(&a[low], &a[last]);

    return last;
}

/*
 * The main function that implements QuickSort
 *  arr[] --> Array to be sorted,
 *  low --> Starting index,
 *  high --> Ending index
 */
void quickSort(int *arr, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/*
 * Function to print an array
 * */
void printArray(int *arr, int size)
{
    for (int i = 0; i < size; i++) {
        printf("%d ", *arr);
        arr++;
    }
}

/*
 * Merge two sorted subarrays
*/
void merge(int *first,int *second, int *result,int first_size,int second_size){
    int i=0;
    int j=0;
    int k=0;

    while(i<first_size && j<second_size){

        if (first[i]<second[j]) {
            result[k]=first[i];
            k++;
            i++;
        }else{
            result[k]=second[j];
            k++;
            j++;
        }

        if(i == first_size){
            // if the first array has been sorted
            while(j<second_size){
                result[k]=second[j];
                k++;
                j++;
            }
        } else if (j == second_size){
            // if the second array has been sorted
            while(i < first_size){
                result[k]=first[i];
                i++;
                k++;
            }
        }
    }
}

/*
 * Generates an array of random numbers
 */
void randomGenerator(int *arr, int num_elements)
{
    for (int i = 0; i < num_elements; i++) {
        *arr =(int) rand() % 1000 ;
        arr++;
    }
    printf("Random array with %d created\n", num_elements);
}

#endif //QUICKSORT_PROJECT_METHODS_H
