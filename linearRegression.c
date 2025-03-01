#include <stdio.h>

void linear_regression(double x[], double y[], int n, double *m, double *b) {
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_xx += x[i] * x[i];
    }

    //double x_mean = sum_x / n;
    //double y_mean = sum_y / n;
    m = (sum_x * sum_y - sum_xy * n)/(sum_xx * sum_xx - sum_xx * n);
    b = (sum_y - sum_x * m)/n;

    printf("m:" m);
    printf("b:" b)
}

double predict(double x, double m, double b) {
    return m * x + b;
}

double residual(double predictY, double y){
    return (predictY - y) * (predictY - y)
}

int main() {
    double x[] = {50, 60, 75, 77, 86, 96 , 32, 82, 53, 91};
    double y[] = {47, 41,71,65,88,89,18, 79, 67, 69,94};
    int n = sizeof(x) / sizeof(x[0]);
    double m, b;

    linear_regression(x, y, n, &m, &b);
    for (int i = 0; i < n; i++) {
        double predictY;
        double residual;
        predictY =predict(x[i], &m, &b)
    }
    
    return 0;
}