#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"

struct htable{
    unsigned int capacity;
    int num_keys;
    char **keys;
    unsigned int *frequencies;
};

htable htable_new(int capacity){
    htable result = emalloc(sizeof * result);
    result->capacity = capacity;
    result->num_keys = 0;
    result->keys = emalloc(result->capacity * sizeof result->keys[0]);
    result->frequencies = emalloc(result->capacity * sizeof result->frequencies[0]);
    for (unsigned int i = 0; i < result->capacity; i++){
      result->frequencies[i] = 0;
      result->keys[i] = NULL;
    }
    return result;
}

void htable_free(htable h){
    for (int i=0; i < h->capacity; i++){
        free(h->keys[i]);
    }
    free(h->keys);
    free(h->frequencies);
    free(h);
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
    unsigned int index = convert%h->capacity;
    unsigned int i = 0;
    if (h->keys[index] == NULL){
        h->keys[index] = emalloc((strlen(str) + 1) * sizeof str[0]);
        strcpy(h->keys[index], str);
        h->frequencies[index] = 1;
        h->num_keys++;
        return 1;
    } else if (strcmp(str, h->keys[index])==0){
        h->frequencies[index]++;
        return h->frequencies[index];
    } else if (strcmp(str, h->keys[index])!=0){
<<<<<<< HEAD:lab12/htable.c
        for ( i = index; i < h->capacity; i=(i+1)%h->capacity){
=======
        i = index + 1;
        while (i != index) {    
>>>>>>> 03925d7514d286f5b3ff9ed73abe9ecb3bb76d68:lab12-hashtable/htable.c
            /* if found a open place, insert it */
            if (h->keys[i] == NULL){
                h->keys[i] = emalloc((strlen(str) + 1) * sizeof str[0]);
                strcpy(h->keys[i], str);
                h->frequencies[i] = 1;
                h->num_keys++;
                return 1;
            }

            /* if found the string, increment the frequency and return */
            if (strcmp(str,h->keys[i])==0){
                h->frequencies[i]++;
                return h->frequencies[i];
            }

            /* capacity gained, table full, return 0 */
            if (h->capacity == i){
                return 0;
            }
            i=(i+1)%h->capacity;
        }
    }
    return 0;
}

int htable_search(htable h, char *str){
    unsigned int collision = 0;
    unsigned int convert = htable_word_to_int(str);
    unsigned int index = convert%h->capacity;

    while(h->keys[index]!=NULL &&
          (strcmp(str, h->keys[index])!=0 )){

        index = (index+1)%h->capacity;
        collision++;

        if (collision == h->capacity){
            return 0;
        }
    }
    return h->frequencies[index];
}

void htable_print(htable h, FILE *stream){
    for (unsigned int i=0; i < h->capacity; i++){
        if (h->frequencies[i] != 0){
            fprintf(stream,"%s : %d\n",h->keys[i],h->frequencies[i]);
        }
    }
}
