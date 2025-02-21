/*
Name: huan zhou
1p
02/14/2025
*/
#include <stdio.h>
#include <math.h>

#define MIN_TEMP -20  // Minimum valid temperature
#define MAX_TEMP 50   // Maximum valid temperature

// Constants for Wind Chill Calculation
#define WIND_MIN 5    // Minimum valid wind speed
#define WIND_MAX 40   // Maximum wind speed for table
#define WIND_STEP 5   // Wind speed increments

// Constants for Heat Index Calculation
#define HUMIDITY_MIN 40  // Minimum relative humidity
#define HUMIDITY_MAX 100 // Maximum relative humidity
#define HUMIDITY_STEP 10 // Humidity increments

// Convert Celsius to Fahrenheit
double celsius_to_fahrenheit(int celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

// Calculate Wind Chill (valid only if temp <= 50F and wind speed >= 5mph)
double calculate_wind_chill(double fahrenheit, double wind_speed) {
    if (fahrenheit > 50 || wind_speed < WIND_MIN) return -1; // Invalid
    return 35.74 + 0.6215 * fahrenheit - 35.75 * pow(wind_speed, 0.16) 
           + 0.4275 * fahrenheit * pow(wind_speed, 0.16);
}

// Calculate Heat Index (valid only if temp >= 80F and humidity >= 40%)
double calculate_heat_index(double fahrenheit, double humidity) {
    if (fahrenheit < 80 || humidity < HUMIDITY_MIN) return -1; // Invalid

    return -42.379 + 2.04901523 * fahrenheit + 10.14333127 * humidity 
           - 0.22475541 * fahrenheit * humidity - 0.00683783 * pow(fahrenheit, 2)
           - 0.05481717 * pow(humidity, 2) + 0.00122874 * pow(fahrenheit, 2) * humidity
           + 0.00085282 * fahrenheit * pow(humidity, 2) - 0.00000199 * pow(fahrenheit, 2) * pow(humidity, 2);
}

int main() {
    int lower, upper;

    // Input validation loop
    while (1) {
        printf("Enter two temperature values in Celsius (%d to %d) [low high]: ", MIN_TEMP, MAX_TEMP);
        if (scanf("%d %d", &lower, &upper) != 2) {
            printf("Invalid input! Please enter two integers.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        if (lower >= MIN_TEMP && upper <= MAX_TEMP && lower < upper) {
            break;
        } else {
            printf("Invalid range! Ensure first value is less than the second and within %d to %d.\n", MIN_TEMP, MAX_TEMP);
        }
    }

    // Print Wind Chill Table
    printf("\nCelsius to Fahrenheit with Wind Chill Factor\n");
    printf("Celsius  Fahrenheit ");
    for (int w = WIND_MIN; w <= WIND_MAX; w += WIND_STEP) {
        printf("%5dmph ", w);
    }
    printf("\n");

    for (int c = lower; c <= upper; c++) {
        double fahrenheit = celsius_to_fahrenheit(c);
        printf("%7d %10.2f ", c, fahrenheit);

        for (int w = WIND_MIN; w <= WIND_MAX; w += WIND_STEP) {
            double wind_chill = calculate_wind_chill(fahrenheit, w);
            if (wind_chill == -1) {
                printf("    X ");
            } else {
                printf("%6.2f ", wind_chill);
            }
        }
        printf("\n");
    }

    // Print Heat Index Table
    printf("\nCelsius to Fahrenheit with Heat Index Factor\n");
    printf("Celsius  Fahrenheit ");
    for (int h = HUMIDITY_MIN; h <= HUMIDITY_MAX; h += HUMIDITY_STEP) {
        printf("%4d%% ", h);
    }
    printf("\n");

    for (int c = lower; c <= upper; c++) {
        double fahrenheit = celsius_to_fahrenheit(c);
        printf("%7d %10.2f ", c, fahrenheit);

        for (int h = HUMIDITY_MIN; h <= HUMIDITY_MAX; h += HUMIDITY_STEP) {
            double heat_index = calculate_heat_index(fahrenheit, h);
            if (heat_index == -1) {
                printf("   X  ");
            } else {
                printf("%6.2f ", heat_index);
            }
        }
        printf("\n");
    }

    return 0;
}