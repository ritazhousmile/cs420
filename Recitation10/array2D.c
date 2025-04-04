/*=======================================================*/
/*=======================================================*/
#include <stdio.h>
#include "array2D.h"

/*=======================================================*/
int main(void){
    int array[MAX_ROWS][MAX_COLS];
	float average = 0;
	char filename[30];
	int rows, cols;
	char line[256];

	printf("Enter Data File Name:");
	scanf("\n%s", filename);

	FILE *dataFile = fopen(filename, "r");
    if (!dataFile) {
        perror("Error opening input file");
        return 1;
    }

	// Read dimensions from the file
    if (fscanf(dataFile, "%d %d", &rows, &cols) != 2) {
        fprintf(stderr, "Failed to read dimensions from file.\n");
        fclose(dataFile);
        return 1;
    }


	read_array(filename, array, &rows, &cols);

	printf("\nOriginal Array:\n");
    print_array(array, rows, cols);

    float avg = array_average(array, rows, cols);
    printf("\nAverage of array elements: %.2f\n", avg);

    replace_diagonal(array, rows, cols);
    printf("\nArray after replacing diagonal with average:\n");
    print_array(array, rows, cols);

    return 0;
}
