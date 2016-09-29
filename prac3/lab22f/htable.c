#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"

struct htablemod {
    /*DON'T NEED TO CODE THIS*/
    int capacity;
    int num_keys;
    char **keys;
};

static unsigned int htable_word_to_int(char *word) {
    /*DON'T NEED TO CODE THIS*/
    unsigned int result = 0;
    while (*word != '\0') {
        result = (*word++ + 31 * result);
    }
    return result;
}

static unsigned int htable_hash(htable h, unsigned int i_key) {
    /*DON'T NEED TO CODE THIS*/
    return i_key % h->capacity;
}

htable htable_new(int capacity) {
    int i;
    htable h = emalloc(sizeof *h);
    h->capacity = capacity;
    h->num_keys = 0;
    h->keys = emalloc(capacity*sizeof h->keys[0]);
    for(i=0;i<capacity;i++){
        h->keys[i]=NULL;
    }
    return h;
}

void htable_free(htable h) {
    int i;
    for (i=0;i<h->num_keys;i++){
        free(h->keys[i]);
    }
    free(h->keys);
    free(h);
}

int htable_insert(htable h, char *str) {
    unsigned int num = htable_word_to_int(str);
    unsigned int i = htable_hash(h,num);
    if (h->capacity==h->num_keys) return 0;
    for(;;){
        if (h->keys[i]==NULL){
            h->keys[i] = emalloc((strlen(str)+1)*sizeof h->keys[0]);
            strcpy(h->keys[i],str);
            h->num_keys++;
            return 1;
        }
        if (strcmp(h->keys[i],str)==0) return 0;
        i++;
        i=htable_hash(h,i);
    }
}

void htable_print(htable h, FILE *stream) {
    /*DON'T NEED TO CODE THIS*/
    /*COPY IT FROM THE PRAC3 BOOK*/
    int i;
    for (i = 0; i < h->capacity; i++) {
        fprintf(stream, "%2d %s\n", i, h->keys[i] == NULL ? "" : h->keys[i]);
    }
}
