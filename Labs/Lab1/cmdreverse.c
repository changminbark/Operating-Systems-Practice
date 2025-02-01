#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Check if 4 arguments are provided (5 because of command to run binary itself)
    if (argc != 2) {
        printf("Error: Incorrect number of arguments.\n");
        printf("Usage: %s <string to reverse>\n", argv[0]);
        return 1;
    }

    // Save input into a buffer
    char input[256];  // Adjust size if necessary
    strncpy(input, argv[1], sizeof(input) - 1);
    input[sizeof(input) - 1] = '\0';  // Null-terminate to prevent overflow

    int length = strlen(input);

    int j = length - 1;

    // Reverse the string using a for loop
    for (int i = 0; i < j; i++) {
        char temp = input[i];
        input[i] = input[j];
        input[j] = temp;
        j--;
    }

    // CHAT-GPT says that this is also valid syntax
    // for (int i = 0, j = length - 1; i < j; i++, j--) {
    //     char temp = input[i];
    //     input[i] = input[j];
    //     input[j] = temp;
    // }

    // Print the reversed string
    printf("Reversed string: %s\n", input);

    return 0;
}