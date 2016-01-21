#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h> //fmax


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
	fprintf(file, "\n");
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


/* 
Authors:        Benjamin Tullis, Dalena Pham, Chris Loomis
Filename:       linear_MSA.c
Created On:     01/18/2016
Last Mod:       01/18/2016

Adapted from https://en.wikipedia.org/wiki/Maximum_subarray_problem

***ALGORITHM 4: Linear Time
Modified linearSubArray method that will output the array assessed, the maximum
subarray and the maximum sum
	
Use the following ideas to develop a nonrecursive linear time algorithm. Start
at the left end of the array and progress towards the right, keeping track of the maximum subarray sum
seen so far. Knowing a maximum subarray of A[1 . . j], extend the answer to find a maximum subarray
ending at index j+1 by using the following observation: a maximum subarray of A[1 . . j+1] is either a
maximum subarray of A[1 . . j] or a subarray A[i . . j+1], for some 1 ≤ i ≤ j+1. Determine a maximum
subarray of the form A[i . . j+1] in constant time based on knowing a maximum subarray ending at
index j.
*/

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
}

/*
Authors:        Benjamin Tullis, Dalena Pham, Chris Loomis
Filename:       divConq_MSA.c
Created On:     01/18/2016
Last Mod:       01/18/2016

Code sourced from Samuel Snyder https://github.com/samuelsnyder/max-sum-sub-array/blob/master/a3.c

***ALGORITHM 3: Divide and Conquer
Finding the maximum sub-array
Divide and Conquer
If we split the array into two halves, we know that the maximum
subarray will either be
• contained entirely i n the first half,
•contained entirely in the second half, or
•made of a suffix of the first half of maximum sum and a prefix of the second half of maximum sum
The first two cases can be found recursively. The last case can be found in linear time
*/


int divAndConMaxSubarray(int a[], int lo, int hi)
{
	//int* sumArray = malloc((hi - lo) * sizeof(int)); //for storing winning array, 
		//maybe don't need
	
	//midpoint of array
	int midpoint;
	
	//max's found w/ div and conq
	int leftMax=0;
	int rightMax=0;

	//max's found crossing middle iteratively
	int bothMax=0;
	int bothMaxLeft=0;
	int bothMaxRight=0;

	//counters
	int i, sum;

	//base case, only 1 element in array
	//TODO: ensure no issue w/ no elements
	if (lo==hi) { //lo and hi are the same element
		return a[hi]; //sum is this element alone
	}

	//divide  array into two halves
	midpoint = (lo + hi)/2;

	//maximum of 

		//maximum sum on left
		//recursive call

	
	leftMax = divAndConMaxSubarray(a, lo, midpoint);

		//max sum on right
		//recursive call
	
	rightMax = divAndConMaxSubarray(a, midpoint+1, hi);

		//max sum from midpoint
			//find max going left

	bothMaxLeft = 0;
	sum = 0;
	for (i = midpoint-1; i >=0; i-- ){
		sum += a[i];
		if (sum > bothMaxLeft)
			bothMaxLeft = sum;
	}
	
			//find max going right
	bothMaxRight = 0;
	sum = 0;
	for (i = midpoint; i < hi; i++ ){
		sum += a[i];
		if (sum > bothMaxRight)
			bothMaxRight = sum;
	}
			//combine
	bothMax = bothMaxRight + bothMaxLeft;

	return fmax(bothMax, fmax(leftMax, rightMax));
}


/*
Authors:        Benjamin Tullis, Dalena Pham, Chris Loomis
Filename:       betterEnum_MSA.c
Created On:     01/18/2016
Last Mod:       01/18/2016

Code sourced from Samuel Snyder https://github.com/samuelsnyder/max-sum-sub-array/blob/master/a2.c

***ALGORITHM 2: Better Enumeration
Notice that in the previous algorithm, 
the same sum is computed many
times. In particular, notice that Sigma(j)(k=i)a[k] 
can be computed from
Sigma(j-1)(k=1)a[k] in O(1) time, rather than
starting from scratch. Write a new version 
of the first algorithm that takes advantage 
of this observation
*/

int betterEnumMaxSubarray(int a[], int n, FILE *file){

	//counters
	int i, j; //1st term, curr term
	//don't need last term, go to the end every run
	
	//variables to store arrays
	/* array variables here */

	//sum variables
	int sum = 0;
	int best = 0;

	for (i = 0; i < n; i++){
		sum = 0; //new starting term, new sum
		for (j = i; j < n; j++){
			sum += a[j];
			if (sum > best){
				best = sum; //new winner

				/*
				TODO copy array segment here maybe
				*/
			}
		}
	}
	printArray(file, a, n, 0, 0, best);

	return best;
}


/*
Authors:        Benjamin Tullis, Dalena Pham, Chris Loomis
Filename:       enum_MSA.c
Created On:     01/18/2016
Last Mod:       01/18/2016

Code sourced from Samuel Snyder https://github.com/samuelsnyder/max-sum-sub-array/blob/master/a1.c

***ALGORITHM 1: Enumeration
Find Max Subarray by Enumeration
Loop over each pair of indices
i, j and compute the sum,
Sigma(f)(k=i) a[k] 
Keep the best sum you have found so far
*/

/*
Pre: a[] is an array of integers of length n
Post: a[] is now the max subarray
Returns: int which represents greatest sum in 
	subarray
*/


int enumMaxSubarray(int a[], int n){
	

	//counters
	int i; //pos of first term in subarray 
	int j; //last term in subarray
	int k; //current term in subarray

	//int currentArray [n];
	int currentArrayLength;
	//int maxArray [n];
	int maxArrayLength;
	int sum = 0;
	int best = 0;

	for (i = 0; i < n; i++) //first term
	{
		for (j = i; j < n; j++){//last term
			sum = 0;//
			//eraseArray(currentArray);
			currentArrayLength = 0;
			for(k = i; k <= j; k++) //step thru terms
			{
				sum += a[k];
				//currentArray[(k-i)] = a[k];
				currentArrayLength++;
			}
				if (sum > best){
				best = sum; //new record
				maxArrayLength = currentArrayLength;
				//copyArray(currentrrentArray, maxArray, maxArrayLength);
			}
		} 
	}
	return best;
}


int main(int argc, char *argv[]) {
    FILE *file, *output;
    file = fopen(argv[1], "r");
    output = fopen("MSS_Results.txt", "a");
    int* array1, *array2, *array3, *array4, *array5, *array6, *array7;
    int length[7];

    array1 = buildArray(40, file, &length[0]);
    array2 = buildArray(40, file, &length[1]);
    array3 = buildArray(40, file, &length[2]);
    array4 = buildArray(40, file, &length[3]);
    array5 = buildArray(40, file, &length[4]);
    array6 = buildArray(40, file, &length[5]);
    array7 = buildArray(40, file, &length[6]);

	linearSubArray(array1, length[0], output);
	linearSubArray(array2, length[1], output);
	linearSubArray(array3, length[2], output);
	linearSubArray(array4, length[3], output);
	linearSubArray(array5, length[4], output);
	linearSubArray(array6, length[5], output);
	linearSubArray(array7, length[6], output);

	//betterEnumMaxSubarray(array1, length[0], output);


    free(array1);
    free(array2);
    free(array3);
    free(array4);
    free(array5);
    free(array6);
    free(array7);

    fclose(file);
    fclose(output);
}

