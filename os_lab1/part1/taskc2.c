#include <stdio.h>
#include <stdlib.h>

int main() {
    int mat[5][5];
    int (*ptr)[5]=mat;
    for (int i = 0; i < 5; i++) {          
        for (int j = 0; j < 5; j++) {     
            *(*(ptr + i) + j) = i * 5 + j + 1;
        }
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
 return 0;   
}