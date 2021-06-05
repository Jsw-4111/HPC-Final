#include <stdlib.h>
#include <stdio.h>
#include "readmat.h"

#define ARRAYSIZE 16

double* grab(int size, char* r){
	
	char* file = malloc(50*sizeof(char));
        double* arr = malloc (size*size*sizeof(double));
        int row, col;
        sprintf(file,r);//"m0016x0016.bin");
        printf("(1) Reading array file %s\n", file);
        printf("(2) of size %dx%d\n", size, size);

        FILE* df = fopen(file, "rb");
        for (row = 0; row < size; row++){
                for (col =0;col<size;col++){
                        fread(&arr[row*size + col], sizeof(double), 1, df);
                        // printf("a[%d][%d]=%f\n", row, col, arr[slot*size+col]);
			//comment-outable
                }
        }
	//comment-outable
        printf("Matrix has been read.\n");
        free(file);	
	return arr;

}

// int main() {
//         int size = 4096;
//         char* fileName = "m4096x4096.bin";
//         double** arr = grab(size, fileName);
//         return 0;
// }