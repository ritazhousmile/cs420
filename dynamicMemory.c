/*in the main function of a C program write code that reads in an integer representing the number of strings to read from stdin, store those strings into an optimal
array of pointers to strings that doesn't waste any space.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int numOfStrings;

    printf("Enter number of strings: ");
    scanf("%d", &numOfStrings);

    char **array_strings = malloc(numOfStrings * sizeof(char *));
    if (array_strings == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < numOfStrings; i++) {
        char str[1000];  // temporary buffer
        printf("Enter string %d: ", i + 1);
        scanf("%s", str);

        array_strings[i] = malloc(strlen(str) + 1);
        if (array_strings[i] == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }

        strcpy(array_strings[i], str);
    }

    printf("\nStored strings:\n");
    for (int i = 0; i < numOfStrings; i++) {
        printf("%s\n", array_strings[i]);
    }

    // Free memory
    for (int i = 0; i < numOfStrings; i++) {
        free(array_strings[i]);
    }
    free(array_strings);

    return 0;
}