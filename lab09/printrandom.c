#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int max=0;
    if (argc >= 2){
        max = atoi(argv[1]);
    }
    
    int i=0;
    for (i=0;i<max;i++){
        printf("%d\n",rand()%max);
    }
}
