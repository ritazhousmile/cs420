#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Returns a pointer to the longer of the two string inputs,
 * or to the first one if they are the same length.
 */
const char *longer_of(const char first[], const char second[]) {
    return (strlen(first) >= strlen(second)) ? first : second;
}

/* Returns a pointer to the shorter of the two string inputs,
 * or to the first one if they are the same length.
 */
const char *shorter_of(const char first[], const char second[]) {
    return (strlen(first) <= strlen(second)) ? first : second;
}

/* Fills the result with a bitwise-AND of the first two string inputs.
 * Returns 1 on success, or 0 on failure (if result_len is too small).
 */
int bitwise_AND(const char first[], const char second[], char result[], int result_len) {
    // Determine shorter and longer input
    const char *shorter = shorter_of(first, second);
    const char *longer = longer_of(first, second);

    int min_len = strlen(shorter);
    int max_len = strlen(longer);

    // Ensure result has enough space (including null terminator)
    if (result_len < max_len + 1)
        return 0;

    int short_offset = max_len - min_len;

    // Fill in the result
    for (int i = 0; i < max_len; i++) {
        if (short_offset > i) {
            result[i] = longer[i]; // Padding shorter string with '0's
        } else {
            result[i] = shorter[i - short_offset] == 1 && longer[i] == 1 ? 1 : 0;
        }
    }

    result[max_len] = '\0'; // Null-terminate the result
    return 1;
}

/* Fills the result with a bitwise-XOR of the first two string inputs.
 * Returns 1 on success, or 0 on failure (if result_len is too small).
 */
int bitwise_XOR(const char first[], const char second[], char result[], int result_len) {
    // Determine shorter and longer input
    const char *shorter = shorter_of(first, second);
    const char *longer = longer_of(first, second);

    int min_len = strlen(shorter);
    int max_len = strlen(longer);

    // Ensure result has enough space (including null terminator)
    if (result_len < max_len + 1)
        return 0;

    int short_offset = max_len - min_len;

    // Fill in the result
    for (int i = 0; i < max_len; i++) {
        if (short_offset > i) {
            result[i] = longer[i]; // Padding with longer string
        } else {
            // Convert '0' or '1' characters to integers, apply bitwise XOR, and convert back to character
            char bit1 = shorter[i - short_offset] - '0';
            char bit2 = longer[i] - '0';
            result[i] = (bit1 ^ bit2) + '0';
        }
    }

    result[max_len] = '\0'; // Null-terminate the result
    return 1;
}

/* Main function for testing */
int main() {
    char first[] = "1101";    // Binary string 1
    char second[] = "101011"; // Binary string 2
    char and_result[20];      // Buffer for AND result
    char xor_result[20];      // Buffer for XOR result

    // Perform bitwise AND operation
    if (bitwise_AND(first, second, and_result, sizeof(and_result))) {
        printf("AND Result: %s\n", and_result);
    } else {
        printf("Error: Buffer too small for AND result\n");
    }

    // Perform bitwise XOR operation
    if (bitwise_XOR(first, second, xor_result, sizeof(xor_result))) {
        printf("XOR Result: %s\n", xor_result);
    } else {
        printf("Error: Buffer too small for XOR result\n");
    }

    return 0;
}