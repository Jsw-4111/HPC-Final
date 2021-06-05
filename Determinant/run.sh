#!/usr/bin/env bash

#SBATCH --job-name=job.%J
#SBATCH --error=job.%J.err
#SBATCH --output=job.%J.out
#SBATCH --ntasks=1
#SBATCH --time=5:00
#SBATCH --mem-per-cpu=100

module load gcc
module load openmpi

cd ~/Final
./DetParallel 32
./DetParallel 64
./DetParallel 128
./DetParallel 256
./DetParallel 496
./DetParallel 512
./DetParallel 1000
./DetParallel 1024
./DetParallel 2000
./DetParallel 2048
./DetParallel 3000
./DetParallel 4000
./DetParallel 4096