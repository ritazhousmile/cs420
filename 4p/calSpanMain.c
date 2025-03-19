/**
 * @author huan zhou
 *calSpanMain.c
 *Main function to test calSpan
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototype for calSpan
int calSpan(int maxSize, char *filename, double data[]);

int main(int argc, char *argv[]) {
    // Check if filename is provided as command-line argument
    if (argc != 2) {
        printf("Usage: %s <data_filename>\n", argv[0]);
        return 1;
    }
    
    // Define maximum size of data
    const int MAX_SIZE = 1000;
    
    // Allocate memory for data array
    double *data = (double *)malloc(MAX_SIZE * sizeof(double));
    if (data == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    // Call calSpan function with provided filename
    int result = calSpan(MAX_SIZE, argv[1], data);
    
    // Check result
    if (result == -1) {
        printf("Error: Could not open file '%s'\n", argv[1]);
    } else {
        printf("\nFile processing complete. Read %d data values.\n", result);
    }
    
    // Free allocated memory
    free(data);
    
    return 0;
}