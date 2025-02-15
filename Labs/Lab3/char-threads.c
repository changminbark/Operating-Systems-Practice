#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void sum_cpu() {
    int sum = 0;
    for (int i = 1; i <= 1000000; i++) {
        sum += i;
    }
}

void *print_num(void *param) {\
    int i = 0;
    while (1) {
        printf("%d\n", i%10);
        fflush(stdout);
        i++;
        sum_cpu();
    }
}

void *print_alph(void *param) {
    char letter = 'a';
    while (1) {
        printf("%c\n", letter);
        fflush(stdout);
        letter = (letter == 'z') ? 'a' : letter + 1;
        sum_cpu();
    }
}

void *print_pound(void *param) {
    while (1) {
        printf("#\n");
        fflush(stdout); 
        sum_cpu();
    }
}
 
int main() {
    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, print_num, NULL);
    pthread_create(&thread2, NULL, print_alph, NULL);
    pthread_create(&thread3, NULL, print_pound, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    return 0;
}