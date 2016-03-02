/* Project 3
    Christopher Loomis
    Benjamin Tullis
    Dalena Pham
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h> /* memset */
#include <time.h>

int** buildArrays(FILE* input, int* lineCount) {
    char str1;
    // Look into a way to not have to hard-code this?
    int** biggerArray = (int**)malloc(sizeof(int) * 20000);
    int i = 0;
    while(!feof(input)) {

        // Extract Array
        int* array = malloc(sizeof(int) * 3);
        // Extract City Identifier
        fscanf(input, "%d", &array[0]);
        // Extract 2nd city x-coordinate
        fscanf(input, "%d", &array[1]);
        // Extract 3rd city y-coordinate
        fscanf(input, "%d", &array[2]);
        // Strip newline
        fscanf(input, "%c", &str1);

        biggerArray[i] = array;
        i++;
    }

    *lineCount = i - 1;
    return biggerArray;
}

void destroy(int** arrays, int line_count) {
    int i;
    for(i = 0; i < line_count; i++) {
        free(arrays[i]);
    }
    free(arrays);
}


int main(int argc, char *argv[]){
    int i, j;

    /* File Input/Output Variables */
    FILE *output, *input;
    char* endFile = ".tour";
    char* outputFile;
    char* inputFile = argv[1];
    input = fopen(inputFile, "r");

    /* Creating .tour output file */
    int len = strlen(inputFile);
    char fileName[len];
    for (i=0; i< len; i++) {
        fileName[i] = inputFile[i];
	}
    outputFile = strcat(fileName, endFile);
    output = fopen(outputFile, "w");

    /* Copy Arrays */
    int** arrays;
    int line_count;
    arrays = buildArrays(input, &line_count);

    // Debug Code
    for(i = 0; i < line_count; i++) {
        for(j = 0; j < 3; j++) {
            printf("%d ", arrays[i][j]);
        }
        printf("\n");
    }

    destroy(arrays, line_count);
	close(output);
    close(input);
    return 0;
}
