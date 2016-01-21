/*
Authors:        Benjamin Tullis, Dalena Pham, Chris Loomis
Group:			9
Filename:       betterEnum_MSA.c
Created On:     01/18/2016
Last Mod:       01/18/2016

Code sourced from Samuel Snyder https://github.com/samuelsnyder/max-sum-sub-array/blob/master/a2.c

Algorithm 2: Better Enumeration
Notice that in the previous algorithm, 
the same sum is computed many
times. In particular, notice that Sigma(j)(k=i)a[k] 
can be computed from
Sigma(j-1)(k=1)a[k] in O(1) time, rather than
starting from scratch. Write a new version 
of the first algorithm that takes advantage 
of this observation
*/

#include "msa.h"
#include <stdio.h>

int betterEnumMaxSubarray(int a[], int n){

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
	return best;
}