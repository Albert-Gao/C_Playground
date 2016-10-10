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

void insertion_sort(int *arr, int size){
    int i,k,insert,pre;
    for (i=1;i<size;i++){
        insert = arr[i];
        pre = i-1;
        while(pre>=0 && arr[pre]>insert){
            arr[pre+1]=arr[pre];
            pre--;
        }
        arr[pre+1]=insert;
        if(i==(size-1)/2){
            for(k=0;k<size;k++){
                fprintf(stderr,"%d\n",arr[k]);
            }
        }
    }
}

flexarray flexarray_new() {
    /* initialise flexarray structure (including items array) */
    flexarray f = emalloc(sizeof *f);
    f->capacity = 2;
    f->itemcount = 0;
    f->items = emalloc(f->capacity * sizeof f->items[0]);
    return f;
}

void flexarray_append(flexarray f, int num) {
    /* add an item to the flexarray, expanding as necessary */
    if(f->capacity==f->itemcount){
        f->capacity+=f->capacity;
        f->items = erealloc(f->items, f->capacity*sizeof f->items[0]);
    }
    f->items[f->itemcount++]=num;
}

void flexarray_print(flexarray f) {
    /* a "for" loop to print out each cell of f->items */
    int i;
    for(i=0;i<f->itemcount;i++)
        printf("%d\n",f->items[i]);
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