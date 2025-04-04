#include <stdio.h>
#include "array2D.h"

void read_array(char filename[30], int arr[][MAX_COLS], int *rows, 
    int *cols){

        FILE *dataFile = fopen(filename, "r");
        if (!dataFile) {
            perror("Error opening input file");
            return;
        }
    
        for (int i = 0; i < *rows; i++) {
            for (int j = 0; j < *cols; j++) {
                if (fscanf(dataFile, "%d", &arr[i][j]) != 1) {
                    fprintf(stderr, "Error reading element at [%d][%d]\n", i, j);
                    fclose(dataFile);
                    return;
                }
            }
        }
    
        fclose(dataFile);

}


void print_array(int arr[][MAX_COLS], int rows, int cols){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d", arr[i][j]);
        }
        printf("\n");
    }

};

float array_average(int arr[][MAX_COLS], int rows, int cols){
    int sum = 0;
    int total = rows * cols;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum += arr[i][j];
        }
    }

    return (float)sum / total;


};
    
void replace_diagonal(int arr[][MAX_COLS], int rows, int cols){
    int size = rows < cols ? rows : cols;
    float avg = array_average(arr, rows, cols);
    int avgInt = (int)(avg + 0.5); // Round to nearest integer

    for (int i = 0; i < size; i++) {
        arr[i][i] = avgInt;
    }

};
    