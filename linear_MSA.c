/*
Authors:        Benjamin Tullis, Dalena Pham, Chris Loomis
Filename:       linear_MSA.c
Created On:     01/18/2016
Last Mod:       01/18/2016

Adapted from https://en.wikipedia.org/wiki/Maximum_subarray_problem

Algorithm 4: Linear Time
Use the following ideas to develop a nonrecursive linear time algorithm. Start
at the left end of the array and progress towards the right, keeping track of the maximum subarray sum
seen so far. Knowing a maximum subarray of A[1 . . j], extend the answer to find a maximum subarray
ending at index j+1 by using the following observation: a maximum subarray of A[1 . . j+1] is either a
maximum subarray of A[1 . . j] or a subarray A[i . . j+1], for some 1 ≤ i ≤ j+1. Determine a maximum
subarray of the form A[i . . j+1] in constant time based on knowing a maximum subarray ending at
index j.
*/
#include <stdio.h>
#include <stdlib.h>
int linearSubArray(int a[], int n){
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
	return max_so_far;
}

