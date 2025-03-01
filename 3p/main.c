/**
 * main.c
 * @author huan zhou
 * @version 1
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 1000

 /* Function prototypes - these should match those in regression.h */
int read_data(char filename[], double x[], double y[]);
void echo_data(int size, double x[], double y[]);
void compute_regression_coefficients(int size, double x[], double y[], double *slope, double *yint);
void compute_fx_residues(int size, double x[], double y[], double slope, double yint, double fx[], double r[]);
void compute_correlation(int size, double r[], double y[], double *sum_residuals, double *sum_squares, double *coeff_of_determination);
double compute_pearson_coefficient(int size, double x[], double y[]);

 int main(int argc, char *argv[]) {
     double x[MAX];      // Array for load values
     double y[MAX];      // Array for compression values
     double fx[MAX];     // Array for estimated compression values
     double r[MAX];      // Array for residuals
     double slope, yint; // Slope and y-intercept
     double sum_residuals, sum_squares, coeff_of_determination; // Correlation metrics
     double pearson;     // Pearson correlation coefficient
     int size;           // Number of data points
    
     // Check command line arguments
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }
    
     // Read data from file
    size = read_data(argv[1], x, y);
    if (size < 0) {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }
    
    printf("Successfully read %d data points from file %s\n\n", size, argv[1]);
    
     // Display the data
    echo_data(size, x, y);
    
     // Compute regression coefficients
    compute_regression_coefficients(size, x, y, &slope, &yint);
    
     // Print regression equation
    printf("Linear Regression Equation: f(x) = %.6f * x + %.6f\n\n", slope, yint);
    
     // Compute estimated values and residuals
    compute_fx_residues(size, x, y, slope, yint, fx, r);
    
     // Display results in tabular format
    printf("%-10s %-15s %-15s %-15s\n", "Load", "Observed", "Estimated", "Residual");
    printf("%-10s %-15s %-15s %-15s\n", "----------", "---------------", "---------------", "---------------");
    
    for (int i = 0; i < size; i++) {
        printf("%-10.4f %-15.6f %-15.6f %-15.6f\n", x[i], y[i], fx[i], r[i]);
    }
    printf("\n");
    
     // Compute correlation metrics
    compute_correlation(size, r, y, &sum_residuals, &sum_squares, &coeff_of_determination);
    
     // Display correlation results
    printf("Correlation Results (Least Squares Method):\n");
    printf("Sum of Squared Residuals: %.6f\n", sum_residuals);
    printf("Total Sum of Squares: %.6f\n", sum_squares);
    printf("Coefficient of Determination: %.6f\n\n", coeff_of_determination);
    
     // Compute and display Pearson correlation coefficient
    pearson = compute_pearson_coefficient(size, x, y);
    printf("Pearson Correlation Results:\n");
    printf("Pearson Correlation Coefficient: %.6f\n", pearson);
    
    return 0;
}