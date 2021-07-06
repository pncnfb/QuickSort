#!/bin/bash

#SBATCH --job-name first
#SBATCH --output out_%j.txt
#SBATCH --error errros_%j.txt
###SBATCH --mail-user schimdmi@dei.unipd.it
###SBATCH --mail-type ALL
#SBATCH --ntasks 8
#SBATCH --partition allgroups
#SBATCH --time 02:00
#SBATCH --mem 1G

cd ~/src/capri/hellompi

spack load intel-parallel-studio@professional.2019.4

srun hellompi.o

