#!/bin/bash

#SBATCH --job-name quicksortMPI
#SBATCH --error err.txt
#SBATCH --output out.txt
#SBATCH --partition allgroups
#SBATCH --ntasks 8
#SBATCH -c 1
#SBATCH --mem 64G
#SBATCH --time 20:00

#spack load openmpi@3.1.4
spack load intel-parallel-studio@professional.2019.4

mpicc quicksortMPI.c -o quicksortMPI.o
mpirun -np 8 ./quicksortMPI.o 16000000
mpirun -np 8 ./quicksortMPI.o 8000000
mpirun -np 8 ./quicksortMPI.o 4000000
mpirun -np 8 ./quicksortMPI.o 1000000
