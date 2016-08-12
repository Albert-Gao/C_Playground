#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_MAX 2000000
int my_array[ARRAY_MAX];
int w[ARRAY_MAX];



void merge(int *arr, int *w, int length) {
    int middle = length/2;
    int i = 0, j = middle, k = 0;
    while (i < middle && j < length)
        {
            if (arr[i] < arr[j]){
                w[k] = arr[i];
                k+=1;
                i+=1;
            } else {
                w[k] = arr[j];
                k+=1;
                j+=1;
            }
        }

    while (i < middle) {
        w[k] = arr[i];
        k+=1;
        i+=1;
    } 

    while (j < length) {
        w[k] = arr[j];
        k+=1;
        j+=1;
    }  
}

/*
 *
 */
void merge_sort(int *arr, int *w, int length) {
    int i = 0, middle = (length/2);
    if (length<2) {
        return;
    }
    merge_sort(arr, w, middle);
    merge_sort(arr + middle, w + middle, length-middle);
    merge(arr, w, length);
   
    for (i = 0; i < length; i++){
        arr[i] = w[i];
    }
}


int main(void) {
    clock_t start, end;
    int i, count = 0;
    
    while (count < ARRAY_MAX && 1 == scanf("%d", &my_array[count])) {
        count++;
    }

    start = clock();
    merge_sort(my_array, w, count);
    end = clock();

    for (i = 0; i < count; i++) {
        printf("%d\n", my_array[i]);
    }

    fprintf(stderr, "%d %f\n", count, (end - start) / (double)CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
