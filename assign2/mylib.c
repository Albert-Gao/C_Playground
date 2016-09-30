/**
 * Library for Memory allocations and getword.
 *
 * @Author foxre274 gaoha773 scrca599
 * @date 10/09/2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include "mylib.h"

/**
 * Allocates memory and checks for allocation failures.
 * @param s size of memory to allocate.
 *
 * @return pointer to successfully allocated memory.
 */
void *emalloc(size_t s) {
    void *result = malloc(s);
    if (NULL == result) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

/**
 * Reallocates memory and checks for allocation failures.
 * @param p pointer to previously allocated memory.
 * @param s size of memory to reallocate.
 *
 * @return pointer to successfully reallocated memory.
 */
void *erealloc(void *p, size_t s) {
    void *result = realloc(p, s);
    if (NULL == result) {
        fprintf(stderr, "Memory re-allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

/**
 * Reads consecutive words from a file.
 * @param s word to get.
 * @param limit the maximum size of the word.
 * @param stream fileto read from.
 *
 * @return the length of the word.
 */
int getword(char *s, int limit, FILE *stream) {
    int c;
    char *w = s;
    assert(limit > 0 && s != NULL && stream != NULL);
    /* skip to the start of the word */
    while (!isalnum(c = getc(stream)) && EOF != c)
        ;

    if (EOF == c) {
       return EOF;
    } else if (--limit > 0) { /* reduce limit by 1 to allow for the \0 */
       *w++ = tolower(c);
    }

    while (--limit > 0) {
       if (isalnum(c = getc(stream))) {
         *w++ = tolower(c);
       } else if ('\'' == c) {
         limit++;
       } else {
           break;
       }
   }
   *w = '\0';
   return w - s;
}
