
/*
Name: huan zhou
1p
02/14/2025
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int rolls;
    int current_streak[7] = {0}; // Current streak for each number (1-6, index 0 unused)
    int max_streak[7] = {0};     // Maximum streak for each number
    int total_counts[7] = {0};   // Total occurrences of each number
    int last_roll = 0;           // Keep track of the previous roll
    int numbers_per_line = 0;    // Counter for formatting output

    // Seed the random number generator with current time
    srand(time(NULL));

    // Get valid input from user
    do {
        printf("Enter the number of times to roll the die (minimum 2): ");
        scanf("%d", &rolls);
        
        if (rolls < 2) {
            printf("Invalid input. Please enter a number greater than 1.\n");
        }
    } while (rolls < 2);

    printf("\nRolling the die %d times:\n", rolls);

    // Simulate dice rolls
    for (int i = 0; i < rolls; i++) {
        int roll = (rand() % 6) + 1;  // Generate random number 1-6
        printf("%d ", roll);
        
        // Format output - 30 numbers per line
        numbers_per_line++;
        if (numbers_per_line == 30) {
            printf("\n");
            numbers_per_line = 0;
        }

        // Update total counts
        total_counts[roll]++;

        // Update streaks
        if (roll == last_roll) {
            current_streak[roll]++;
        } else {
            current_streak[roll] = 1;
        }

        // Update maximum streak if current streak is larger
        if (current_streak[roll] > max_streak[roll]) {
            max_streak[roll] = current_streak[roll];
        }

        last_roll = roll;
    }

    // Print final newline if needed
    if (numbers_per_line != 0) {
        printf("\n");
    }

    // Print results
    printf("\nTotal Count\n");
    for (int i = 1; i <= 6; i++) {
        printf("    %s:    %2d\n", 
               i == 1 ? "Ones" :
               i == 2 ? "Twos" :
               i == 3 ? "Threes" :
               i == 4 ? "Fours" :
               i == 5 ? "Fives" :
               "Sixes",
               total_counts[i]);
    }

    printf("\nConsecutive Count\n");
    for (int i = 1; i <= 6; i++) {
        printf("    %s:    %2d\n", 
               i == 1 ? "Ones" :
               i == 2 ? "Twos" :
               i == 3 ? "Threes" :
               i == 4 ? "Fours" :
               i == 5 ? "Fives" :
               "Sixes",
               max_streak[i]);
    }

    return 0;
}