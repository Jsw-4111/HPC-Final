/** Developed by John Wu and Samuel Ketner
 * Determinant: Solve the smaller ones on their own processors, solve the big bois together
 * Big bois are the 1000+x1000+ determinants
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "readmat.h"
#include <sys/time.h>
#include <pthread.h>
#include <omp.h>
#include <math.h>

void upperTriangular(double* matrix, int size);
void printMatrix(double* matrix, int size);
void* addRow(void* rowInfo);

struct addRowInfo {
    int i;
    int j;
    int totalThreads;
    int size;
    int thread;
    double scalar;
    double* matrix;
};

int main() {
    struct timeval start, end;
    int size = 4096;
    char* fileName = "m4096x4096.bin";
    gettimeofday(&start, NULL);
    double* matrix = grab(size, fileName);
    // printMatrix(matrix, size);
    upperTriangular(matrix, size);
    // printMatrix(matrix, size);
    double determinantResult = 1;
    // #pragma omp parallel for num_threads(size)
    for(int i = 0; i < size; i++) {
        determinantResult *= matrix[i*size + i];
    }
    gettimeofday(&end, NULL);
    printf("The computation took %ld milliseconds\n", (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec)/1000);
    printf("\nThe result of our determinant is: %f\n", determinantResult);
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
            int pthreadcount = trunc(log2(size));
            pthread_t* pthreadhandles = malloc(sizeof(pthread_t) * pthreadcount);
            struct addRowInfo* allRowInfo = malloc(sizeof(struct addRowInfo) * pthreadcount);
            for(int thread = 0; thread < pthreadcount; thread++) {
                allRowInfo[thread].i = i;
                allRowInfo[thread].j = j;
                allRowInfo[thread].totalThreads = pthreadcount;
                allRowInfo[thread].size = size;
                allRowInfo[thread].matrix = matrix;
                allRowInfo[thread].thread = thread;
                allRowInfo[thread].scalar = scalar;
                pthread_create(&pthreadhandles[thread], NULL, addRow, (void*) &allRowInfo[thread]);
            }
            for(int thread = 0; thread < pthreadcount; thread++) {
                pthread_join(pthreadhandles[thread], NULL);
            }
            // for(int k = i; k < size; k++) { // Adds the multiple of a row to this one
            // // #   pragma omp critical
            //     matrix[j*size + k] += (-scalar)*matrix[i*size + k];
            // }
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

void* addRow(void* rowInfo) {
    struct addRowInfo info = *((struct addRowInfo*) rowInfo);
    double* matrix = info.matrix;
    int numRuns = info.size / info.totalThreads;
    int startIndex = numRuns * (info.thread);
    if(info.thread < info.size % info.totalThreads) {
        numRuns++;
        startIndex += info.thread;
    } else {
        startIndex += info.size % info.totalThreads;
    }
    int endIndex = startIndex + numRuns;
    for(int i = startIndex; i < endIndex; i++) {
        matrix[info.j*info.size + i] = info.scalar * matrix[info.i * info.size + i];
    }
    return NULL;
}
