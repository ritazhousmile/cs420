#include <stdio.h>
#include <stdint.h>

// Function to check if the Least Significant Bit (LSB) is set
int is_LSB_set(unsigned int num) {
    return num & 1;
}

// Function to check if the Most Significant Bit (MSB) is set (Assuming 32-bit)
int is_MSB_set(unsigned int num) {
    return num & (1U << (sizeof(unsigned int) * 8 - 1)); // Works for all integer sizes
}

int main(void) {
    unsigned int num;

    while (1) {
        printf("Enter a number (0 to exit): ");
        if (scanf("%u", &num) != 1) { // Handle invalid input
            printf("Invalid input. Exiting.\n");
            break;
        }

        if (num == 0) {
            printf("Exiting...\n");
            break;
        }

        printf("LSB is %s\n", is_LSB_set(num) ? "set" : "not set");
        printf("MSB is %s\n", is_MSB_set(num) ? "set" : "not set");
    }

    return 0;
}