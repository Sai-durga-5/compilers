#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int p2c[2], c2p[2];   
    pid_t pid;

    
    if (pipe(p2c) == -1 || pipe(c2p) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // ----------------- CHILD PROCESS -----------------
        close(p2c[1]); 
        close(c2p[0]); 
        int num_a, num_b, product;

        
        if (read(p2c[0], &num_a, sizeof(num_a)) == -1) {
            perror("read from parent failed");
            exit(1);
        }
        close(p2c[0]); 

        
        printf("Process B (PID: %d): Enter another positive integer: ", getpid());
        scanf("%d", &num_b);

        if (num_b <= 0) {
            printf("Invalid input in Process B! Exiting.\n");
            exit(1);
        }

        
        product = num_a * num_b;

        
        if (write(c2p[1], &product, sizeof(product)) == -1) {
            perror("write to parent failed");
            exit(1);
        }
        close(c2p[1]); 

        exit(0);
    } else {    
        close(p2c[0]); 
        close(c2p[1]); 
        int num_a, product;
           printf("Process A (PID: %d): Enter a positive integer: ", getpid());
        scanf("%d", &num_a);
        if (num_a <= 0) {
            printf("Invalid input in Process A! Exiting.\n");
            exit(1);
        }
        if (write(p2c[1], &num_a, sizeof(num_a)) == -1) {
            perror("write to child failed");
            exit(1);
        }
        close(p2c[1]); 
        wait(NULL);
        if (read(c2p[0], &product, sizeof(product)) == -1) {
            perror("read from child failed");
            exit(1);
        }
        close(c2p[0]);
        printf("Process A (PID: %d): Product is %d\n", getpid(), product);
    }

    return 0;
}

