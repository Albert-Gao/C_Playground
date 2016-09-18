/**
 * Library for Memory allocations and getword.
 *
 * @Author foxre274 gaoha773 scrca599
 * @date 10/09/2016
 */


#ifndef MYLIB_H_
#define MYLIB_H_
#include <stddef.h>

/**
 * Allocates memory and checks for allocation failures.
 * @param s size of memory to allocate.
 *
 * @return pointer to successfully allocated memory.
 */

extern void *emalloc(size_t);

/**
 * Reallocates memory and checks for allocation failures.
 * @param p pointer to previously allocated memory.
 * @param s size of memory to reallocate.
 *
 * @return pointer to successfully reallocated memory.
 */

extern void *erealloc(void *, size_t);

/**
 * Reads consecutive words from a file.
 * @param s word to get.
 * @param limit the maximum size of the word.
 * @param stream file to read from.
 *
 * @return the length of the word.
 */

extern int getword(char *s, int limit, FILE *stream);

#endif
