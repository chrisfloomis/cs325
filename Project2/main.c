#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h> /* memset */
#include <time.h>


struct Array {
    int min;
    int size;
    int* V;
    int* C;
	float total_time;
};

void printResults(FILE *output, int* C, int size, int min) {
	int i;
	fprintf(output, "[");
	for(i = 0; i < size; i++)
	{
		fprintf(output, "%d", C[i]);
		if(i < size-1)
		{
			fprintf(output, ", ");
		}
	}
	fprintf(output, "]\n");
    fprintf(output, "%d\n", min);
}

/* Adapted from http://www.geeksforgeeks.org/find-minimum-number-of-coins-that-make-a-change/*/
struct Array changeSlowHelper(struct Array a, int value) {
    struct Array subProblem;
    int i, minCoins, numCoins;
	clock_t start_time, end_time;

    // base case, ya broke
    if (value == 0) {
        a.min = 0;
        return a;
    }
    // Initialize result
    minCoins = value;
	
	start_time = clock();
    // Try every coin that has smaller value than target Value
    for (i = 0; i< a.size; i++) {
        if (a.V[i] <= value) {
            // Reset coin counts
            memset(a.C, 0, sizeof(int)*a.size);
            subProblem = changeSlowHelper(a, value-a.V[i]);
            // Incrementing the coin
            subProblem.C[i]++;
            numCoins = subProblem.min;
            // Check for INT_MAX to avoid overflow and see if result can minimized
            if ((numCoins != INT_MAX) && (numCoins + 1 < minCoins)) {
                minCoins = numCoins + 1;
                a.C = subProblem.C;
            }
        }
    }
    a.min = minCoins;
	end_time = clock();
    a.total_time =(float)end_time - (float)start_time;

    return a;
}

void changeSlow(int V[], int size, int value, FILE *output){
    // Create Struct to hold Array Information
    struct Array a;
    a.V = V;
    a.size = size;
    int* coinArr = malloc(sizeof(int) * size);
    memset(coinArr, 0, sizeof(int)*size);
    a.C = coinArr;

    a = changeSlowHelper(a, value);

	//print to console the values in our output array
	printf("\n***changeslow***\n");
	printf("C = [");
	int i;
	for(i = 0; i < size; i++)
	{
		printf("%d", a.C[i]);
		if(i < size-1)
		{
			printf(", ");
		}
	}
	printf("]\n");
    printf("m = %d\n", a.min);

    printResults(output, a.C, size, a.min);
	printf("Time: %d\n", a.total_time);

    free(coinArr);
}

/*Adapted from http://www.geeksforgeeks.org/find-minimum-number-of-coins-that-make-a-change/ */
void changedp(int V[], int size, int value, FILE *output){
    int i, j;
    // table[i] will be storing the minimum number of coins
    // required for i value.  So table[value] will have result
    int table[value+1];

    // Base case (If given value is 0)
    table[0] = 0;
	
	float total_time; 
	clock_t start_time, end_time;

	// Initialize all table values as Infinite
    for (i = 1; i <= value; i++) // Constant work not included in the timer.  This is work that we don't care about asymptomatically speaking
        table[i] = INT_MAX;

	start_time = clock();
    // Compute minimum coins required for all
    // values from 1 to value
    for (i = 1; i <= value; i++){
        // Go through all coins smaller than i
        for (j = 0; j < size; j++)
          if (V[j] <= i){
              int sub_res = table[i - V[j]];
              if ((sub_res != INT_MAX) && (sub_res + 1 < table[i]))
                  table[i] = sub_res + 1;
          }
    }
	end_time = clock();
    total_time =(float)end_time - (float)start_time;

	// Not included in timer as this is not part of the asymptomatic analysis
    int countBack = table[value]; //gets number of coins
    int n;

    int combo[size];    //holds combination of coins
    for(i = 0; i < size; i++)
        combo[i] = 0;   //put 0s in combo

    j = value;  //gets value which is used as index

    while(countBack > 0){
        for(i = size-1; i >=0; i--){
            n = j - V[i];
            if(table[n] == table[j]-1){
                combo[i]++;
                j = n;
                countBack--;
            }
        }
    }

	//print to console the values in our output array
	printf("\n***changedp***\n");
	printf("C = [");
	for(i = 0; i < size; i++)
	{
		printf("%d", combo[i]);
		if(i < size-1)
		{
			printf(", ");
		}
	}
	printf("]\n");
    printf("m = %d\n", table[value]);

    printResults(output, combo, size, table[value]);
	printf("Time: %d\n", total_time);
}

