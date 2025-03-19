/** 
* @author: huan zhou
* @version: 03/18/2025
* calSpan.c
* Sensor data processing function
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int dataDump(char *filename) {
    FILE *file;
    int byte;
    int count = 0;
    int linePos;
    char asciiChars[17]; // 16 characters + null terminator
    
    // Open the file
    file = fopen(filename, "rb");
    if (file == NULL) {
        return -1;  // Return -1 if file cannot be opened
    }
    
    // Process file contents
    while (1) {
        // Print byte counter at the start of each line
        printf("%08d", count);
        
        // Reset ASCII string
        asciiChars[0] = '\0';
        
        // Process up to 16 bytes per line
        for (linePos = 0; linePos < 16; linePos++) {
            // Read a byte
            byte = fgetc(file);
            
            // Check for end of file
            if (byte == EOF) {
                // If we're at the start of a line with no bytes read, break out completely
                if (linePos == 0) {
                    goto end;
                }
                
                // Otherwise, pad the rest of the line with spaces
                while (linePos < 16) {
                    printf("   ");
                    asciiChars[linePos] = '\0';
                    linePos++;
                }
                break;
            }
            
            // Print byte in hex
            printf(" %02x", (unsigned char)byte);
            
            // Add to ASCII representation
            if (byte >= 32 && byte <= 126) {
                asciiChars[linePos] = (char)byte;
            } else {
                asciiChars[linePos] = '.';
            }
            
            count++;
        }
        
        // Null-terminate the ASCII string
        asciiChars[linePos] = '\0';
        
        // Print ASCII representation
        printf("  %s\n", asciiChars);
    }
    
end:
    // Close the file
    fclose(file);
    
    return count;
}