#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"

struct htablemod{
    unsigned int capacity;
    int num_keys;
    char **keys;
};

htable htable_new(int capacity){
    htable result = (htable)emalloc(sizeof * result);
    result->capacity = capacity;
    result->num_keys = 0;
    result->keys = (char **)emalloc(result->capacity * sizeof result->keys[0]);
    for (unsigned int i = 0; i < result->capacity; i++){
      result->keys[i] = NULL;
    }
    return result;
}

void htable_free(htable h){
    for (unsigned int i=0; i < h->capacity; i++){
        if ( h->keys[i] != NULL ){
            free(h->keys[i]);
        }
    }
    free(h->keys);
    free(h);
}

static unsigned int htable_word_to_int(char *word) {
    unsigned int result = 0;
    while (*word != '\0') {
       result = (*word++ + 31 * result);
    }
    return result;
}

int htable_insert1(htable h, char *str){
    // unsigned int convert = htable_word_to_int(str);
    // unsigned int index = convert%h->capacity;
    // unsigned int i = 0;
    // if (h->keys[index] == NULL){
    //     h->keys[index] = (char *)emalloc((strlen(str) + 1) * sizeof str[0]);
    //     strcpy(h->keys[index], str);
    //     h->num_keys++;
    //     return 1;
    // } else if (strcmp(str, h->keys[index])==0){
    //     return 0;
    // } else if (strcmp(str, h->keys[index])!=0){
    //     i = index + 1;
    //     while (i != index) {
    //         /* if found a open place, insert it */
    //         if (h->keys[i] == NULL){
    //             h->keys[i] = (char *)emalloc((strlen(str) + 1) * sizeof str[0]);
    //             strcpy(h->keys[i], str);
    //             h->num_keys++;
    //             return 1;
    //         }

    //         /* if found the string, increment the frequency and return */
    //         if (strcmp(str,h->keys[i])==0){
    //             return 0;
    //         }

    //         /* capacity gained, table full, return 0 */
    //         if (h->capacity == i){
    //             return 0;
    //         }
    //         i=(i+1)%h->capacity;
    //     }
    // }
    // return 0;
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
    unsigned int i;
    for (i = 0; i < h->capacity; i++) {
        fprintf(stream, "%2d %s\n", i, h->keys[i] == NULL ? "" : h->keys[i]);
    }
}
