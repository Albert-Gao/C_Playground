#ifndef FLEXARRAY_H_
#define FLEXARRAY_H_
#include <stddef.h>

typedef struct flexarrayrec *flexarray;
/*
extern void* emalloc(size_t);
extern void* erealloc(void *, size_t);
*/
extern void flexarray_append(flexarray f, int item);
extern void flexarray_free(flexarray f);
extern flexarray flexarray_new();
extern void flexarray_print(flexarray f);
extern void flexarray_sort(flexarray f);

#endif
