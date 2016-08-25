#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"

struct htable{
    unsigned int capacity;
    char **keys;
    unsigned int *frequencies;
};

htable htable_new(int capacity){
    htable result = emalloc(sizeof * result);
    result->keys = emalloc(result->capacity * sizeof result->keys[0]);
    result->frequencies = emalloc(result->capacity * sizeof result->frequencies[0]);
    result->capacity = capacity;
    for (unsigned int i = 0; i < result->capacity; i++){
      result->frequencies[i] = 0;
      result->keys[i] = NULL;
    }
    return result;
}

void htable_free(htable h){
    free(h->keys);
    free(h->frequencies);
    free(h);
}

static unsigned int htable_step(htable h, unsigned int i_key) {
  //return 1 + (i_key % (h->capacity - 1));
  return i_key%h->capacity;
}

static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;
    while (*word != '\0') {
       result = (*word++ + 31 * result);
    }
    return result;
}

int htable_insert(htable h, char *str){
    unsigned int convert = htable_word_to_int(str);
    unsigned int index = htable_step(h,convert);
    unsigned int i = 0;
    if (h->keys[index] == NULL){
        h->keys[index] = emalloc((strlen(str) + 1) * sizeof str[0]);
        strcpy(h->keys[index], str);
        h->frequencies[index] = 1;
        return 1;
    } else if (strcmp(str, h->keys[index])==0){
        h->frequencies[index]++;
        return h->frequencies[index];
    } else if (strcmp(str, h->keys[index])!=0){
        for ( i = index; i < h->capacity; i++){
            if (h->keys[i] == NULL){
                h->keys[i] = emalloc((strlen(str) + 1) * sizeof str[0]);
                strcpy(h->keys[i], str);
                h->frequencies[i] = 1;
                return 1;
            }
            if (strcmp(str,h->keys[i])==0){
                h->frequencies[i]++;
                return h->frequencies[i];
            }
            if (h->capacity == i){
                return 0;
            }
        }
    }
    return 0;
}

int htable_search(htable h, char *str){
    unsigned int collision = 0;
    unsigned int convert = htable_word_to_int(str);
    unsigned int index = htable_step(h,convert);

    while(h->keys[index]!=NULL &&
        (strcmp(str, h->keys[index])!=0 &&
        index < h->capacity)){

        index++;
        collision++;
    }

    if (collision == h->capacity){
        return 0;
    } else {
        return h->frequencies[index];
    }
}

void htable_print(htable h, FILE *stream){
    for (unsigned int i=0; i < h->capacity; i++){
        if (h->frequencies[i] != 0){
            fprintf(stream,"%s : %d\n",h->keys[i],h->frequencies[i]);
        }
    }
}
