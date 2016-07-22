#include "stdio.h"

void insertion_sort(int *arr, int size) {
    int start, compare, temp;

    for (start = 1; start < size; start++) {
        temp = arr[start];
        compare = start - 1;

        while (compare >= 0 && arr[compare] > temp) {
            arr[compare + 1] = arr[compare];
            compare = compare - 1;
        }

        arr[compare + 1] = temp;
    }
}

void max_min(int *a, int n, int *max, int *min){
	insertion_sort(a, n);
	*min = a[0];
	*max = a[n-1];
}

int main(void){
	int my_array[] = { 5, 2, 7, 3, 4 };
	int biggest=0, smallest=0;
	max_min(my_array, 5, &biggest, &smallest);
	printf("max value is %d, min value is %d\n", biggest, smallest);
	return 0;
}

