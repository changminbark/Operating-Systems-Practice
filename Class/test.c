#include <stdio.h>

int main(){
    int number = 5;
    int *pNumber = &number;

    char string[50] = "Hello World";

    printf("String is %s\n", string);
    printf("Number: %d\n", number);
    printf("Addr: %p\n", (int *), pNumber);
    return 0;
}

