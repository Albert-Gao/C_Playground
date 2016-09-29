#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "queue.h"

typedef struct q_item *q_item;

struct q_item {

};

struct queue {

};

queue queue_new() {

}

void enqueue(queue q, double item) {
    /*DON'T NEED TO CODE THIS*/
    q_item i = emalloc(sizeof *i);
    i->item = item;
    i->next = NULL;
    if (q->length == 0) {
        q->first = i;
    } else {
        q->last->next = i;
    }
    q->last = i;
    q->length++;
}

double dequeue(queue q) {

}

void queue_print(queue q) {

}

void queue_print_info(queue q) {
    /*DON'T NEED TO CODE THIS*/
    if (q->length == 0) {
        printf("The queue is empty\n");
    } else {
        printf("first %.2f, last %.2f, length %d\n", q->first->item,
               q->last->item, q->length);
    }
}

int queue_size(queue q) { 

}

queue queue_free(queue q) {

}
