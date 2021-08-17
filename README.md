# QuickSort

* /include/methods.h, contains the functions shared between 'main.c' and 'mainMPI.c'

## Sequential QuickSort 
/sequential folder contains:
  * main.c  : pure sequential implementation of QuickSort
  * CMakeLists.txt


## Parallel QuickSort
/parallel folder contains:
  * mainMPI.c   : MPI implementation of both parallel and sequential QuickSort (based on the number of processes)
  * mainSLURM.slurm : compiles and runs the code for 1M, 2M, 4M and 16M  of instances


