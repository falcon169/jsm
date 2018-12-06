#include <stdio.h>
#include <string.h>

int max(int a, int b)
{   return (a > b ? a : b);
}

int lcs(char *str1, char *str2, int m , int n, int M, int N){
     int lcs_len = 0;
     if (str1 == NULL || str2 == NULL) {
         return 0;
     }
     if (m == M || n == N) {
         printf("++++\n");
         return 0;
     }

     if (str1[m] == str2[n]) {
         printf(" m=%d n=%d : %c ", m , n, str1[m]);
        //If same, move to next character in both strings
         return (lcs(str1, str2, m+1, n+1, M ,N) + 1);
     } else {
         //if not same, move to next character in one, while keeping other same and ..
         //extract maximum returned length from both
         return (max(lcs(str1, str2, m+1, n, M, N), lcs(str1, str2, m, n+1, M, N)));
     }
}
// Lomngest common subsequence
int main (int argc, char **argv)
{
   //LCS of ava.kkku 
   char *str1= "avajkkku";
   char *str2= "jhavakkkumll";
   printf("\n\n\n\n ****STR1 %lu STR2 %lu \n", strlen(str1), strlen(str2));
   printf(" %s %s ", str1, str2);
   printf(" \n Length of CS = %d", lcs(str1, str2, 0 , 0, strlen(str1), strlen(str2)));
}
