#include <stdio.h>
#include <stdlib.h>
#include "htable.h"
#include "mylib.h"

typedef struct htablerec *htable;

extern htable htable_new(int capacity);
extern void htable_free(htable h);
extern void htable_print(htable h, FILE *stream);
extern int htable_insert(htable h, char *str);
extern int htable_search(htable h, char *str);

struct htable{
    int capacity;
    int *keys;
    int *frequencies;
};

htable htable_new(htable h){
    htable result = emalloc(sizeof *result);
    result->keys = emalloc(result->capacity * sizeof result->keys[0]);
    result->frequencies = emalloc(result->capacity * sizeof result->frequencies[0]);
    return result;
}

void htable_free(htable h){
    free(h->keys);
    free(h->frequencies);
    free(h);
}

htable_print(htable h, FILE *stream){
    int i;
    for (i=0; i < h->capacity; i++){
        fprintf(stderr,"%d : %d\n",h->keys[i],h->frequencies[i]);    
    }
}