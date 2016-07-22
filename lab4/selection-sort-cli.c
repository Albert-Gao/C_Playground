#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 10

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
}
