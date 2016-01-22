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
    for(i = 0; i < size; i++) {
        if(i < size-1)
            fprintf(file, "%d, ", a[i]);
        else
            fprintf(file, "%d]", a[i]);
    }

    /* Prints maximum subarray */
    fprintf(file, "\n\[");
    for(i = begin; i <= end; i++) {
        if(i < end)
		{
            fprintf(file, "%d, ", a[i]);
		}
        else
		{
            fprintf(file, "%d]", a[i]);
		}

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

    fscanf(file, "%d", &array[i]);

    // Continue until there are no more commas

    do{
		fscanf(file, "%c", &str1);
		fscanf(file, "%d", &array[i]);
        fscanf(file, "%c", &str1);
		i++;

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

void linearSubArray(int a[], int n, FILE *file){
	int i;
	int begin = 0, end = 0, begin_temp = 0;
	int max_so_far = a[0];
	int max_ending_here = a[0];

	for(i = 1; i < n; i++) {
		   if(a[i] > (max_ending_here + a[i])){
			   max_ending_here = a[i];
			   begin_temp = i;
		   } else {
			   max_ending_here = max_ending_here + a[i];
		   }

		   if(max_so_far < max_ending_here) {
			   max_so_far = max_ending_here;
			   if(begin_temp > begin) {
				   begin = begin_temp;
			   }
			   end = i;
		   }
	}

	printArray(file, a, n, begin, end, max_so_far);
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

/* Struct to keep track of maximum sum and maximum subarray in algorithm 3 */
struct Tracker {
    int lo;
    int hi;
    int sum;
};

struct Tracker divAndConMaxSubarrayHelper(int a[], int lo, int hi) {
	//counters
	int i, sum;
	//midpoint
	int midpoint = (lo + hi) / 2;
	//max's found w/ div and conq
    struct Tracker leftMax;
    struct Tracker rightMax;
    struct Tracker tracker;
    //max's found crossing middle iteratively
	int bothMax = 0, bothMaxLeft = 0, bothMaxRight =0;

	//base case, only 1 element in array
	if (lo==hi){
        tracker.sum = a[lo];
        tracker.lo = lo;
        tracker.hi = hi;
        return tracker;
	} else {
        //maximum sum on left
        leftMax = divAndConMaxSubarrayHelper(a, lo, midpoint);
        //max sum on right
        rightMax = divAndConMaxSubarrayHelper(a, midpoint+1, hi);

        //max sum from midpoint
        //find max going left
        sum = 0;
        for (i = midpoint; i >= lo; i--){
            sum += a[i];
            if (sum > bothMaxLeft){
                bothMaxLeft = sum;
                tracker.lo = i;
            }
        }
        //find max going right
        sum = 0;
        for (i = midpoint + 1; i <= hi; i++){
            sum += a[i];
            if (sum > bothMaxRight){
                bothMaxRight = sum;
                tracker.hi = i;
            }
        }
        //combine
        tracker.sum = bothMaxRight + bothMaxLeft;
        if(leftMax.sum >= rightMax.sum && leftMax.sum >= tracker.sum){
            return leftMax;
        } else if(rightMax.sum >= leftMax.sum && rightMax.sum >= tracker.sum) {
            return rightMax;
        } else {
            return tracker;
        }
    }
}

void divAndConMaxSubarray(int a[], int n, FILE *file)
{
    struct Tracker tracker;
    tracker = divAndConMaxSubarrayHelper(a, 0, n-1);
    printArray(file, a, n, tracker.lo, tracker.hi, tracker.sum);
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

void betterEnumMaxSubarray(int a[], int n, FILE *file){
	//counters
	int i, j, begin, end;
	//sum variables
	int sum = 0, best = 0;

	for (i = 0; i < n; i++){
		sum = 0; //new starting term, new sum
		for (j = i; j < n; j++){
			sum += a[j];
			if (sum > best){
                begin = i;
                end = j;
				best = sum; //new winner
			}
		}
	}

	printArray(file, a, n, begin, end, best);
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

void enumMaxSubarray(int a[], int n, FILE *file){
	//counters
    int i, j, k, begin, end;
	int currentArrayLength, maxArrayLength;
	int sum = 0, best = 0;

	for (i = 0; i < n; i++) //first term
	{
		for (j = i; j < n; j++){//last term
			sum = 0;
			currentArrayLength = 0;
			for(k = i; k <= j; k++) //step thru terms
			{
				sum += a[k];
				currentArrayLength++;
			}
				if (sum > best){
                begin = i;
                end = j;
				best = sum; //new record
				maxArrayLength = currentArrayLength;
			}
		}
	}
	printArray(file, a, n, begin, end, best);
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

    divAndConMaxSubarray(array1, length[0], output);
    divAndConMaxSubarray(array2, length[1], output);
    divAndConMaxSubarray(array3, length[2], output);
    divAndConMaxSubarray(array4, length[3], output);
    divAndConMaxSubarray(array5, length[4], output);
    divAndConMaxSubarray(array6, length[5], output);
    divAndConMaxSubarray(array7, length[6], output);

	betterEnumMaxSubarray(array1, length[0], output);
	betterEnumMaxSubarray(array2, length[1], output);
	betterEnumMaxSubarray(array3, length[2], output);
	betterEnumMaxSubarray(array4, length[3], output);
	betterEnumMaxSubarray(array5, length[4], output);
	betterEnumMaxSubarray(array6, length[5], output);
	betterEnumMaxSubarray(array7, length[6], output);

	enumMaxSubarray(array1, length[0], output);
	enumMaxSubarray(array2, length[1], output);
	enumMaxSubarray(array3, length[2], output);
	enumMaxSubarray(array4, length[3], output);
	enumMaxSubarray(array5, length[4], output);
	enumMaxSubarray(array6, length[5], output);
	enumMaxSubarray(array7, length[6], output);

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

