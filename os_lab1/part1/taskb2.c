#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int m, k, n;
    scanf("%d %d %d", &m, &k, &n);

    int div[k];
    for (int i = 0; i < k; i++) {
        scanf("%d", &div[i]);
    }
    
     int *filter = (int*)calloc(m, sizeof(int));
     for (int op = 0; op < n; op++) {
        int op_code, element;
        scanf("%d %d", &op_code, &element);
         if (op_code == 1) {  
          
            for (int j = 0; j < k; j++) {
                int pos = (element % div[j]) % m;
                filter[pos] = 1;
            }
        } 
        else if (op_code == 2) {  
            
            int exists = 1;
            for (int j = 0; j < k; j++) {
                int pos = (element % div[j]) % m;
                if (filter[pos] == 0) {
                    exists = 0;
                    break;
                }
            }
            printf("%d\n", exists);
        }
    }

}