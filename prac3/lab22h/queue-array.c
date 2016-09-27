#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "queue.h"

struct queue {

};

queue queue_new() {
    int default_size = 7;
    
}

void enqueue(queue q, double item) {
    /*DON'T NEED TO CODE THIS*/
    if (q->num_items < q->capacity) {
        q->items[(q->head + q->num_items++) % q->capacity] = item;
    }
}

double dequeue(queue q) {

}

void queue_print(queue q) {
    /* print queue contents one per line to 2 decimal places */
    
}

void queue_print_info(queue q) {
    /*DON'T NEED TO CODE THIS*/
    int i;
    printf("capacity %d, num_items %d, head %d\n[", q->capacity, q->num_items,
           q->head);
    for (i = 0; i < q->capacity; i++) {
        printf("%s%.2f", i == 0 ? "" : ", ", q->items[i]);
    }
    printf("]\n");
}

int queue_size(queue q) {

}

queue queue_free(queue q) {
    
}
