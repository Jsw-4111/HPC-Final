#include <stdlib.h>
#include <stdio.h>

#define ARRAYSIZE 16








double* grab(int size, char* r){
	
	char* file = malloc(50*sizeof(char));
        double* arr = malloc (size*size*sizeof(double));
        int slot, col;
        double d;
        sprintf(file,r);//"m0016x0016.bin");
        printf("Reading array file %s of size %dx%d\n", file, size, size);

        FILE* df = fopen(file, "rb");
        for (slot = 0; slot < size;slot++){
                for (col =0;col<size;col++){
                        fread(&arr[slot*size+col], sizeof(double), 1, df);
                        // printf("a[%d][%d]=%f\n", slot, col, arr[slot*size+col]);
			//comment-outable
                }


        }
	//comment-outable
        printf("Matrix has been read.\n");	
	return df;


}





int main (int count, char ** r){

double * y = grab(4096, "m4096x4096.bin");

	return 0;
}