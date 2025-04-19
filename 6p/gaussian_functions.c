/** @author: huan zhou
*@version：1
6p
 */

#include "gaussian.h"
#include <math.h>  /* For fabs() function */

/* Function to allocate memory for the augmented matrix */
double** allocateMatrix(int n) {
    double** matrix = (double**)malloc(n * sizeof(double*));
    if (matrix == NULL) {
        printf("Memory allocation failed for matrix rows\n");
        exit(1);
    }
    
    for (int i = 0; i < n; i++) {
        matrix[i] = (double*)malloc((n + 1) * sizeof(double));
        if (matrix[i] == NULL) {
            printf("Memory allocation failed for matrix columns\n");
            
            // Free previously allocated memory
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            
            exit(1);
        }
    }
    
    return matrix;
}

/* Function to allocate memory for the solution array */
double* allocateSolution(int n) {
    double* solution = (double*)malloc(n * sizeof(double));
    if (solution == NULL) {
        printf("Memory allocation failed for solution array\n");
        exit(1);
    }
    
    return solution;
}

/* Function to read matrix data from the file */
void readMatrixFromFile(const char* filename, double** matrix, int n) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    
    // Skip the first line which contains the number of unknowns
    int dummy;
    fscanf(file, "%d", &dummy);
    
    // Read the matrix values
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            fscanf(file, "%lf", &matrix[i][j]);
        }
    }
    
    fclose(file);
}

/* Function to perform forward elimination with partial pivoting */
void forwardElimination(double** matrix, int n) {
    for (int k = 0; k < n - 1; k++) {
        // Find the pivot (row with maximum absolute value in current column)
        int maxRow = k;
        double maxVal = fabs(matrix[k][k]);
        
        for (int i = k + 1; i < n; i++) {
            if (fabs(matrix[i][k]) > maxVal) {
                maxVal = fabs(matrix[i][k]);
                maxRow = i;
            }
        }
        
        // Swap the pivot row with the current row if needed
        if (maxRow != k) {
            for (int j = 0; j <= n; j++) {
                double temp = matrix[k][j];
                matrix[k][j] = matrix[maxRow][j];
                matrix[maxRow][j] = temp;
            }
        }
        
        // Make all elements below the pivot zero
        for (int i = k + 1; i < n; i++) {
            double factor = matrix[i][k] / matrix[k][k];
            
            for (int j = k; j <= n; j++) {
                matrix[i][j] -= factor * matrix[k][j];
            }
        }
    }
}

/* Function to perform back substitution */
void backSubstitution(double** matrix, double* solution, int n) {
    // Solve for the last unknown first
    solution[n - 1] = matrix[n - 1][n] / matrix[n - 1][n - 1];
    
    // Solve for the rest of the unknowns
    for (int i = n - 2; i >= 0; i--) {
        double sum = 0.0;
        
        for (int j = i + 1; j < n; j++) {
            sum += matrix[i][j] * solution[j];
        }
        
        solution[i] = (matrix[i][n] - sum) / matrix[i][i];
    }
}

/* Function to print the matrix */
void printMatrix(double** matrix, int n) {
    // Print the top border
    printf("+");
    for (int j = 0; j < n; j++) {
        printf("=========+");
    }
    printf("=========+\n");
    
    // Print each row
    for (int i = 0; i < n; i++) {
        printf("|");
        for (int j = 0; j <= n; j++) {
            printf("%8.2f |", matrix[i][j]);
        }
        printf("\n");
        
        // Print row separator
        printf("+");
        for (int j = 0; j < n; j++) {
            printf("=========+");
        }
        printf("=========+\n");
    }
}

/* Function to print the solution */
void printSolution(double* solution, int n) {
    printf("(");
    for (int i = 0; i < n; i++) {
        printf("%.6f", solution[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

/* Function to free the matrix memory */
void freeMatrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

/* Function to free the solution array memory */
void freeSolution(double* solution) {
    free(solution);
}
int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Usage: %s <data file>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    FILE* file = fopen(filename, "r");
    if(file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);
    fclose(file);

    double** matrix = allocateMatrix(n);
    readMatrixFromFile(filename, matrix, n);
	
	printf("Augmented Matrix\n");
	printMatrix(matrix, n);

    forwardElimination(matrix, n);

	printf("\nFinal Matrix\n");
	printMatrix(matrix, n);

    double* solution = allocateSolution(n);
    backSubstitution(matrix, solution, n);

	printf("\nSolution is: ");
    printSolution(solution, n);

    freeMatrix(matrix, n);
	freeSolution(solution);

    return 0;
}
