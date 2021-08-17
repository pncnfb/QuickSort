/*
 * Pancino Fabio 1238530
 * Parallel Computing
 * QuickSort
*/

#include "mpi.h"
#include<stdio.h>
#include <stdlib.h>
#include "math.h"
#include <stdbool.h>
#include "../include/methods.h"
#include <time.h>

int main(int argc, char *argv[]) {
    char *p;
    int SIZE = strtol(argv[1], &p, 10);
    int *unsorted_array = (int *)malloc(SIZE * sizeof(int));
    int *result = (int *)malloc(SIZE * sizeof(int));
    int array_size = SIZE;
    int size, rank;
    int sub_array_size;

    MPI_Status status;
    MPI_Init(&argc, &argv); // Start parallel execution
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank==0)
        randomGenerator(unsorted_array, SIZE);

    // Number of Clusters to be run
    int iter_count = size;

    // Size of the subarray that each Cluster receives
    sub_array_size=(int)SIZE/size;
    clock_t begin,end;

    /** Master  **/
    if( rank == 0 ){

        double start_useful, end_useful;
        double total_useful;
        double start_comm, end_comm;
        double start_timer;
        start_timer=MPI_Wtime();
        begin = clock();

        if(size > 1){
            // SENDING DATA
            // SPLITS the array and SENDS each subarray to the respective process
            start_comm = MPI_Wtime();
            for(int i=1;i<iter_count;i++) {
                MPI_Send(&unsorted_array[(i) * sub_array_size], sub_array_size, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
            end_comm = MPI_Wtime();

            printf("Master SEND time: %2.7f\n", end_comm-start_comm);

            // First subarray
            int *sub_array = (int *)malloc(sub_array_size*sizeof(int));
            for(int i=0;i<sub_array_size;i++){
                // Passing the first sub array since rank 0 always calculates the first sub array
                sub_array[i]=unsorted_array[i];
            }

            free(unsorted_array);

            start_useful = MPI_Wtime();

            // Sequentially sorting the first array
            quickSort(sub_array,0,sub_array_size-1);

            end_useful = MPI_Wtime();
            total_useful+=(end_useful-start_useful);

            //printf("Master\n");
            //printArray(sub_array,sub_array_size);

            double sum_communication;
            // RECEIVING DATA
            for (int i=0;i<iter_count;i++){
                if(i > 0){
                    int *temp_sub_array = (int *)malloc(sub_array_size * sizeof(int));

                    start_comm = MPI_Wtime();

                    MPI_Recv(temp_sub_array,sub_array_size,MPI_INT,i,0,MPI_COMM_WORLD,&status); // Receive each subarray
                    end_comm = MPI_Wtime();

                    sum_communication+=(end_comm-start_comm);

                    //printf("\nReceive from process %d \n", i);
                    //printArray(temp_sub_array,sub_array_size);
                    //printf("\n\n");

                    int *temp_result = (int *)malloc((i*sub_array_size) * sizeof(int));
                    for(int j=0;j<i*sub_array_size;j++){
                        temp_result[j]=result[j];
                    }
                    int temp_result_size = sub_array_size*i;

                    start_useful = MPI_Wtime();

                    // Merge it back into the result array
                    merge(temp_sub_array,temp_result,result,sub_array_size,temp_result_size);

                    end_useful = MPI_Wtime();
                    total_useful+=(end_useful-start_useful);

                }else{
                    // On first iteration we just pass the sorted elements to the result array

                    for(int j=0;j<sub_array_size;j++){
                        result[j]=sub_array[j];
                    }
                    free(sub_array);
                }
            }
            printf("Master RECEIVE time: %2.7f\n", sum_communication);
            printf("Master USEFUL work time: %2.7f\n", total_useful);

        }else{
            start_useful = MPI_Wtime();
            // if it runs only in a single Cluster
            quickSort(unsorted_array,0,SIZE-1);
            end_useful = MPI_Wtime();

            printf("Master USEFUL work time: %2.7f\n", end_useful-start_useful);
            for(int i=0;i<SIZE;i++){
                result[i]=unsorted_array[i];
            }
        }
        clock_t end = clock();
        double finish_timer;
        finish_timer=MPI_Wtime();
        printf("End Result: \n");
        printf("Cluster Size %d, execution time measured : %2.7f sec \n",size, finish_timer-start_timer);

        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("\n Time (%d samples): %2.7f sec", SIZE, time_spent);
    }

    /** All the other Processes **/
    double start_comm, end_comm;
    double communication_time;
    if(rank>0){



        sub_array_size=(int)SIZE/iter_count;
        int *sub_array = (int *)malloc(sub_array_size*sizeof(int));

        start_comm=MPI_Wtime();
        MPI_Recv(sub_array,sub_array_size,MPI_INT,0,0,MPI_COMM_WORLD,&status);  // receive the data
        end_comm=MPI_Wtime();

        printf("Receive time: %2.7f\n", end_comm-start_comm);

        communication_time+=(end_comm-start_comm);

        start_comm=MPI_Wtime();
        quickSort(sub_array,0,sub_array_size-1);    // sort the data
        end_comm=MPI_Wtime();

        printf("quicksort time: %2.7f\n", end_comm-start_comm);

        start_comm=MPI_Wtime();
        MPI_Send(sub_array,sub_array_size,MPI_INT,0,0,MPI_COMM_WORLD);//sends the data back to rank 0
        end_comm=MPI_Wtime();
        printf("Send time: %2.7f\n", end_comm-start_comm);

        communication_time+=(end_comm-start_comm);

        free(sub_array);

        printf("Communication time %2.7f\n\n", communication_time);

    }

    // Uncomment for validation check
    /*if(rank==0){
        printf("Validation \n");
        bool error = false;
        for(int i=0;i<SIZE-1;i++) {
            if (result[i] > result[i+1]){
                error = true;
                printf("Error in i=%d \n", i);
            }
        }
        if(error)
            printf("Error\n");
        else
            printf("Correct!\n");

    }*/
    free(unsorted_array);

    //printf("\n\n");
    //printArray(result,SIZE);

    MPI_Finalize(); // End of Parallel Execution
}