#include "mpn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MPN_MAX_DATA 50  // Define max records

// Fix structure definition


// ✅ Corrected `read_mpn_data()`
int read_mpn_data(FILE *in_file, Bacterial b_array[], int *size) {
    if (!in_file) {
        perror("Error opening file");
        return -1;
    }

    *size = 0;  // Reset size
    while ((*size < MPN_MAX_DATA) &&
           (fscanf(in_file, "%9s %d %d %d", 
                   b_array[*size].combination_of_positives, 
                   &b_array[*size].mpn_index_100ml, 
                   &b_array[*size].lower, 
                   &b_array[*size].upper) == 4)) {
        (*size)++;
    }

    return *size;  // Return the actual size of data read
}

// ✅ Corrected `print_mpn_table()`
void print_mpn_table(FILE *output_file, int size, Bacterial arr[]) {
    if (!output_file) {
        perror("Error opening output file");
        return;
    }

    // Print to console
    printf("Table of Bacterial Concentrations for Most Probable Number Method\n");
    printf("+------------+------------+---------------------+\n");
    printf("| Combination| MPN Index  | 95%% Confidence Limits |\n");
    printf("|            | (per 100ml)| Lower    | Upper    |\n");
    printf("+------------+------------+----------+----------+\n");

    // Write to file
    fprintf(output_file, "Table of Bacterial Concentrations for Most Probable Number Method\n");
    fprintf(output_file, "+------------+------------+---------------------+\n");
    fprintf(output_file, "| Combination| MPN Index  | 95%% Confidence Limits |\n");
    fprintf(output_file, "|            | (per 100ml)| Lower    | Upper    |\n");
    fprintf(output_file, "+------------+------------+----------+----------+\n");

    for (int i = 0; i < size; i++) {
        printf("| %-10s | %-10d | %-8d | %-8d |\n",
               arr[i].combination_of_positives,
               arr[i].mpn_index_100ml,
               arr[i].lower,
               arr[i].upper);

        fprintf(output_file, "| %-10s | %-10d | %-8d | %-8d |\n",
                arr[i].combination_of_positives,
                arr[i].mpn_index_100ml,
                arr[i].lower,
                arr[i].upper);
    }

    // Print closing table line
    printf("+------------+------------+----------+----------+\n");
    fprintf(output_file, "+------------+------------+----------+----------+\n");
}

// ✅ Corrected `search_mpn_table()`
int search_mpn_table(Bacterial arr[], int size, char userInput[]) {
    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i].combination_of_positives, userInput) == 0) {
            return i;  // Return index if found
        }
    }
    return -1;  // Return -1 if not found
}
