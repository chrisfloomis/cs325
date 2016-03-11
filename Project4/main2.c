#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h> /* memset */
#include <time.h>
#include <math.h>


int pythag(int x1, int x2, int y1, int y2){
	return round(sqrt(pow((x1-x2),2) + pow((y1-y2),2)));
}

/* Returns the number of cities in given inputFile */
int lineCounter(char* inputFile) {
    FILE *input;
    char str1;
    int holder, lineCount, i = 0;
    input = fopen(inputFile, "r");
    while(!feof(input)) {
        fscanf(input, "%d", &holder);
        fscanf(input, "%d", &holder);
        fscanf(input, "%d", &holder);
        fscanf(input, "%c", &str1);
        i++;
    }
    lineCount = i - 1;
    close(input);
    return lineCount;
}


int main(int argc, char *argv[]){
    int i, j, k;
    int largeFile = 0;              // Program will change behavior depending on number of cities given
	clock_t start_time, end_time;
	float total_time;

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

    /* Determine number of cities from inputFile*/
    int lineCount = lineCounter(inputFile);

    /* Extract city information and save to array */
    int cities[lineCount][3];
    input = fopen(inputFile, "r");
    i = 0;
    char str1;
    while(!feof(input)) {
        // Extract City Identifier
        fscanf(input, "%d", &cities[i][0]);
        // Extract x-coordinate
        fscanf(input, "%d", &cities[i][1]);
        // Extract y-coordinate
        fscanf(input, "%d", &cities[i][2]);
        // Strip newline
        fscanf(input, "%c", &str1);
        i++;
    }

    /* Determine the number of times to loop in the greedy loop
        Behavior of program changes if given an extremely large input
        to save time */
    int greedyCount;
    if(lineCount > 2000) {
        greedyCount = 1;
        largeFile = 1;
    } else {
        greedyCount = lineCount;
    }

    /* Route variable structure:
     1st element is the total distance of path (route[0])
     Subsequent elements are the actual path traversal (route[1] ... route[lineCount + 1])*/

    /* Where the magic happens */
	int tempRoute [lineCount + 1];                  // Keep track of temporary route
	int minRoute [lineCount + 1];                   // Will hold the overall minimum route
    int visited [lineCount];
    int distance, tempDistance, minDistance, minDistance_all;
    int current, candidateCity, originCity;

    // For every city
    minDistance_all = INT_MAX;
	start_time = clock();
    for(i = 0; i < greedyCount; i++) {
        distance = 0;

        // First city is current city
        originCity = i;
        if(largeFile) {
            srand(time(NULL));
            originCity = (rand()% lineCount + 1);
        }
        current = originCity;

       // Initialize visited array to 0
        for(j = 0; j < lineCount; j++) {
            visited[j] = 0;
            if (j == current) {
                visited[j] = 1;
            }
        }

        // First city in route is current city
        tempRoute[1] = current;

        // Visit all the cities
        for(k = 1; k < lineCount; k++) {
            minDistance = INT_MAX;
            // Evaluate each unvisited city as the next candidate city
            for(j = 0; j < lineCount; j++) {
                if(visited[j] == 0) {
                    // Check distance from current city to candidate city
                    tempDistance = pythag(cities[current][1],cities[j][1],cities[current][2],cities[j][2]);
                    //tempDistance = costM[current][j];
                    // Keep track of the closest candidate city
                    if(tempDistance < minDistance) {
                        minDistance = tempDistance;
                        candidateCity = j;
                    }
                }
            }

            // Save and move to best candidate city
            visited[candidateCity] = 1;
            tempRoute[k + 1] = candidateCity;
            current = candidateCity;
            distance += minDistance;
        }

        // Get final distance back to original city
        tempDistance = pythag(cities[current][1],cities[originCity][1],cities[current][2],cities[originCity][2]);
        distance += tempDistance;
        tempRoute[0] = distance;

        // If this route produces a smaller distance, keep it
        if(distance < minDistance_all) {
            minDistance_all = distance;
            for(j = 0; j < lineCount + 1; j++) {
                minRoute[j] = tempRoute[j];
            }
        }
    }

	end_time = clock();
	total_time =(float)end_time - (float)start_time;
    /* End Magic */

    /* Write best route to .tour file */
    for(i = 0; i < lineCount + 1; i++) {
        fprintf(output, "%d\n", minRoute[i]);
    }

    /* Print to Screen General Results and Time */
	printf("Time: %f\n", total_time);
	printf("Tour Length: %d\n", minRoute[0]);

	close(output);
    close(input);
    return 0;
}
