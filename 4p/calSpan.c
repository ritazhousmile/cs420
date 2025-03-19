/** 
* @author: huan zhou
* @version: 03/18/2025
* calSpan.c
* Sensor data processing function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int calSpan(int maxSize, char *filename, double data[]) {
    FILE *file;
    char buffer[100];
    int count = 0;
    int i;
    
    // Open the file
    file = fopen(filename, "r");
    if (file == NULL) {
        return -1;  
    }
    
    // Read data from file
    while (count < maxSize && fscanf(file, "%s", buffer) == 1) {
        // Try to convert string to double
        char *endptr;
        double value = strtod(buffer, &endptr);
        
        // Check if conversion was successful and value is in valid range
        if (*endptr != '\0' || value == 0.0 || value < -100.0 || value > 100.0) {
            // Corrupted data, set to a very low value to mark as corrupted
            data[count] = -999.0;  // Using a value well below the valid range
        } else {
            data[count] = value;
        }
        count++;
    }
    
    // Close the file
    fclose(file);
    
    char query[20];
    int minute;
    
    // Process user queries
    while (1) {
        printf("Which minute to query? ");
        scanf("%s", query);
        
        // Check if user wants to exit
        if (strcasecmp(query, "exit") == 0) {
            break;
        }
        
        // Try to convert query to integer
        char *endptr;
        minute = strtol(query, &endptr, 10);
        
        // Check if conversion was successful
        if (*endptr != '\0') {
            printf("Wrong query input\n");
            continue;
        }
        
        // Check if minute is in range
        if (minute < 0 || minute >= count) {
            printf("Query minute out of range\n");
            continue;
        }
        
        // Check if data is corrupted
        if (data[minute] <= -999.0) {
            printf("Data at minute %d is corrupted.\n", minute);
            continue;
        }
        
        // Calculate span
        int span = 1;
        for (i = minute - 1; i >= 0; i--) {
            if (data[i] <= -999.0 || data[i] > data[minute]) {
                break;
            }
            span++;
        }
        
        printf("Data at minute %d is a %d-minute(s) high\n", minute, span);
    }
    
    return count;
}