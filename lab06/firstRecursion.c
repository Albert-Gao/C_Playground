#include <stdio.h>


void insertion_sort(int *arr, int size) {
    int start,previousIndex,insertValue;

    for (start = 1; start < size; start++) {
        insertValue = arr[start];
        previousIndex = start - 1;

        while (previousIndex >= 0 && arr[previousIndex] > insertValue) {
            arr[previousIndex + 1] = arr[previousIndex];
            previousIndex = previousIndex - 1;
        }
        arr[previousIndex + 1] = insertValue;
    }
}

void printit(int *arr,int start, int size){
    if (start > size){
        return;
    }

    printf("%d ",arr[start]);
    printit(arr, ++start, size);
}

void print_it_c_way(int *arr, int size){
    if ( size == 0 ){
        return;
    }

    printf("%d ", arr[0]);
    print_it_c_way(arr+1, size-1);
}

int main(void){
    int test[] = {1,5,4,2,6,9,3};
    insertion_sort(test,7);
    print_it_c_way(test, 7);
}
