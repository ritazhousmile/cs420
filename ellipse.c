/*
Name: huan zhou
0p
01/31/2025
*/



#include <stdio.h>
#include <math.h>
#define PI 3.14159

int main(void) {
    float a;
    float b;
    float h;    
    float e;     
    float s;    

    //input the value of a
    printf("Enter Major Axis:");
    scanf("\n%f", &a);

     //input the value of b
    printf("Enter Minor Axis:");
    scanf("\n%f",&b);

    // Print header with axis values
    printf("\nEllipse Circumference for Major Axis: %8.2f and Minor Axis: %8.2f\n", a, b);

    // Table border line
    printf("+-----------------------------------------------------+\n");

    // Simple first approximation
    float simple1 = PI * (a + b);
    printf("|%30s | %12.6f|\n", "Simple First Approximation", simple1);
    printf("+-----------------------------------------------------+\n");

     // Simple second approximation
    float simple2 = PI * sqrt(2 * (a*a + b*b));
    printf("|%30s | %12.6f|\n", "Simple Second Approximation", simple2);
    printf("+-----------------------------------------------------+\n");

     // Simple third approximation
    float simple3 = PI * ((3.0/2.0)*(a+b) - sqrt(a*b));
    printf("|%30s | %12.6f|\n", "Simple Third Approximation", simple3);
    printf("+-----------------------------------------------------+\n");

    // Ramanujan's first approximation
    float ram1 = PI * (3*(a+b) - sqrt((3*a+b)*(a+3*b)));
    printf("|%30s | %12.6f|\n", "Ramanujan's First Approximation", ram1);
    printf("+-----------------------------------------------------+\n");

    // Ramanujan's second approximation
    h = pow(a-b, 2) / pow(a+b, 2);
    float ram2 = PI*(a+b) * (1 + (3*h)/(10 + sqrt(4 - 3*h)));
    printf("|%30s | %12.6f|\n", "Ramanujan's Second Approximation", ram2);
    printf("+-----------------------------------------------------+\n");

    // Muir's formula
    s = 1.5;
    float muir = 2 * PI * pow((pow(a,s)/2 + pow(b,s)/2), 1/s);
    printf("|%30s | %12.6f|\n", "Muir's Formula", muir);
    printf("+-----------------------------------------------------+\n");

     // Hudson's formula
    h = pow(a-b, 2) / pow(a+b, 2);
    float hudson = 0.25 * PI * (a+b) * (3*(1 + h/4) + 1/(1 - h/4));
    printf("|%30s | %12.6f|\n", "Hudson Formula", hudson);
    printf("+-----------------------------------------------------+\n");

    // Holder mean
    s = log(2) / log(PI/2);
    float holder = 4 * pow(pow(a,s) + pow(b,s), 1/s);
    printf("|%30s | %12.6f|\n", "Holder mean", holder);
    printf("+-----------------------------------------------------+\n");

    // David Cantrell's formula
    s = 0.825056;
    float cantrell = 4*(a+b) - 2*(4-PI)*a*b/pow(pow(a,s)/2 + pow(b,s)/2, 1/s);
    printf("|%30s | %12.6f|\n", "David Cantrell's formula", cantrell);
    printf("+-----------------------------------------------------+\n");

    // Eccentric Series approximation
    e = sqrt(a*a - b*b)/a;
    float series = 2*a*PI*(1 - pow(1.0/2, 2)*e*e -  pow(1.0*3/(2.0*4), 2)*pow(e,4)/3 - pow(1.0*3*5/(2.0*4*6), 2)*pow(e,6)/5);
    printf("|%30s | %12.6f|\n", "Eccentric series formula", series);
    printf("+-----------------------------------------------------+\n");

    return 0;
}