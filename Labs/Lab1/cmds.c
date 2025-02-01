#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Check if 4 arguments are provided (5 because of command to run binary itself)
    if (argc != 5) {
        printf("Error: Incorrect number of arguments.\n");
        printf("Usage: %s <char> <int> <float> <string>\n", argv[0]);
        return 1;
    }

    // Assign each value to variables
    char charVal = argv[1][0];  // First argument is a character
    int intVal = atoi(argv[2]); // Second argument converted to an integer
    float floatVal = atof(argv[3]); // Third argument converted to a float
    char stringVal[100]; // Fourth argument is a string 
    strncpy(stringVal, argv[4], sizeof(stringVal) - 1); 
    stringVal[sizeof(stringVal) - 1] = '\0'; // Null-terminate to prevent overflow

    // Print values
    printf("char: %c\n", charVal);
    printf("int: %d\n", intVal);
    printf("float: %.2f\n", floatVal);
    printf("string: %s\n", stringVal);

    return 0;
}