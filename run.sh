#!/usr/bin/env bash

#SBATCH --job-name=job.%J
#SBATCH --error=job.%J.err
#SBATCH --output=job.%J.out
#SBATCH --ntasks=8
#SBATCH --time=5:00
#SBATCH --mem-per-cpu=100

module load gcc
module load openmpi

cd ~/Final
./DetSerial 32
./DetSerial 64
./DetSerial 128
./DetSerial 256
./DetSerial 496
./DetSerial 512
./DetSerial 1000
./DetSerial 1024
./DetSerial 2000
./DetSerial 2048
./DetSerial 3000
./DetSerial 4000
./DetSerial 4096