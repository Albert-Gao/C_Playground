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
    
}

void htable_free(htable h) {
    
}

int htable_insert(htable h, char *str) {
    
}

void htable_print(htable h, FILE *stream) {
    /*DON'T NEED TO CODE THIS*/
    /*COPY IT FROM THE PRAC3 BOOK*/
    int i;
    for (i = 0; i < h->capacity; i++) {
        fprintf(stream, "%2d %s\n", i, h->keys[i] == NULL ? "" : h->keys[i]);
    }
}
