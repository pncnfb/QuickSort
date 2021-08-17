/*
 * Pancino Fabio 1238530
 * Parallel Computing
 * Sequential implementation of QuickSort
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>
#include "methods.h"
#include "mpi.h"
#define SIZE 1000000

int main()
{
    int *unsorted_array = (int *)malloc(SIZE * sizeof(int));
    randomGenerator(unsorted_array, SIZE);


    int n = SIZE;

    double begin = MPI_Wtime();
    //clock_t begin = MPI_Wtime();//clock();
    quickSort(unsorted_array, 0, n - 1);
    //clock_t end = MPI_Wtime();//clock();
    double end = MPI_Wtime();
    //double time_spent1 = (double)(end - begin) / CLOCKS_PER_SEC;
    //printf( "Sorted array: ");
    //printArray(array1, n);


/*
    // 2M samples
    int* array2 = (int *) malloc(sizeof(int) * 2000000);
    for (int i = 0; i < 2000000; i++)
        array2[i] = rand()%2000000;


    n = 2000000;

    begin = clock();
    quickSort(array2, 0, n - 1);
    end = clock();
    double time_spent2 = (double)(end - begin) / CLOCKS_PER_SEC;

    printf( "Sorted array: ");
    //printArray(array2, n);
*/
    // 4M samples
    /*  int* array3 = (int *) malloc(sizeof(int) * 1000000);
      for (int i = 0; i < 4000000; i++)
          array3[i] = rand()%4000000;


      n = 4000000;//sizeof(array3) / sizeof(array3[0]);

      begin = clock();
      quickSort(array3, 0, n - 1);
      end = clock();
      double time_spent3 = (double)(end - begin) / CLOCKS_PER_SEC; */

    //printf( "Sorted array: ");
    //printArray(array3, n);

    // 16M samples
    /* int* array4 = (int *) malloc(sizeof(int) * 16000000);
     for (int i = 0; i < 16000000; i++)
         array4[i] = rand()%16000000;


      n = 16000000;
      begin = clock();
     quickSort(array4, 0, n - 1);
     end = clock();
     double time_spent4 = (double)(end - begin) / CLOCKS_PER_SEC;*/

    //printf( "Sorted array: ");
    //printArray(array3, n);

    //printf("\n Time (%d samples): %f", SIZE, time_spent1);
    printf("\n Time (%d samples): %2.7f sec", SIZE, (end-begin));
//    printf("\n Time (2M samples): %f", time_spent2);
    //   printf("\n Time (4M samples): %f", time_spent3);
// printf("\n Time (16M samples): %f", time_spent4);
/*
    FILE *fp;
    int myInt = 5;
    fp = fopen("Output.txt", "w");// "w" means that we are going to write on this file
    fprintf(fp, "\n Time (1M samples): %f", time_spent1);
    fprintf(fp, "\n Time (2M samples): %f", time_spent2);
  //  fprintf(fp, "\n Time (4M samples): %f", time_spent3);
   // fprintf(fp, "\n Time (16M samples): %f", time_spent4);
    fclose(fp); //Don't forget to close the file when finished
*/
    return 0;
}

/*
 * con malloc vado ad allocare nell'heap e riesco a gestire grandi vettori
 */

