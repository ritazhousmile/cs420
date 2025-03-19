#include <stdio.h>
#include "seethe.h"

int main(){
    int sum = 0;
    int value;

    for (int i=0; i<100; i++){
        scanf("%d", &value);   // read from stdin
        debug("input value = %d", value);
        sum += value;
    }

    printf("Total is %d\n", sum);  // output to stdout
}

