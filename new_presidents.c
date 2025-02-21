#include <stdio.h>
/**/
int main(int argc, char *argv[]) { 
    FILE *inputFile1 = fopen(argv[1], "r");
    FILE *inputFile2 = fopen(argv[2], "r");
    FILE *outputFile = fopen(argv[3], "w");
    char name[80];
    int status;
    if (inputFile1 == NULL){
        printf("Unable to open sample!\n");
        return 1; 
    }
    while((status = fscanf(inputFile1, "%s\n", name) )!= EOF) {
        fprintf(outputFile, "%s\n", name);
    }
    fclose(inputFile1);

    if (inputFile2 == NULL){
        printf("Unable to open sample!\n");
        return 1; 
    }
    while((status = fscanf(inputFile2, "%s\n", name)) != EOF) {
        fprintf(outputFile, "%s\n", name);
    }
    fclose(inputFile2);

    fclose(outputFile);
}


