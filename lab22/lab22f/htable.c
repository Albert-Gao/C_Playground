#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"

struct htablemod{
    int capacity;
    int num_keys;
    char **keys;
};

htable htable_new(int capacity){
    int i;
    htable result = (htable)emalloc(sizeof * result);
    result->capacity = capacity;
    result->num_keys = 0;
    result->keys = (char **)emalloc(result->capacity * sizeof result->keys[0]);
    for (i = 0; i < result->capacity; i++){
      result->keys[i] = NULL;
    }
    return result;
}

void htable_free(htable h){
    int i;
    for (i=0; i < h->capacity; i++){
        if ( h->keys[i] != NULL ){
            free(h->keys[i]);
        }
    }
    free(h->keys);
    free(h);
}

static unsigned int htable_word_to_int(char *word) {
    /*DON'T NEED TO CODE THIS*/
    unsigned int result = 0;
    while (*word != '\0') {
       result = (*word++ + 31 * result);
    }
    return result;
}

int htable_insert(htable h, char *str){
    unsigned int num = htable_word_to_int(str);
    unsigned int index = num%h->capacity;
    if (h->num_keys == h->capacity){
        return 0;
    }
    for(;;){
        if (h->keys[index] == NULL){
            h->keys[index] = emalloc((strlen(str)+1) * sizeof str[0]);
            strcpy(h->keys[index], str);
            h->num_keys++;
            return 1;
        }
        if (strcmp(str, h->keys[index]) == 0){
            return 0;
        }
        index++;
        index = index % h->capacity;
    }
}

void htable_print(htable h, FILE *stream){
    int i;
    for (i = 0; i < h->capacity; i++) {
        fprintf(stream, "%2d %s\n", i, h->keys[i] == NULL ? "" : h->keys[i]);
    }
}
