#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 40000

/*
 * Start from the 2nd item,
 * everytime when you do a sort,
 * bumped the started item first,
 * then compare all the previous items one by one,
 * from left to right, if the checked item is bigger
 * than the bumped item, copy its value to the bumped value,
 * then move one step back to do the checking again,
 * until you are outOfIndex, then insert the bumped value
 * to the stopped position. 
 */
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
int main(void) {
    /*
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
    */
    int my_array[ARRAY_MAX];
    clock_t start, end;
    int i, count = 0;
    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
        count++;
    }
    start = clock();
    insertion_sort(my_array, count);
    end = clock();
    for (i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }
    fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
