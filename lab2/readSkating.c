#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int arr[]) {
    int start, compare, temp;

    for (start = 1; start < 3; start++) {
        temp = arr[start];
        compare = start - 1;

        while (compare >= 0 && arr[compare] > temp) {
            arr[compare + 1] = arr[compare];
            compare = compare - 1;
        }

        arr[compare + 1] = temp;
    }
}

void readOneline(int *winnerID, double *winnerScore){
    int nowID;
    double p1, p2, p3;
    int arr[3];

    scanf("%d%lg%lg%lg\n",&nowID, &p1, &p2, &p3);
    arr[0]=p1;
    arr[1]=p2;
    arr[2]=p3;
    insertion_sort(arr);

    if (arr[2] > *winnerScore){
        *winnerID = nowID;
        *winnerScore = arr[2];
    }
}

int main(){
    int winnerID;
    double winnerScore=0;
    readOneline(&winnerID, &winnerScore);
    readOneline(&winnerID, &winnerScore);
    readOneline(&winnerID, &winnerScore);

    printf("winner ID is %d\n", winnerID);
    printf("winner Score is %f\n", winnerScore);

    return EXIT_SUCCESS;
}