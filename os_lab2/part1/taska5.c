#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


void create_processes(int n, int current) {
    if (current > n) {
        return; 
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // -------- CHILD PROCESS --------
        printf("Process %d created, Parent pid is %d\n", getpid(), getppid());

        create_processes(n, current + 1);

        
        wait(NULL);

       
        printf("Process %d exiting, Parent pid is %d\n", getpid(), getppid());
        exit(0);

    } 
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    if (n <= 0) {
        return 1;
    }

    
    create_processes(n, 1);

    return 0;
}
