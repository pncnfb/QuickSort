#!/bin/bash

#SBATCH --job-name first
#SBATCH --output out_%j.txt
#SBATCH --error errros_%j.txt
###SBATCH --mail-user schimdmi@dei.unipd.it
###SBATCH --mail-type ALL
#SBATCH --ntasks 1
#SBATCH --partition allgroups
#SBATCH --time 02:00
#SBATCH --mem 1G

cd ~/project/sequential_quicksort/main

spack load intel-parallel-studio@professional.2019.4

srun main.o

