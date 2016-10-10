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

    /*copy this from the book!*/
    if (NULL == result) {
        fprintf(stderr, "Memory allocation failed!!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

void *erealloc(void *p, size_t s) {
    void *result = realloc(p, s);

    /*copy this from the book!*/
    if (NULL == result) {
        fprintf(stderr, "Memory re-allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

void insertion_sort(int *array, int size) {
    int i, j,insert_value, k;

    for (i = 1; i < size; i++) {
        insert_value = array[i];
        j = i - 1;
        while (j >= 0 && array[j] > array[i]) {
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = insert_value;
        if(i==(size-1)/2){
            for (k=0;k<size;k++)
                fprintf(stderr,"%d\n",array[k]);
        }
    }
}

flexarray flexarray_new() {
    /* initialise flexarray structure (including items array) */
    flexarray r = emalloc(sizeof *r);
    r->capacity = 2;
    r->itemcount = 0;
    r->items = emalloc(r->capacity * sizeof r->items[0]);
    return r;
}

void flexarray_append(flexarray f, int num) {
    /* add an item to the flexarray, expanding as necessary */
    if (f->capacity == f->itemcount) {
        f->capacity += f->capacity;
        f->items = realloc(f->items, f->capacity);
    }
    f->items[f->itemcount++] = num;
}

void flexarray_print(flexarray f) {
    /* a "for" loop to print out each cell of f->items */
    int i;
    for (i = 0; i < f->itemcount; i++)
        printf("%d\n", f->items[i]);
}

void flexarray_sort(flexarray f) { 
    /* sort into ascending order */
    insertion_sort(f->items,f->itemcount);
}

void flexarray_free(flexarray f) {
    /* free the memory associated with the flexarray */
    free(f->items);
    free(f);
}