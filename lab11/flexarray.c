#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "flexarray.h"

struct flexarrayrec {
    int capacity;
    int itemcount;
    int *items;
};

void quick_sort(int *arr, int size){
    int pivot = arr[0];
    int i = -1;
    int j = size;
    int temp;
    
    if (size < 2){
        return;
    }

    for(;;){
        do{i++;} while (arr[i] < pivot);
        do{j--;} while (arr[j] > pivot);
        
        if ( i < j ){
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        } else {
            break;
        }
    }
    quick_sort(arr, j+1);
    quick_sort(arr+i, size-j-1);
}

flexarray flexarray_new() {
    flexarray result = emalloc(sizeof *result);
    result->capacity = 2;
    result->itemcount = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);
    return result;
}

void flexarray_append(flexarray f, int num) {
    if (f->itemcount == f->capacity) {
        f->capacity += f->capacity;
        f->items = erealloc(f->items, f->capacity * sizeof f->items[0]);
    }
    f->items[f->itemcount++] = num;
}

void flexarray_print(flexarray f) {
    int n = f->itemcount;
    int i;
    for (i = 0; i < n; i++) {
        printf("%d\n", f->items[i]);
    }
}

void flexarray_sort(flexarray f) {
    quick_sort(f->items, f->itemcount);
}

void flexarray_free(flexarray f) {
    free(f->items);
    free(f);
}
