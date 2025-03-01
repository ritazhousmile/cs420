/**
 * regression.c
 * @author huan zhou
 * 
 */

#include <stdio.h>
#include <math.h>

/**
  * read_data - Reads data pairs from a file into arrays
  */
int read_data(char filename[], double x[], double y[]) {
     FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return -1;
    }

    int count = 0;
    while (count < 1000 && fscanf(fp, "%lf %lf", &x[count], &y[count]) == 2) {
        count++;
    }

    fclose(fp);
    return count;
}

/**
  * echo_data - Prints the contents of the input arrays
  */
void echo_data(int size, double x[], double y[]) {
    printf("Data read from file:\n");
    printf("%-10s %-10s\n", "Load", "Compression");
    printf("%-10s %-10s\n", "----------", "----------");
    
    for (int i = 0; i < size; i++) {
        printf("%-10.4f %-10.4f\n", x[i], y[i]);
    }
    printf("\n");
}

/**
  * compute_regression_coefficients - Calculates slope and y-intercept for linear regression
  */
 void compute_regression_coefficients(int size, double x[], double y[], double *slope, double *yint) {
    double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_x2 = 0.0;
    
    for (int i = 0; i < size; i++) {
        sum_x += x[i];
        sum_y += y[i];
         sum_xy += x[i] * y[i];
         sum_x2 += x[i] * x[i];
    }
    
    double mean_x = sum_x / size;
    double mean_y = sum_y / size;
    
     // Calculate slope and y-intercept
     *slope = (size * sum_xy - sum_x * sum_y) / (size * sum_x2 - sum_x * sum_x);
     *yint = mean_y - (*slope) * mean_x;
}

/**
  * compute_fx_residues - Calculates estimated values and residuals
  */
void compute_fx_residues(int size, double x[], double y[], double slope, double yint, double fx[], double r[]) {
    for (int i = 0; i < size; i++) {
         fx[i] = slope * x[i] + yint;    // Calculate estimated value
         r[i] = y[i] - fx[i];            // Calculate residual
    }
}

/**
  * compute_correlation - Calculates correlation metrics
  */
 void compute_correlation(int size, double r[], double y[], double *sum_residuals, double *sum_squares, double *coeff_of_determination) {
    double sum_y = 0.0;
     *sum_residuals = 0.0;
     *sum_squares = 0.0;
    
     // Calculate sum of y values for mean
    for (int i = 0; i < size; i++) {
        sum_y += y[i];
    }
    
    double mean_y = sum_y / size;
    
     // Calculate sum of squared residuals and total sum of squares
    for (int i = 0; i < size; i++) {
         *sum_residuals += r[i] * r[i];             // Sum of squared residuals
         *sum_squares += pow(y[i] - mean_y, 2);     // Total sum of squares
    }
    
     // Calculate coefficient of determination
     *coeff_of_determination = 1.0 - (*sum_residuals / *sum_squares);
}

/**
  * compute_pearson_coefficient - Calculates Pearson correlation coefficient
  */
double compute_pearson_coefficient(int size, double x[], double y[]) {
    double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_x2 = 0.0, sum_y2 = 0.0;
    
    for (int i = 0; i < size; i++) {
        sum_x += x[i];
        sum_y += y[i];
         sum_xy += x[i] * y[i];
         sum_x2 += x[i] * x[i];
         sum_y2 += y[i] * y[i];
    }
    
     // Calculate Pearson correlation coefficient
     double numerator = size * sum_xy - sum_x * sum_y;
     double denominator = sqrt((size * sum_x2 - sum_x * sum_x) * (size * sum_y2 - sum_y * sum_y));
    
    return numerator / denominator;
}