#include <stdio.h>
#include <stdlib.h>

void selection_sort(int *arr, int size) {
    int i, j, smaller, temp;
    for (i = 0; i < size - 1; i++) {
        smaller = i;
        for (j = i + 1; j < size; j++) {
            if (arr[j] < arr[smaller])
                smaller = j;
        }

        temp = arr[smaller];
        arr[smaller] = arr[i];
        arr[i] = temp;
    }
}

void insertion_sort(int *arr, int size) {
    int i, j, temp;
    for (i = 1; i < size; i++) {
        temp = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

void print(int *arr, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void s_sort(int *arr, int size) {
    int i,j,tempi,tempv;
    for (i=0;i<size-1;i++){
        tempi = i;
        for (j=i+1;j<size;j++){
            if (arr[j]<arr[tempi]) tempi = j;
        }

        tempv = arr[tempi];
        arr[tempi] = arr[i];
        arr[i] = tempv;
    }
}

void i_sort(int *arr, int size) {
    int i,j,insert;
    for (i=1;i<size;i++){
        insert = arr[i];
        j=i-1;
        while(j>=0&&arr[j]>insert){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=insert;
    }
}

int main(void) {
    int myArray1[10] = {5, 4, 3, 6, 8, 7, 2, 9, 1, 10};
    int myArray2[10] = {5, 4, 3, 6, 8, 7, 2, 9, 1, 10};

    print(myArray1, 10);
    s_sort(myArray1, 10);
    print(myArray1, 10);

    printf("\n\n");

    print(myArray2, 10);
    i_sort(myArray2, 10);
    print(myArray2, 10);

    return EXIT_SUCCESS;
}

