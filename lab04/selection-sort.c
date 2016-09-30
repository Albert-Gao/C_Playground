#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 40000

/*
 * start from the first item to the last
 * everytime you start from a index,
 * check all the rest items to its right side,
 * and everytime you found a smaller value,
 * mark its index until you hit the end.
 * swap the foundSmallest to the current start-loop-item
 * move the start index one more step to the right
 * then do the previous procedures again.
 */
void selection_sort(int *arr, int size) {
    /* Sorting code goes here */
    int i,j,min_index,tempSwap;

    for (i=0; i<size-1; i++){
        min_index = i;

        for (j=i+1;j<size;j++){
            if (arr[j]<arr[min_index]){
                min_index=j;
            }
        }

        tempSwap = arr[min_index];
        arr[min_index]=arr[i];
        arr[i]=tempSwap;        
    }
}
int main(void) {
    /*
    int my_array[ARRAY_MAX];
    int i, count = 0;
    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
        count++;
    }
    selection_sort(my_array, count);
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
    selection_sort(my_array, count);
    end = clock();
    for (i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }
    fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
