#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "htable.h"

int main(void) {
    htable h = htable_new(113,DOUBLE_H);
    char word[256];
    while (getword(word, sizeof word, stdin) != EOF) {
        htable_insert(h, word);
    }
    htable_print_entire_table(h, stdout);
    htable_print(h,stdout);
    htable_free(h);
    return EXIT_SUCCESS;
}