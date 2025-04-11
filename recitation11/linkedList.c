#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LEN 1024

// Linked list node holding a line of string
typedef struct LINK_LIST_NODE {
    char* data;
    int isPalindrome;
    struct LINK_LIST_NODE* next;
} LINK_LIST_NODE;

// Create a new node
LINK_LIST_NODE* createNode(const char* value) {
    LINK_LIST_NODE* newNode = (LINK_LIST_NODE*)malloc(sizeof(LINK_LIST_NODE));
    newNode->data = strdup(value);  // Copy string into dynamically allocated memory
    newNode->isPalindrome = 0;      // Default value
    newNode->next = NULL;
    return newNode;
}

// Append node to the end
void appendNode(LINK_LIST_NODE** head, const char* value) {
    LINK_LIST_NODE* newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    LINK_LIST_NODE* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
}

// Print the list
void printList(LINK_LIST_NODE* head) {
    while (head != NULL) {
        printf("%s", head->data); // No need for newline, fgets already includes it
        head = head->next;
    }
}

// Free all memory
void freeList(LINK_LIST_NODE* head) {
    LINK_LIST_NODE* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}


// Function to check if a string is a palindrome
int isPalindrome(const char* str) {
    int left = 0;
    int right = strlen(str) - 1;

    while (left < right) {
        // Skip non-alphanumeric characters
        while (left < right && !isalnum(str[left])) left++;
        while (left < right && !isalnum(str[right])) right--;

        // Compare lowercase versions
        if (tolower(str[left]) != tolower(str[right])) {
            return 0; // Not a palindrome
        }

        left++;
        right--;
    }

    return 1; // It is a palindrome
}

void printListWithPalindrome(LINK_LIST_NODE* head) {
    while (head != NULL) {
        printf("%s", head->data);
        if (head->isPalindrome) {
            printf(" ↠ (Palindrome)\n");
        }
        head = head->next;
    }
}

void filterNonPalindromes(LINK_LIST_NODE** head) {
    LINK_LIST_NODE* current = *head;
    LINK_LIST_NODE* prev = NULL;

    while (current != NULL) {
        if (!current->isPalindrome) {
            LINK_LIST_NODE* toDelete = current;

            if (prev == NULL) {
                // Head needs to be removed
                *head = current->next;
                current = *head;
            } else {
                // Remove current node
                prev->next = current->next;
                current = current->next;
            }

            // Free the removed node
            free(toDelete->data);
            free(toDelete);
        } else {
            // Keep node, move forward
            prev = current;
            current = current->next;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Program needs a file name to be supplied on the command line\n");
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL) {
        printf("Input file could not be opened\n");
        return 1;
    }

    LINK_LIST_NODE* head = NULL;
    char buffer[MAX_LINE_LEN];

    while (fgets(buffer, MAX_LINE_LEN, infile)) {
        appendNode(&head, buffer);
    }

    fclose(infile);

    // After setting isPalindrome values
    LINK_LIST_NODE* temp = head;
    while (temp != NULL) {
        temp->isPalindrome = isPalindrome(temp->data);
        temp = temp->next;
    }

    filterNonPalindromes(&head);

    // Print with palindrome info
    printf("Contents of the file in the linked list:\n");
    printListWithPalindrome(head);

    // Free memory
    freeList(head);
    return 0;
}