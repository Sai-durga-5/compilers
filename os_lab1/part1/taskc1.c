#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr[5]; 
    int *b;
     for (int i = 0; i < 5; i++) {
        arr[i] = (int *)malloc(sizeof(int)); 
        b = arr[i]; 
        *b = i + 1; 
     }
      for (int i = 0; i < 5; i++) {
        printf("%d ", *arr[i]);
    }
    printf("\n");

}
