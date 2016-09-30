#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "queue.h"

typedef struct q_item *q_item;

struct q_item {
    double item;
    q_item next;
};

struct queue {
    q_item first,last;
    int length;
};

queue queue_new() {
    queue q = emalloc(sizeof *q);
    q->first = q->last = NULL;
    q->length = 0;
    return q;
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
    if(q->length>0){
        q_item node = q->first;
        double pop = node->item;

        q->first = node->next;
        free(node);
        q->length--;
        return pop;
    }
    return -8.88;
}

void queue_print(queue q) {
    q_item node;
    if (q->length>0){
        node = q->first;
        while(node!=NULL){
            printf("%.2f\n",node->item);
            node=node->next;
        }
    }
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
    return q->length;
}

queue queue_free(queue q) {
    q_item node;
    while(q->first!=NULL){
        node = q->first;
        q->first = node->next;
        free(node);
    }
    free(q);
    return q;
}
