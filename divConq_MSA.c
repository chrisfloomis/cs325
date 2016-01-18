/*
Authors:        Benjamin Tullis, Dalena Pham, Chris Loomis
Filename:       divConq_MSA.c
Created On:     01/18/2016
Last Mod:       01/18/2016

Code sourced from Samuel Snyder https://github.com/samuelsnyder/max-sum-sub-array/blob/master/a3.c

Finding the maximum sub-array
Divide and Conquer
If we split the array into two halves, we know that the maximum
subarray will either be
• contained entirely i n the first half,
•contained entirely in the second half, or
•made of a suffix of the first half of maximum sum and a prefix of the second half of maximum sum
The first two cases can be found recursively. The last case can be found in linear time
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h> //fmax

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