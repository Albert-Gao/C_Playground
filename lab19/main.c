#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "mylib.h"

int main(void){
    queue q = queue_new();
    enqueue(q,1);
    enqueue(q,2);
    enqueue(q,3);
    enqueue(q,4);
    enqueue(q,5);

    queue_print(q);

    dequeue(q);/*dequeue 1*/
    queue_print(q);

    dequeue(q);/*dequeue 2*/
    queue_print(q);

    dequeue(q);/*dequeue 3*/
    queue_print(q);

    dequeue(q);/*dequeue 4*/
    queue_print(q);

    dequeue(q);/*dequeue 5*/
    queue_print(q);

    dequeue(q);/*dequeue one more*/
    queue_print(q);
    
    queue_free(q);

    return EXIT_SUCCESS;
}
