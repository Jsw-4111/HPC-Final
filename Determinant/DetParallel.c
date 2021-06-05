/** Developed by John Wu and Samuel Ketner
 * Determinant: Solve the smaller ones on their own processors, solve the big bois together
 * Big bois are the 1000+x1000+ determinants
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "readmat.h"
#include <sys/time.h>
#include <omp.h>
#include <math.h>
#include <string.h>

void upperTriangular(double* matrix, int size);
void printMatrix(double* matrix, int size);

int main(int argc, char* argv[]) {
    struct timeval start, end;
    if(argc != 2) {
        printf("Too few or many arguments, this program only accepts a single argument for the size of the matrix\n");
        return 0;
    }
    int size = 32;
    char* fileName  = "m0032x0032.bin";
    if(strcmp(argv[1], "32") == 0) {
        size = 32;
        fileName = "m0032x0032.bin";
    } else if(strcmp(argv[1], "64") == 0) {
        size = 64;
        fileName = "m0064x0064.bin";
    } else if(strcmp(argv[1], "128") == 0) {
        size = 128;
        fileName = "m0128x0128.bin";
    } else if(strcmp(argv[1], "256") == 0) {
        size = 256;
        fileName = "m0256x0256.bin";
    } else if(strcmp(argv[1], "496") == 0) {
        size = 496;
        fileName = "m0496x0496.bin";
    } else if(strcmp(argv[1], "512") == 0) {
        size = 512;
        fileName = "m0512x0512.bin";
    } else if(strcmp(argv[1], "1000") == 0) {
        size = 1000;
        fileName = "m1000x1000.bin";
    } else if(strcmp(argv[1], "1024") == 0) {
        size = 1024;
        fileName = "m1024x1024.bin";
    } else if(strcmp(argv[1], "2000") == 0) {
        size = 2000;
        fileName = "m2000x2000.bin";
    } else if(strcmp(argv[1], "2048") == 0) {
        size = 2048;
        fileName = "m2048x2048.bin";
    } else if(strcmp(argv[1], "3000") == 0) {
        size = 3000;
        fileName = "m3000x3000.bin";
    } else if(strcmp(argv[1], "4000") == 0) {
        size = 4000;
        fileName = "m4000x4000.bin";
    } else if(strcmp(argv[1], "4096") == 0) {
        size = 4096;
        fileName = "m4096x4096.bin";
    }
    gettimeofday(&start, NULL);
    double* matrix = grab(size, fileName);
    // printMatrix(matrix, size);
    upperTriangular(matrix, size);
    // printMatrix(matrix, size);
    double determinantResult = 1;
    double determinantLog = 0;
    // #pragma omp parallel for num_threads(size)
    for(int i = 0; i < size; i++) {
        determinantResult *= matrix[i*size + i];
        determinantLog += log10(fabs(matrix[i*size + i]));
    }
    gettimeofday(&end, NULL);
    printf("The computation took %ld milliseconds\n", (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec)/1000);
    printf("(3) The result of our determinant is: %f\n", determinantResult);
    printf("(4) The log result of our determinant is: %f\n\n", determinantLog);
}

void upperTriangular(double* matrix, int size) {
    for(int i = 0; i < size - 1; i++) { // Iterate through the diagonal
        int threadNum = trunc(log2(size));
        if(threadNum < 4) {
            threadNum = 4;
        }
    #   pragma omp parallel for num_threads(threadNum)
        for(int j = i+1; j < size; j++) { // Grab the rows we're interested in this run
            double scalar = matrix[j*size + i] / matrix[i*size + i];
            for(int k = i; k < size; k++) { // Adds the multiple of a row to this one
            // #   pragma omp critical
                matrix[j*size + k] += (-scalar)*matrix[i*size + k];
            }
        }
    }
}

void printMatrix(double* matrix, int size) {
    for(int i = 0; i < size*size; i++) {
            if(i % size == 0) {
                printf("\n");
            }
            printf("%f ", matrix[i]);
        }
}
