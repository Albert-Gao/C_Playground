#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "mylib.h"

typedef struct q_item *q_item;

struct q_item {
    double item;
    q_item next;
};

struct queue {
    q_item first;
    q_item last;
    int length;
};

queue queue_new() {
    queue q = emalloc(sizeof *q);
    q->first = NULL;
    q->last = NULL;
    q->length = 0;
    return q;
}

void enqueue(queue q, double item) {
    q_item node = emalloc(sizeof *node);
    node->item = item;
    node->next = NULL;
    if (q->first == NULL) {
        q->first = node;
        q->first->next = NULL;
        q->last = q->first;
    } else if (q->first != NULL) {
        q->last->next = node;
        q->last = node;
    }
    q->length++;
    
}

double dequeue(queue q) {
    if (q->length > 1) {
        /*store the first one;*/
        q_item node = q->first;
        double item = node->item;

        /*make the 1st node points to the next*/
        q->first = node->next;

        /*free the former 1st node*/
        free(node);

        /*decrease the length*/
        q->length--;

        return item;
    } else if (q->length == 1) {
        double item = q->first->item;
        free(q->first);
        q->length--;
        return item;
    }
    return 0;
}

void queue_print(queue q) {
    printf("\n");
    if (q->length > 0) {
        q_item node = q->first;
        while (node != NULL) {
            printf("%.2f\n", node->item);
            node = node->next;
        }
    }
}

int queue_size(queue q) { return q->length; }

queue queue_free(queue q) {
    int i = 0;
    q_item node = q->first;
    while (i < q->length) {
        q_item tmp = node->next;
        free(node);
        node = tmp;
        i++;
    }
    free(q);
    return q;
}
