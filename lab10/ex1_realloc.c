#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

void insertion_sort(int *arr, int size) {
    int start,previousIndex,insertValue;

    for (start = 1; start < size; start++) {
        insertValue = arr[start];
        previousIndex = start - 1;

        while (previousIndex >= 0 && arr[previousIndex] > insertValue) {
            arr[previousIndex + 1] = arr[previousIndex];
            previousIndex = previousIndex - 1;
        }
        arr[previousIndex + 1] = insertValue;
    }
}

static void array_print(int *a, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d\n", a[i]);
    }
}

int main(void) {
    int capacity = 2;
    int itemcount = 0;
    int item;
    int *my_array = emalloc(capacity * sizeof my_array[0]);
    
    while (1 == scanf("%d", &item)) {
        if (itemcount == capacity) {
            capacity += capacity;
            my_array = erealloc(my_array, capacity * sizeof my_array[0]);
        }
        my_array[itemcount++] = item;
    }
    insertion_sort(my_array,itemcount);
    array_print(my_array, itemcount);
    free(my_array);
    return EXIT_SUCCESS;
}
