#!/bin/bash
#SBATCH --job-name=MPI
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1

# Cargar Modulos de gcc y mpi
module load devtools/gcc/6.2.0
module load devtools/mpi/openmpi/3.1.4

# Con el comando make, compilamos el programa
make

# Se corren inicialmente con los valores predeterminados
mpirun -np 1 ./heat_mpi

# Se asignan el número de pasos de tiempo
mpirun -np 1 ./heat_mpi bottle.dat 1000

# Se ejecuta el patrón con dimensiones y pasos de tiempo
mpirun -np 1 ./heat_mpi 800 800 1000
