/*
Authors:        Benjamin Tullis, Dalena Pham, Chris Loomis
Filename:       enum_MSA.c
Created On:     01/18/2016
Last Mod:       01/18/2016

Code sourced from Samuel Snyder https://github.com/samuelsnyder/max-sum-sub-array/blob/master/a1.c

Find Max Subarray by Enumeration
Loop over each pair of indices
i, j and compute the sum,
Sigma(f)(k=i) a[k] 
Keep the best sum you have found so far
*/

#include <stdio.h>

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