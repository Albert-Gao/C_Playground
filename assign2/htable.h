/**
 * ADT Interface for hTable.
 *
 * @Author foxre274 gaoha773 scrca599
 * @date 10/09/2016
 */

#ifndef  HTABLE_H_
#define HTABLE_H_

#include <stdio.h>

typedef struct htablerec *htable;
typedef enum hashing_e {LINEAR_P, DOUBLE_H} hashing_t;

/**
 * Creates an instance of a hash table.
 *
 * @param capacity sets the size of the hash table.
 * If no value is given, the default size is 113;
 * @param type the type of hash function used. This can be either
 * Linear probing hash table or Double hash table. By default this
 * is a Linear probing table.
 *
 * @return an empty hash table of size capacity.
 */

extern htable htable_new(int capacity, hashing_t type);

/**
 * Called once the hash table is finished with to deallocate
 * memory.
 *
 * @param h the table to have the allocated memory freed. 
 */

extern void htable_free(htable h);

/**
 * Inserts a new word into a hash table.
 *
 * @param h the table for the word to be inserted into.
 * @param str the word to be inserted into the hash table.
 *
 * @return If the word is inserted 1 is returned. If the word is
 * already in the hash table, the frequency is returned.
 */

extern int htable_insert(htable h,char *str);

/**
 * Searches a hash table for a given word.
 *
 * @param h the table to search in for the given word.
 * @param str the word to be searched for.
 *
 * @return If the word is found the frequency of the word is returned.
 * If the word isn't found 0 is returned. 
 */

extern int htable_search(htable h, char *str);

/**
 * Prints the content of the hash table, using the passed in function.
 *
 * @param h the table to print the contents of.
 * @param f the function to be used for printing. 
 */

extern void htable_print(htable h, void f());

/**
 * Print the Hash table Contents in the form of a 
 * table with the following columns:
 * Pos  Freq  Stats  Word
 * 
 * @li Pos - hash table position.
 * @li Freq - how many occurrences of the word in the text at the given position.
 * @li Stats - number of collisions that occurred, in sequential order.
 * @li Word - Word stored in hash table at the given position.
 *
 * @param h hash table.
 * @param FILE stream to output information to.
 */
extern void htable_print_entire_table(htable h, FILE *stream);

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

extern void htable_print_stats(htable h, FILE *stream, int num_stats);

#endif
