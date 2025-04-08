#include "bitOperations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to check if a date is valid
int isValidDate(int day, int month, int year) {
    // Check month validity
    if (month < 1 || month > 12)
        return 0;
    
    // Check year validity for 20th century (1900-1999)
    if (year < 0 || year > 99)
        return 0;
    
    // Check day validity based on month
    int maxDays;
    switch (month) {
        case 4: case 6: case 9: case 11:
            maxDays = 30;
            break;
        case 2:
            // Check for leap year in 20th century
            if ((year % 4 == 0) && (year != 0))
                maxDays = 29;
            else
                maxDays = 28;
            break;
        default:
            maxDays = 31;
    }
    
    return (day >= 1 && day <= maxDays);
}

// Pack date into 16-bit value
unsigned short packDate(int day, int month, int year) {
    // Day: 5 most significant bits (bits 11-15)
    // Month: 4 middle bits (bits 7-10)
    // Year: 7 least significant bits (bits 0-6)
    unsigned short packedDate = 0;
    
    packedDate |= (day & 0x1F) << 11;    // Day (5 bits)
    packedDate |= (month & 0x0F) << 7;   // Month (4 bits)
    packedDate |= (year & 0x7F);         // Year (7 bits)
    
    return packedDate;
}

// Unpack date from 16-bit value
void unpackDate(unsigned short packedDate, int *day, int *month, int *year) {
    *day = (packedDate >> 11) & 0x1F;    // Extract day (5 bits)
    *month = (packedDate >> 7) & 0x0F;   // Extract month (4 bits)
    *year = packedDate & 0x7F;           // Extract year (7 bits)
}

// Reverse bits of a 16-bit value
unsigned short reverseBits(unsigned short value) {
    unsigned short result = 0;
    
    for (int i = 0; i < 16; i++) {
        // Get bit at position i
        unsigned short bit = (value >> i) & 1;
        
        // Place it at position (15-i) in the result
        result |= (bit << (15 - i));
    }
    
    return result;
}

// Circular right shift
unsigned short circularRightShift(unsigned short value, int shift) {
    // Ensure shift is within range (0-15)
    shift = shift & 0x0F;
    
    // Perform circular right shift
    return (value >> shift) | (value << (16 - shift));
}

// Main function to convert dates
int convertDate(char filename[], date_t dates[]) {
    FILE *file = fopen(filename, "r");
    if (!file) return INVALID_INPUT_FILE;  // Return error code if file cannot be opened
    
    int count = 0;
    char buffer[20];
    
    // Read each line from file
    while (count < MAX_DATES && fgets(buffer, sizeof(buffer), file)) {
        // Remove newline character if present
        buffer[strcspn(buffer, "\n")] = 0;
        
        int day, month, year;
        
        // Parse the date string (format: mm/dd/yy)
        if (sscanf(buffer, "%d/%d/%d", &month, &day, &year) != 3) {
            continue;  // Skip invalid lines
        }
        
        // Check if the input date is valid
        if (!isValidDate(day, month, year)) {
            continue;  // Skip invalid dates
        }
        
        // Copy the input date string to the record
        strncpy(dates[count].startDateStr, buffer, sizeof(dates[count].startDateStr) - 1);
        dates[count].startDateStr[sizeof(dates[count].startDateStr) - 1] = '\0';  // Ensure null termination
        
        // Step 1: Convert date to binary
        dates[count].binaryDate = packDate(day, month, year);
        
        // Step 2: Reverse bits
        dates[count].reverseDate = reverseBits(dates[count].binaryDate);
        
        // Step 3: Circular right shift by the value from first 4 LSB
        int shiftAmount = dates[count].reverseDate & 0x0F;  // Get first 4 LSB
        dates[count].shiftedDate = circularRightShift(dates[count].reverseDate, shiftAmount);
        
        // Step 4: Unpack the shifted value to get a date
        int finalDay, finalMonth, finalYear;
        unpackDate(dates[count].shiftedDate, &finalDay, &finalMonth, &finalYear);
        
        // Format the end date string
        sprintf(dates[count].endDateStr, "%02d/%02d/%02d", finalMonth, finalDay, finalYear);
        
        // Check if final date is valid
        dates[count].endDateValid = isValidDate(finalDay, finalMonth, finalYear) ? 1 : 0;
        
        count++;
    }
    
    fclose(file);
    return count;
}