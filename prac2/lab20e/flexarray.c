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

void swap(int *x, int *y) {
    /*copy this from the book!*/
    int temp = *x; /* temp gets the value living at memory address x. */
    *x = *y;       /* the value at x gets the value at y. */
    *y = temp;     /* the value at y gets the variable "temp" */
}

void selection_sort(int *arr, int size){
    int i,j,k,min_index;
    for(i=0;i<size-1;i++){
        min_index = i;
        for (j=i+1;j<size;j++){
            if (arr[j]<arr[min_index])
                min_index = j;
        }
        swap(&arr[i],&arr[min_index]);
        if(i==(size-1)/2){
            for(k=0;k<size;k++)
                fprintf(stderr,"%d\n",arr[k]);
        }
    }
}

flexarray flexarray_new() {
    /* initialise flexarray structure (including items array) */
    flexarray f = emalloc(sizeof *f);
    f->capacity = 2;
    f->itemcount = 0;
    f->items = emalloc(f->capacity*sizeof f->items[0]);
    return f;
}

void flexarray_append(flexarray f, int num) {
    /* add an item to the flexarray, expanding as necessary */
    if(f->capacity==f->itemcount){
        f->capacity+=f->capacity;
        f->items=erealloc(f->items, f->capacity*sizeof f->items[0]);
    }
    f->items[f->itemcount++] = num;
}

void flexarray_print(flexarray f) {
    /* a "for" loop to print out each cell of f->items */
    int i;
    for(i=0;i<f->itemcount;i++)
        printf("%d\n",f->items[i]);
}

void flexarray_sort(flexarray f) { 
    /* sort into ascending order */ 
    selection_sort(f->items,f->itemcount);    
}

void flexarray_free(flexarray f) {
    /* free the memory associated with the flexarray */
    free(f->items);
    free(f);
}