#include <stdio.h>
#include <string.h>
/*
int main(int argc, char *argv[]) { 

	FILE *myFile = fopen(argv[1],"r");
    
    if (myFile == NULL) {
        printf("unable to open the file");
        return 1;
    };
    char name[80];
    int status;
    while((status = fscanf(myFile, "%s\n", name)) != EOF) {
        printf( "%s\n", name);
    }
        fclose(myFile);  // Close the file
        return 0;
}
*/

int main(int argc, char *argv[]) { 

	FILE *myFile = fopen(argv[1],"r");
    
    if (myFile == NULL) {
        printf("unable to open the file");
        return 1;
    };
    char name[80];
    int status;
    while((status = fscanf(myFile, "%s\n", name)) != EOF) {
        if (strstr(name, "Johnson") || strstr(name, "Roosevelt")) {
            printf( "%s\n", name);
        }
    }
        fclose(myFile);  // Close the file
        return 0;
}