/** @author: huan zhou
* dataDumpMain.c
* Main function to test dataDump
*/

#include <stdio.h>
#include <stdlib.h>

// Function prototype for dataDump
int dataDump(char *filename);

int main(int argc, char *argv[]) {
    // Check if filename is provided as command-line argument
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    // Call dataDump function with provided filename
    int result = dataDump(argv[1]);
    
    // Check result
    if (result == -1) {
        printf("Error: Could not open file '%s'\n", argv[1]);
        return 1;
    }
    
    printf("\nTotal bytes processed: %d\n", result);
    
    return 0;
}