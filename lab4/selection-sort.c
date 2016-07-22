#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 40000

/*
 *
 *
 */
void selection_sort(int *arr, int size) {
    /* Sorting code goes here */
    int i,j,min_index,tempSwap;

    /*start from the first item to the last*/
    for (i=0; i<size-1; i++){
        /* set the start index to min because in
         * the previous loop, it will exchange to
         * the smaller value */
        min_index = i;

        /*search from the rest of the array*/
        for (j=i+1;j<size;j++){
            /*if found a smaller one than the excluding item,
              store its index to the excluding item*/
            if (arr[j]<arr[min_index]){
                min_index=j;
            }
        }

        /* swap the value of the two items */
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
