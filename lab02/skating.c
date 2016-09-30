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

int main(void) {
    int s1, s2, s3;
    int return_code;
    int s[3];

    printf("enter 3 scores:");
    fflush(stdout);
    return_code = scanf("%d%d%d", &s1, &s2, &s3);

    if (return_code != 1) {
        s[0] = s1;
        s[1] = s2;
        s[2] = s3;
        insertion_sort(s);
    }

    if (s1 == s[0]) {
        printf("%d",(s2+s3)/2);
    } else if (s2 == s[0]) {
        printf("%d",(s1+s3)/2);
    } else if (s3 == s[0]) {
        printf("%d",(s1+s2)/2);
    }

    return EXIT_SUCCESS;
}