#include <stdio.h>
#include <stdlib.h>

void check_repeats(int *array, int size) {
    int i = 0, j = 0;
    int *check_array = malloc(size * sizeof check_array[0]);

    for (i = 0; i < size; i++) {
        check_array[i] = 0;
    }

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (array[j] == i) {
                check_array[i]++;
            }
        }
    }

    for (i = 0; i < size; i++) {
        if (check_array[i] >= 2) {
            printf("%d occurs %d times\n", i, check_array[i]);
        }
    }

    free(check_array);
}

int main(void) {
    int array_size = 0;
    int *my_array;
    int i = 0;

    printf("Enter the size of the array: ");
    scanf("%d", &array_size);

    my_array = malloc(array_size * sizeof my_array[0]);

    if (NULL == my_array) {
        fprintf(stderr, "memory allocation failed!\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < array_size; i++) {
        my_array[i] = rand() % array_size;
    }

    printf("What’s in the array:\n");

    for (i = 0; i < array_size; i++) {
        printf("%d ", my_array[i]);
    }

    printf("\n");

    check_repeats(my_array, array_size);

    free(my_array);

    return EXIT_SUCCESS;
}
