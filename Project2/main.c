#include <stdio.h>
#include <limits.h>

/* Adapted from http://www.geeksforgeeks.org/find-minimum-number-of-coins-that-make-a-change/*/
int changeSlow(int V[], int size, int value) {
    int i, res, sub_res;
   // base case, ya broke
   if (value == 0) return 0;
   // Initialize result
   res = INT_MAX;
   // Try every coin that has smaller value than V
   for (i = 0; i< size; i++) {
     if (V[i] <= value) {
         sub_res = changeSlow(V, size, value-V[i]);
         // Check for INT_MAX to avoid overflow and see if result can minimized
         if ((sub_res != INT_MAX) && (sub_res + 1 < res))
            res = sub_res + 1;
     }
   }
   return res;
}

/*Adapted from http://www.geeksforgeeks.org/find-minimum-number-of-coins-that-make-a-change/ */
int changedp(int V[], int size, int value){
    int i, j;
    // table[i] will be storing the minimum number of coins
    // required for i value.  So table[value] will have result
    int table[value+1];

    // Base case (If given value is 0)
    table[0] = 0;

    // Initialize all table values as Infinite
    for (i = 1; i <= value; i++)
        table[i] = INT_MAX;

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
    return table[value];
}

int changegreedy(int V[], int size, int value){
    int i, currentValue;
    int count = 0, amount = 0;
    int combo[size];    //holds combination of coins used
    
    for(i = 0; i < size; i++){
        combo[i] = 0;   //put 0s in combo
    }

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

    return count;
}


// Driver program to test above function
int main()
{
    int arr[] = {1, 2, 3};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("%d ", changedp(arr, size, 4));
    printf("%d ", changeSlow(arr, size, 4));
    printf("%d ", changegreedy(arr, size, 4));
    return 0;
}
