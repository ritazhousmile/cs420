#include <stdio.h>

#define MAX_SIZE 512

int main() {
    char word[MAX_SIZE];
    int count = 0;

    scanf("%s", word);
    while (!feof(stdin)) {
        count++;
        scanf("%s", word);
    }
    printf("%d\n", count);

    return 0;
}
