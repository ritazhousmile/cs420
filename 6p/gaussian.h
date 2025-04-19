#include <stdio.h>
#include <stdlib.h>

/* prototype declarations of functions */

void forwardElimination(double** matrix, int n);
void backSubstitution(double** matrix, double* solution, int n);
void printMatrix(double** matrix, int n);
void printSolution(double* solution, int n);
double** allocateMatrix(int n);
double* allocateSolution(int n);
void freeMatrix(double** matrix, int n);
void freeSolution(double *solution);
void readMatrixFromFile(const char* filename, double** matrix, int n);