#include <stdio.h>
#include <stdlib.h>
#include "flexarray.h"

struct flexarrayrec {
    int capacity;
    int itemcount;
    int *items;
};

void *emalloc(size_t s) {
    void *result = malloc(s);
    if (NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

void *erealloc(void *p, size_t s) {
    void *result = realloc(p, s);
    if (NULL == result) {
        fprintf(stderr, "Memory re-allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

/*
 * start from the first item to the last
 * everytime you start from a index,
 * check all the rest items to the one next to rightmost,
 * and everytime found a smaller value,
 * mark its index until you hit the end.
 * swap the found Smallest to the current start-loop-item
 * move the start index one more step to the right
 * then do the previous procedures again.
 */
void selection_sort(int *arr, int size) {
    int i, j, min_index, tempSwap, k;

    for (i = 0; i < size - 1; i++) {
        min_index = i;

        for (j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        tempSwap = arr[min_index];
        arr[min_index] = arr[i];
        arr[i] = tempSwap;

        if (i == ((size - 1) / 2)) {
            for (k = 0; k < size; k++) {
                fprintf(stderr, "%d\n", arr[k]);
            }
        }
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
    int i, n = f->itemcount;
    for (i = 0; i < n; i++) {
        printf("%d\n", f->items[i]);
    }
}

void flexarray_sort(flexarray f) { selection_sort(f->items, f->itemcount); }

void flexarray_free(flexarray f) {
    free(f->items);
    free(f);
}
