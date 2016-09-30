#include <stdio.h>

int is_prime(int candidate) {
    int i, result = 1;
    for (i = 2; i <= candidate-1; i++) {
        if (candidate % i == 0) {
            result = 0;
            break;
        }
    }
    return result;
}

int main() {
    int candidate = 2, num_printed = 0;
    while (num_printed < 100) {
        if (is_prime(candidate) == 1) {
            printf("%d\n", candidate);
            num_printed+=1;
        }
        candidate+=1;
    }
    return 0;
}