
/*
typedef struct {
    char combination_of_positives;
    int mpn_index_100ml;
    int lower;
    int upper;
}bacterial;

#define MPN_MAX_DATA 50

int read_mpn_data(File *in_file, bacterial b_array[], int *size);
void print_mpn_table(File output_file,int size, bacterial arr[]);
int search_mpn_table(bacterial arr[], int size, char userInput);
*/
#include <stdio.h>
#include <string.h>

#define MPN_MAX_DATA 50  // Maximum data records

// Define the structure properly
typedef struct {
    char combination_of_positives[10];  // Changed to array to store strings like "4-2-0"
    int mpn_index_100ml;
    int lower;
    int upper;
} Bacterial;  // Capitalized struct name for clarity

// Function Prototypes
int read_mpn_data(FILE *in_file, Bacterial b_array[], int *size);
void print_mpn_table(FILE *output_file, int size, Bacterial arr[]);
int search_mpn_table(Bacterial arr[], int size, char userInput[]);