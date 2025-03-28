#include "mpn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Main function
int main(int argc, char *argv[]) {
    Bacterial bact[MPN_MAX_DATA]; // Array to store bacteria data
    int size = 0;  // Initialize size

    // Check if the correct number of arguments is supplied
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1; // Return error
    }

    // Open input file
    FILE *infile = fopen(argv[1], "r");
    if (!infile) {
        perror("Error opening input file");
        return 1;
    }

    // Open output file
    FILE *outfile = fopen(argv[2], "w");
    if (!outfile) {
        perror("Error opening output file");
        fclose(infile);
        return 1;
    }

    // Read data from input file
    size = read_mpn_data(infile, bact, &size);
    fclose(infile);  // Close input file after reading

    // Print table to console and write to output file
    print_mpn_table(outfile, size, bact);
    fclose(outfile);  // Close output file after writing

    // Allow user to search for a combination
    char user_input[10];

    while (1) {
        printf("\nEnter a combination to search (e.g., 4-2-0) or 'exit' to quit: ");
        scanf("%9s", user_input);

        if (strcmp(user_input, "exit") == 0) {
            printf("Exiting program...\n");
            break;
        }

        int index = search_mpn_table(bact, size, user_input);
        if (index != -1) {
            printf("\nMatch found:\n");
            printf("| %-10s | %-10d | %-8d | %-8d |\n",
                bact[index].combination_of_positives,
                bact[index].mpn_index_100ml,
                bact[index].lower,
                bact[index].upper);
        } else {
            printf("Combination '%s' not found.\n", user_input);
        }
    }

    return 0;
}