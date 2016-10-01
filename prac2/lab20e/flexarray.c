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
        fprintf(stderr, "Memory allocation failed!!\n");
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

flexarray flexarray_new() {
    /* initialise flexarray structure (including items array) */
}

void flexarray_append(flexarray f, int num) {
    /* add an item to the flexarray, expanding as necessary */
}

void flexarray_print(flexarray f) {
    /* a "for" loop to print out each cell of f->items */
}

void flexarray_sort(flexarray f) { /* sort into ascending order */ }

void flexarray_free(flexarray f) {
    /* free the memory associated with the flexarray */
}