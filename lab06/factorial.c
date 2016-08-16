#include <stdio.h>
#include <stdlib.h>

int factorial(int num) {
    if (num == 0){
        return 1;
    }
    return num*factorial(num-1);
}

int main(void){
    int num;
    while (1 == scanf("%d", &num)) {
        printf("%d\n", factorial(num));
    }
    return EXIT_SUCCESS;
}
