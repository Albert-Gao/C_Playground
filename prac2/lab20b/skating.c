#include <stdio.h>
#include <stdlib.h>

int main(void){
    double s1=0,s2=0,s3=0,score=0,win_score=0;
    int skater=0,win_skater=0;

    while(4==scanf("%d%lg%lg%lg",&skater,&s1,&s2,&s3)){
        if (s1<s2&&s1<s3) score=(s2+s3)/2;
        else if (s2<s1&&s2<s3) score=(s1+s3)/2;
        else score=(s1+s2)/2;

        if(score>win_score){
            win_score = score;
            win_skater = skater;
        }

        printf("%d\n",win_skater);
    }
    return EXIT_SUCCESS;
}