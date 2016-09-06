#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"

struct htable {
    unsigned int capacity;
    int num_keys;
    char **keys;
    unsigned int *frequencies;
    int *stats;
    hashing_t method;
};

htable htable_new(int capacity, hashing_t hmethod){
    unsigned int i;
    htable result = emalloc(sizeof * result);
    result->capacity = 113;
    result->capacity = capacity;
    result->method = hmethod;
    result->keys = emalloc(result->capacity * sizeof result->keys[0]);
    result->frequencies = emalloc(result->capacity * sizeof result->frequencies[0]);
    result->stats = emalloc(result->capacity*sizeof result->stats[0]);
    for (i = 0; i < result->capacity; i++){
        result->stats[i] = 0;
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
    if (h->method == DOUBLE_H) {
       return 1 + (i_key % (h->capacity - 1));
    }
    return 1;
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
    unsigned int index = convert % h->capacity;
    unsigned int step = htable_step(h, convert);
    unsigned int i = 0;
    unsigned int collision = 0;
    if (h->keys[index] == NULL){
        h->keys[index] = emalloc((strlen(str) + 1) * sizeof str[0]);
        strcpy(h->keys[index], str);
        h->frequencies[index] = 1;
        return 1;
    } else if (strcmp(str, h->keys[index])==0){
        h->frequencies[index]++;
        return h->frequencies[index];
    } else if (strcmp(str, h->keys[index])!=0){
        i = (index + step)%h->capacity;
        while (i != index) {
            /* if found a open place, insert it */
            if (h->keys[i] == NULL){
                h->keys[i] = emalloc((strlen(str) + 1) * sizeof str[0]);
                strcpy(h->keys[i], str);
                h->frequencies[i] = 1;
                h->stats[i] = collision;
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

            i=(i+step)%h->capacity;
            collision += 1;
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

/**
 * Prints out a line of data from the hash table to reflect the state
 * the table was in when it was a certain percentage full.
 * Note: If the hashtable is less full than percent_full then no data
 * will be printed.
 *
 * @param h - the hash table.
 * @param stream - a stream to print the data to.
 * @param percent_full - the point at which to show the data from.
 */
static void print_stats_line(htable h, FILE *stream, int percent_full) {
   int current_entries = h->capacity * percent_full / 100;
   double average_collisions = 0.0;
   int at_home = 0;
   int max_collisions = 0;
   int i = 0;

   if (current_entries > 0 && current_entries <= h->num_keys) {
      for (i = 0; i < current_entries; i++) {
         if (h->stats[i] == 0) {
            at_home++;
         }
         if (h->stats[i] > max_collisions) {
            max_collisions = h->stats[i];
         }
         average_collisions += h->stats[i];
      }

      fprintf(stream, "%4d %10d %10.1f %10.2f %11d\n", percent_full,
              current_entries, at_home * 100.0 / current_entries,
              average_collisions / current_entries, max_collisions);
   }
}

/**
 * Prints out a table showing what the following attributes were like
 * at regular intervals (as determined by num_stats) while the
 * hashtable was being built.
 *
 * @li Percent At Home - how many keys were placed without a collision
 * occurring.
 * @li Average Collisions - how many collisions have occurred on
 *  average while placing all of the keys so far.
 * @li Maximum Collisions - the most collisions that have occurred
 * while placing a key.
 *
 * @param h the hashtable to print statistics summary from.
 * @param stream the stream to send output to.
 * @param num_stats the maximum number of statistical snapshots to print.
 */
void htable_print_stats(htable h, FILE *stream, int num_stats) {
   int i;

   fprintf(stream, "\n%s\n\n",
           h->method == LINEAR_P ? "Linear Probing" : "Double Hashing");
   fprintf(stream, "Percent   Current   Percent    Average      Maximum\n");
   fprintf(stream, " Full     Entries   At Home   Collisions   Collisions\n");
   fprintf(stream, "-----------------------------------------------------\n");
   for (i = 1; i <= num_stats; i++) {
      print_stats_line(h, stream, 100 * i / num_stats);
   }
   fprintf(stream, "-----------------------------------------------------\n\n");
}

void htable_print(htable h, FILE *stream){
    unsigned int i;
    for (i=0; i < h->capacity; i++){
        if (h->frequencies[i] != 0){
            fprintf(stream,"%d    %s\n", h->frequencies[i], h->keys[i]);
        }
    }
}

/**
 * Prints out the entire contents of the hash table, with the
 * position of the key in the hash table, the frequency of the key,
 * the number of collisions, and the key itself.
 * If a position doesn't contain a word, it will remain blank.
 *
 * @param h - the hash table.
 * @param stream - a stream to print the data to.
 */
void htable_print_entire_table(htable h, FILE *stream){
    unsigned int i;
    char *word;

    fprintf(stream, "  Pos  Freq  Stats  Word\n");
    fprintf(stream, "----------------------------------------\n");

    for (i=0; i < h->capacity; i++) {
       if (NULL == h->keys[i]) {
          word = "\0";
       }
       else {
          word = h->keys[i];
       }
       fprintf(stream, "%5d %5d %5d   %s\n", i, h->frequencies[i],
               h->stats[i], word);
    }
}
