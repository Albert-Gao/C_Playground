#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 10

void insertion_sort(int *arr, int size) {
    /* Sorting code goes here */
    int start,previousIndex,insertValue;

    /* Start from the 2nd item*/
    for (start = 1; start < size; start++) {
        insertValue = arr[start];
        /* index of the value need to compare
         * with the insert value 
         */
        previousIndex = start - 1;

        /* While the previous item is bigger than the insertValue
         * and we don't outOfIndex, do the while loop
         */
        while (previousIndex >= 0 && arr[previousIndex] > insertValue) {
            /* store the previous value to the item next to it */
            arr[previousIndex + 1] = arr[previousIndex];
            /* narrow the sorted list by move index by 1 step back*/
            previousIndex = previousIndex - 1;
        }
        /* store the bumped insertValue to the front
         * of the sorted list */
        arr[previousIndex + 1] = insertValue;
    }
}
int main(void) {
    int my_array[ARRAY_MAX];
    int i, count = 0;
    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
        count++;
    }
    insertion_sort(my_array, count);
    for (i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }
    return EXIT_SUCCESS;
}
