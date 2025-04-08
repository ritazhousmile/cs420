#include "ipAddress.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to convert dot notation IP address to 32-bit numeric value
unsigned int convertDotToNumeric(const char *dotNotation) {
    unsigned int octet1, octet2, octet3, octet4;
    
    sscanf(dotNotation, "%u.%u.%u.%u", &octet1, &octet2, &octet3, &octet4);
    
    // Combine octets into a 32-bit value (most significant to least significant)
    return (octet1 << 24) | (octet2 << 16) | (octet3 << 8) | octet4;
}

// Helper function to count bits set to 1 in a 32-bit value
int countOneBits(unsigned int value) {
    int count = 0;
    for (int i = 0; i < 32; i++) {
        if (value & (1 << 31)) {
            count++;
        }
        value <<= 1;
    }
    return count;
}

// Helper function to determine the number of subnet and host bits based on network class
void getSubnetHostBits(unsigned int ipAddress, unsigned int subnetMask, int *subnetBits, int *hostBits) {
    // Determine network class and default network bits
    unsigned char firstOctet = (ipAddress >> 24) & 0xFF;
    int networkBits;
    
    if (firstOctet < 128) {
        // Class A: First byte is network
        networkBits = 8;
    } else if (firstOctet < 192) {
        // Class B: First two bytes are network
        networkBits = 16;
    } else {
        // Class C: First three bytes are network
        networkBits = 24;
    }
    
    // Calculate total bits that are set to 1 in the subnet mask
    int totalOnes = 0;
    unsigned int mask = subnetMask;
    for (int i = 0; i < 32; i++) {
        if (mask & 0x80000000) {
            totalOnes++;
        }
        mask <<= 1;
    }
    
    // Subnet bits are the ones beyond the default network bits
    *subnetBits = totalOnes - networkBits;
    if (*subnetBits < 0) *subnetBits = 0;  // Ensure non-negative
    
    // Host bits are the remaining zeros in the subnet mask
    *hostBits = 32 - totalOnes;
}

// Read data from file into array of structures
int readData(char filename[], ipInfo_t records[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return 0;
    }
    
    int count = 0;
    
    // Read each line until end of file or max records reached
    while (count < MAX_RECORDS && 
           fscanf(file, "%15s %15s", records[count].ipAddressDot, records[count].subnetMaskDot) == 2) {
        count++;
    }
    
    fclose(file);
    return count;
}

// Compute values for each record
void computeValues(ipInfo_t records[], int size) {
    for (int i = 0; i < size; i++) {
        // Convert dot notation to numeric values
        records[i].ipAddress = convertDotToNumeric(records[i].ipAddressDot);
        records[i].subnetMask = convertDotToNumeric(records[i].subnetMaskDot);
        
        // Determine network class
        unsigned char firstOctet = (records[i].ipAddress >> 24) & 0xFF;
        
        if (firstOctet < 128) {
            records[i].networkClass = 'A';
        } else if (firstOctet < 192) {
            records[i].networkClass = 'B';
        } else if (firstOctet < 224) {
            records[i].networkClass = 'C';
        } else {
            // This shouldn't happen with valid IP addresses in this assignment
            records[i].networkClass = '?';
        }
        
        // Calculate subnet and host bits
        int subnetBits = 0, hostBits = 0;
        switch (records[i].networkClass) {
            case 'A':
                // For Class A, subnet bits are 1's in positions 9-32 of subnet mask
                subnetBits = countOneBits(records[i].subnetMask & 0x00FFFFFF);
                // For Class A, host bits are 0's in positions 9-32 of subnet mask
                hostBits = 24 - subnetBits;
                break;
            case 'B':
                // For Class B, subnet bits are 1's in positions 17-32 of subnet mask
                subnetBits = countOneBits(records[i].subnetMask & 0x0000FFFF);
                // For Class B, host bits are 0's in positions 17-32 of subnet mask
                hostBits = 16 - subnetBits;
                break;
            case 'C':
                // For Class C, subnet bits are 1's in positions 25-32 of subnet mask
                subnetBits = countOneBits(records[i].subnetMask & 0x000000FF);
                // For Class C, host bits are 0's in positions 25-32 of subnet mask
                hostBits = 8 - subnetBits;
                break;
        }
        
        // Calculate total subnets and hosts
        if (subnetBits > 0) {
            records[i].totalSubnets = 1 << subnetBits; // 2^subnetBits
        } else {
            records[i].totalSubnets = 1; // No subnetting
        }
        
        if (hostBits > 0) {
            records[i].totalHosts = (1 << hostBits) - 2; // 2^hostBits - 2 (subtract network and broadcast addresses)
        } else {
            records[i].totalHosts = 0; // No host addresses available
        }
    }
}

// Print results to output file
void printResults(char filename[], ipInfo_t records[], int size) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening output file: %s\n", filename);
        return;
    }
    
    fprintf(file, "IP Address\t\tSubnet Mask\t\tIP Value (Hex)\tMask Value (Hex)\tClass\tSubnets\tHosts\n");
    fprintf(file, "----------\t\t-----------\t\t-------------\t---------------\t-----\t-------\t-----\n");
    
    for (int i = 0; i < size; i++) {
        fprintf(file, "%-15s\t%-15s\t%08X\t%08X\t%c\t%u\t%u\n", 
                records[i].ipAddressDot,
                records[i].subnetMaskDot,
                records[i].ipAddress,
                records[i].subnetMask,
                records[i].networkClass,
                records[i].totalSubnets,
                records[i].totalHosts);
    }
    
    fclose(file);
}