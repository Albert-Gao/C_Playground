#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "flexarray.h"

struct flexarrayrec {
    int capacity;
    int itemcount;
    int *items;
};

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
    insertion_sort(f->items, f->itemcount);
}

void flexarray_free(flexarray f) {
    free(f->items);
    free(f);
}
