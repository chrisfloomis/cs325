/*
Authors:        Benjamin Tullis, Dalena Pham, Chris Loomis
Group:			9
Filename:       main.c
Created On:     01/20/2016
Last Mod:       01/20/2016
*/

#include "msa.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Prints array in format:
    Entire array
    Maximum subarray
    Maximum subarray sum
*/
void printArray(FILE *file, int a[], int size, int begin, int end, int maxSum) {
    int i;

    /* Prints entire array */
    fprintf(file, "\n\[");
    for(i = 0; i <= size; i++) {
        if(i < size)
            fprintf(file, "%d, ", a[i]);
        else
            fprintf(file, "%d]", a[i]);
    }

    /* Prints maximum subarray */
    fprintf(file, "\n\[");
    for(i = begin; i <= end; i++) {
        if(i < end)
            fprintf(file, "%d, ", a[i]);
        else
            fprintf(file, "%d]", a[i]);
    }

    /* Prints maximum subarray sum */
    fprintf(file, "\n%d", maxSum);
}


/* Reads array from file and returns a pointer to a copied array */
int* buildArray(int size, FILE *file, int* length) {
    char str1;
    int* array = malloc(sizeof(int) * size);
    int i = 0;

    // fencepost
    fscanf(file, "%c", &str1);
    fscanf(file, "%d", &array[i]);

    // Continue until there are no more commas
    do{
        i++;
        fscanf(file, "%c", &str1);
        fscanf(file, "%d", &array[i]);
        //printf("%d ", array[counter]);
        fscanf(file, "%c", &str1);
    }while(str1 == ',');

    // save length of array in pointer
    *length = i;

    return array;
}


/* Modified linearSubArray method that will output the array assessed, the maximum
    subarray and the maximum sum 
int linearSubArray(int a[], int n, FILE *file){
	int i;
	int begin = 0, end = 0;
	int max_so_far = a[0];
	int max_ending_here = a[0];

	for(i = 1; i < n; i++) {
        if(a[i] > (max_ending_here + a[i])){
            max_ending_here = a[i];
            begin = i;
        } else {
            max_ending_here = max_ending_here + a[i];
        }

        if(max_so_far < max_ending_here) {
            max_so_far = max_ending_here;
            end = i;
        }
	}

	printArray(file, a, n, begin, end, max_so_far);

	return max_so_far;
}*/

int main(int argc, char *argv[]) {
printf("1");
	int i;		//counter
	int *msa = NULL;	//this pointer will get the array back from functions
	int msaSum;		//this will hold the sum
	
    FILE *file, *output;
    file = fopen(argv[1], "r");
    output = fopen("MSS_Results.txt", "w");
    int* array1, *array2, *array3, *array4, *array5, *array6, *array7;
    int length[7];
printf("2");
    array1 = buildArray(40, file, &length[0]);
    array2 = buildArray(40, file, &length[1]);
    array3 = buildArray(40, file, &length[2]);
    array4 = buildArray(40, file, &length[3]);
    array5 = buildArray(40, file, &length[4]);
    array6 = buildArray(40, file, &length[5]);
    array7 = buildArray(40, file, &length[6]);
printf("3");
    linearSubArray(array1, length[0], msa, &msaSum);		//pass in array, length, pointer for subarr, and pointer to store the sum of subarr
printf("4");	
	printf("msa\n");
printf("5");								/* SEG FAULT HERE
	for(i=0; i<length[0]; i++){	//guessing problem is here, for loop going out of bounds
		printf("%d \n", msa[i]);	//wanted it to print value to console for checking if it was doing it's job
	}
	printf("msaSum is %d \n", msaSum);*/
printf("6");
    free(array1);
    free(array2);
    free(array3);
    free(array4);
    free(array5);
    free(array6);
    free(array7);

    fclose(file);
    fclose(output);
	
	return 0;
}

