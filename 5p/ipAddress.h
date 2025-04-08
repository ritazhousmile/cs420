#ifndef IP_ADDRESS_H
#define IP_ADDRESS_H

#define MAX_RECORDS 100 // Maximum records read from the input data file

// Structure to hold IP address information
typedef struct {
    char ipAddressDot[16];    // Character string read from data file
    char subnetMaskDot[16];   // Character string read from data file
    unsigned int ipAddress;   // 32-bit container - numeric value
    unsigned int subnetMask;  // 32-bit container - numeric value
    char networkClass;        // Character ('A', 'B', or 'C')
    unsigned int totalSubnets; // Numeric value
    unsigned int totalHosts;   // Numeric value
} ipInfo_t;

// Function prototypes
int readData(char filename[], ipInfo_t records[]);
void computeValues(ipInfo_t records[], int size);
void printResults(char filename[], ipInfo_t records[], int size);

#endif // IP_ADDRESS_H