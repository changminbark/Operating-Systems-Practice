#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Integer array of 100 ints
    int nums[100];

    // Seed random number generator
    srand(42);

    // OMP for loop
    #pragma omp parallel for num_threads(16)
    for (int i = 0; i < 100; i++) {
        nums[i] = (rand() % (10000 - 1 + 1)) + 1;
    }

    // Print the array
    printf("Generated Random Numbers:\n");
    for (int i = 0; i < 100; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}