void changegreedy(int V[], int size, int value, FILE *output){
    int i, currentValue;
    int count = 0, amount = 0;
    int combo[size];    //holds combination of coins used
	float total_time;
	clock_t start_time, end_time;

	start_time = clock();
    for(i = 0; i < size; i++)
        combo[i] = 0;   //put 0s in combo

    for(i = size - 1; i >= 0; i--) {
        currentValue = V[i];
        while(amount < value ) {
            amount = amount + V[i];
            count++;
            combo[i]++;
        }
        if(amount > value) {
            amount = amount - V[i];
            count--;
            combo[i]--;
        }
    }
	end_time = clock();
	total_time =(float)end_time - (float)start_time;

	//print to console the values in our output array
	printf("\n***changegreedy***\n");
	printf("C = [");
	for(i = 0; i < size; i++)
	{
		printf("%d", combo[i]);
		if(i < size-1)
		{
			printf(", ");
		}
	}
	printf("]\n");
    printf("m = %d\n", count);


    printResults(output, combo, size, count);
	printf("Time: %d\n", total_time);
}

int** buildArrays(FILE* input, int* length, int* target, int* lineCount) {
    char str1;
    int** biggerArray = (int**)malloc(sizeof(int) * 20);
    int i = 0, j;
    while(!feof(input)) {
        j = 0;

        // Extract Array
        int* array = malloc(sizeof(int) * 40);
        fscanf(input, "%c", &str1);
        do {
            fscanf(input, "%d", &array[j]);
            fscanf(input, "%c", &str1);
            j++;
        }while(str1 == ',');

        length[i] = j;
        biggerArray[i] = array;

        //Extract Target Value, strip newlines, store target value
        fscanf(input, "%c", &str1);
        fscanf(input, "%d", &target[i]);
        fscanf(input, "%c", &str1);
        i++;
    }

    *lineCount = i;
    return biggerArray;
}

void destroy(int** arrays, int* lengths, int* targets, int line_count) {
    int i;
    for(i = 0; i < line_count; i++) {
        free(arrays[i]);
    }
    free(arrays);
    free(lengths);
    free(targets);
}

int main(int argc, char *argv[])
{
    int** arrays;
    int* lengths = malloc(sizeof(int) * 20);
    int* targets = malloc(sizeof(int) * 20);
    int line_count;
    FILE *output, *input;
    input = fopen("CoinW16.txt", "r");
    // ! Change to [inputFileName]Change.txt after done with input functions !!
    output = fopen("change.txt", "w");

    arrays = buildArrays(input, lengths, targets, &line_count);

    // Debug Code
    int i, j;
    for(i = 0; i < line_count; i++) {
        printf("ROW %d: ", i);
        for(j = 0; j < lengths[i]; j++) {
            printf("%d ", arrays[i][j]);
        }
        printf("TARGET: %d\n", targets[i]);
    }

    for(i = 0; i < line_count; i++) {
        changedp(arrays[i], lengths[i], targets[i], output);
    }

    /*int arr[] = {1, 2, 4, 8};
	int value = 15;
    int size = sizeof(arr)/sizeof(arr[0]);

    fprintf(output, "changeSlow\n");
    changeSlow(arr, size, value, output);

    fprintf(output, "changedp\n");
    changedp(arr, size, value, output);

    fprintf(output, "changegreedy\n");
	changegreedy(arr, size, value, output);*/

	close(output);
    close(input);
    destroy(arrays, lengths, targets, line_count);

    return 0;
}
