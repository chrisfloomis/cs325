#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h> /* memset */
#include <time.h>
#include <math.h>

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
        // Extract x-coordinate
        fscanf(input, "%d", &array[1]);
        // Extract y-coordinate
        fscanf(input, "%d", &array[2]);
        // Strip newline
        fscanf(input, "%c", &str1);

        biggerArray[i] = array;
        i++;
    }

    *lineCount = i - 1;
    return biggerArray;
}

int pythag(int x1, int x2, int y1, int y2){
	return round(sqrt(pow((x1-x2),2) + pow((y1-y2),2)));
}

//takes the biggerArray of the cities and the number of them
//creates and returns a cost matrix of each city to each other city
//costMatrix[0][1] will hold the distance from the first city read in from input to the second read from input
int** buildCostMatrix(int** cities, int lineCount){
	int i,j;
	int** costMatrix = (int**)malloc(sizeof(int) * 20000);	//copy/paste from buildArrays()
	//for each city
	for(i = 0; i < lineCount; i++){
        // allocate space for row
        int* row = malloc(sizeof(int) * lineCount);
		//call pythag from current city to each other city
		for(j = 0; j < lineCount; j++){
			if(i == j)
				row[j] = INT_MAX;
			else
				row[j] = pythag(cities[i][1],cities[j][1],cities[i][2],cities[j][2]);
		}
        costMatrix[i] = row;
	}
	return costMatrix;
}

/* Deallocates reserved memory */
void destroy(int** cities, int** costM, int line_count) {
    int i;
    for(i = 0; i < line_count; i++) {
        free(cities[i]);
        free(costM[i]);
    }
    free(cities);
    free(costM);
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

    /* Copy Cities */
    int** cities;
    int lineCount;
    cities = buildArrays(input, &lineCount);

    /* Create Cost Matrix */
    int** costM;
    costM = buildCostMatrix(cities, lineCount);


    // Route variable structure:
    // 1st element is the total distance of path
    // Subsequent elements are the actual path traversal

    /* Where the magic happens */
    int routeTable[lineCount][lineCount + 1];
    int visited [lineCount];
    int whileCounter;
    int distance, tempDistance, minDistance;
    int current, candidateCity;

    // For every city
    for(i = 0; i < lineCount; i++) {
        whileCounter = lineCount - 1;
        distance = 0;

       // Initialize visited array to 0
        for(j = 0; j < lineCount; j++) {
            visited[j] = 0;
            if (j == i) {
                visited[j] = 1;
            }
        }

        // First city is current city
        current = i;
        // First city in route is current city
        routeTable[i][1] = current;

        int k;
        // We have lineCount visits to check and visit
        for(k = 1; k < lineCount; k++) {
            minDistance = INT_MAX;
            // Evaluate each unvisited city as a next candidate
            for(j = 0; j < lineCount; j++) {
                if(visited[j] == 0) {
                    // Check distance from current city to candidate city
                    tempDistance = costM[current][j];
                    // Keep track of the closest candidate city
                    if(tempDistance < minDistance) {
                        minDistance = tempDistance;
                        candidateCity = j;
                    }
                }
            }
            // Save and move to best candidate city
            visited[candidateCity] = 1;
            routeTable[i][k + 1] = candidateCity;
            current = candidateCity;
            distance += minDistance;
        }

        // Get final distance back to original city
        //tempDistance = costM[current][i];
        tempDistance = costM[current][i];
        distance += tempDistance;
        routeTable[i][lineCount+1] = i;
        routeTable[i][0] = distance;
    }

    minDistance = INT_MAX;
    int optimal_route;
    // Find the route with the lowest distance
    for(i = 0; i < lineCount; i++) {
        if(routeTable[i][0] < minDistance) {
            minDistance = routeTable[i][0];
            optimal_route = i;
        }
    }
    /* End Magic */

    for(i = 0; i < lineCount + 1; i++) {
        fprintf(output, "%d\n", routeTable[optimal_route][i]);
    }

    destroy(cities, costM, lineCount);
	close(output);
    close(input);
    return 0;
}
