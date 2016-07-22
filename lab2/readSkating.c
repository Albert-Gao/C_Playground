#include <stdio.h>
#include <stdlib.h>

void insertion_sort(double arr[]) {
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
    double arr[3];

    while (4==scanf("%d%lg%lg%lg\n",&nowID, &p1, &p2, &p3)){
        arr[0]=p1;
        arr[1]=p2;
        arr[2]=p3;       
    }
    insertion_sort(arr);

    /*
    printf("%f\n",arr[0]);
    printf("%f\n",arr[1]);
    printf("%f\n",arr[2]);
    */

    if (arr[2] > *winnerScore){
        *winnerID = nowID;
        *winnerScore = arr[2];
    }
}

int main(){
    int i;
    int winnerID;
    double winnerScore=0;

    for (i=0; i<5; i++){
        readOneline(&winnerID, &winnerScore);    
    }

    printf("winner ID is %d\n", winnerID);
    printf("winner Score is %f\n", winnerScore);

    return EXIT_SUCCESS;
}