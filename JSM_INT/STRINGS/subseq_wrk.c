#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char seq[100][80] =  {{0}};
int next = 0;
void subseq(char *arr, int n, int prev, int len, int incl, int cfrom)
{
    int i,j, lcpy; 

    if (n == (len+1)) {
        return;
    }

    printf("\nN=%d, pr=%d, INC:%d cfrom=%d{{\t", n, prev,incl,cfrom);
    for (i=0; i < prev; i++){
         if ((seq[cfrom][i] != '\0')) {
             seq[next][i] = seq[cfrom][i]  ;
             printf(">%c<,i:%d ", seq[cfrom][i], i);
         } else {
             if (!incl) {
             seq[next][i] = seq[cfrom][i+1]  ;
             printf("skip:%d:%c",i,seq[cfrom][i+1]);
             }
         }

    }
    if (incl) { 
            seq[next][i] = arr[n-1];
            printf("NEW:%c i:%d,n=%d, Next=%d", seq[next][i],i, n, next);
    } 

    printf("\t }}N=%d, next=%d, SQ:%s SQ[next]=%c, %c: INC:%d ", 
                n, next, seq[next], seq[next][i], arr[n-1], incl);
    lcpy = next;
    next++;
    subseq(arr, n+1, prev, len, 0, lcpy);
    subseq(arr, n+1, prev+1, len, 1,lcpy);
}
int main (int argc, char **argv)
{
   char *arr = "ABCD";
   int len = strlen(arr), i,j;

   subseq(arr, 0, 0, len, 1, 0);
   printf("\n\nTotal is %d ", next); 
   for (i = 0; i <= next ; i++) {
       for (j=0;j<=len;j++)
          printf("%c ", seq[i][j]);
       printf("\n");
   }
}
